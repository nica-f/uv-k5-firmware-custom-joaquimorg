/* Copyright 2023 Dual Tachyon
 * https://github.com/DualTachyon
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 */

#include <stdint.h>
#include <string.h>
#include <stdio.h>     // NULL

#ifdef ENABLE_MESSENGER
	#include "app/messenger.h"
#endif

#ifdef ENABLE_AM_FIX
	#include "am_fix.h"
#endif

#include "audio.h"
#include "board.h"
#include "misc.h"
#include "radio.h"
#include "app.h"
#include "settings.h"
#include "version.h"

#include "app/app.h"
#include "app/dtmf.h"
#include "bsp/dp32g030/gpio.h"
#include "bsp/dp32g030/syscon.h"

#include "driver/backlight.h"
#include "driver/bk4819.h"
#include "driver/gpio.h"
#include "driver/system.h"
#include "driver/systick.h"
#ifdef ENABLE_UART
	#include "driver/uart.h"
	#include "app/uart.h"
	#include "ARMCM0.h"
#endif

#include "helper/battery.h"
#include "helper/boot.h"

#include "ui/lock.h"
#include "ui/welcome.h"
#include "ui/menu.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

StackType_t main_task_stack[configMINIMAL_STACK_SIZE + 500];
StaticTask_t main_task_buffer;

TimerHandle_t hwStatusTimer;
StaticTimer_t hwStatusTimerBuffer;

TimerHandle_t hwStatusTimer500;
StaticTimer_t hwStatusTimerBuffer500;


extern void SystickHandlerA(void);


void HandlerGPIOB1(void) {
	UART_printf("HandlerGPIOB IRQ %b \r\n", GPIO_CheckBit(&GPIOB->DATA, GPIOB_PIN_SWD_CLK));
}

void hw_timer_callback(TimerHandle_t xTimer) {	

#ifdef ENABLE_UART
	//taskENTER_CRITICAL();
	if (UART_IsCommandAvailable()) {
		//__disable_irq();
		UART_HandleCommand();
		//__enable_irq();
	}
	//taskEXIT_CRITICAL();
#endif

    xTimerStart(xTimer, 0);
}

//bool flippp = false;

void hw_timer_callback_500(TimerHandle_t xTimer) {

	//BK4819_ToggleGpioOut(2, flippp);
	//UART_printf("GPIOB->DATA %b \r\n", GPIO_CheckBit(&GPIOB->DATA, GPIOB_PIN_SWD_CLK));
	//flippp = !flippp;

	APP_TimeSlice500ms();
    xTimerStart(xTimer, 0);
}


void main_task(void* arg) {
	(void)arg;

	BOARD_Init();

#ifdef ENABLE_UART
	UART_Init();
	UART_Send(UART_Version, strlen(UART_Version));
#endif

	boot_counter_10ms = 250;   // 2.5 sec

	hwStatusTimer = xTimerCreateStatic("hwStatus", pdMS_TO_TICKS(50), pdFALSE, NULL, hw_timer_callback, &hwStatusTimerBuffer);

	hwStatusTimer500 = xTimerCreateStatic("hwStatus500", pdMS_TO_TICKS(500), pdFALSE, NULL, hw_timer_callback_500, &hwStatusTimerBuffer500);

	// Not implementing authentic device checks

	memset(gDTMF_String, '-', sizeof(gDTMF_String));
	gDTMF_String[sizeof(gDTMF_String) - 1] = 0;

	taskENTER_CRITICAL();
	BK4819_Init();

	BOARD_ADC_GetBatteryInfo(&gBatteryCurrentVoltage, &gBatteryCurrent);

	SETTINGS_InitEEPROM();

	#ifdef ENABLE_CONTRAST
		ST7565_SetContrast(gEeprom.LCD_CONTRAST);
	#endif

	//SETTINGS_WriteBuildOptions();
	SETTINGS_LoadCalibration();

	RADIO_ConfigureChannel(0, VFO_CONFIGURE_RELOAD);
	RADIO_ConfigureChannel(1, VFO_CONFIGURE_RELOAD);

	RADIO_SelectVfos();

	RADIO_SetupRegisters(true);

	for (unsigned int i = 0; i < ARRAY_SIZE(gBatteryVoltages); i++)
		BOARD_ADC_GetBatteryInfo(&gBatteryVoltages[i], &gBatteryCurrent);

	BATTERY_GetReadings(false);

#ifdef ENABLE_MESSENGER
	MSG_Init();
#endif

#ifdef ENABLE_AM_FIX
	AM_fix_init();
#endif

	const BOOT_Mode_t  BootMode = BOOT_GetMode();

	if (BootMode == BOOT_MODE_F_LOCK)
	{
		gF_LOCK = true;            // flag to say include the hidden menu items
	}

	// count the number of menu items
	gMenuListCount = 0;
	while (MenuList[gMenuListCount].name[0] != '\0') {
		if(!gF_LOCK && MenuList[gMenuListCount].menu_id == FIRST_HIDDEN_MENU_ITEM)
			break;

		gMenuListCount++;
	}

	// wait for user to release all butts before moving on
	if (!GPIO_CheckBit(&GPIOC->DATA, GPIOC_PIN_PTT) ||
	     KEYBOARD_Poll() != KEY_INVALID || BootMode != BOOT_MODE_NORMAL
	 		 
	)
	{	// keys are pressed
		UI_DisplayReleaseKeys();
		BACKLIGHT_TurnOn();

		// 500ms
		for (int i = 0; i < 50;)
		{
			i = (GPIO_CheckBit(&GPIOC->DATA, GPIOC_PIN_PTT) && KEYBOARD_Poll() == KEY_INVALID) ? i + 1 : 0;
			SYSTEM_DelayMs(10);
		}
		gKeyReading0 = KEY_INVALID;
		gKeyReading1 = KEY_INVALID;
		gDebounceCounter = 0;
	}

	/*if (!gChargingWithTypeC && gBatteryDisplayLevel == 0)
	{
		FUNCTION_Select(FUNCTION_POWER_SAVE);

		if (gEeprom.BACKLIGHT_TIME < (ARRAY_SIZE(gSubMenu_BACKLIGHT) - 1)) // backlight is not set to be always on
			BACKLIGHT_TurnOff();	// turn the backlight OFF
		else
			BACKLIGHT_TurnOn();  	// turn the backlight ON

		gReducedService = true;
	}
	else*/
	{
		UI_DisplayWelcome();

		BACKLIGHT_TurnOn();

		if (gEeprom.POWER_ON_DISPLAY_MODE != POWER_ON_DISPLAY_MODE_NONE)
		{	// 2.55 second boot-up screen
			while (boot_counter_10ms > 0)
			{
				if (KEYBOARD_Poll() != KEY_INVALID)
				{	// halt boot beeps
					boot_counter_10ms = 0;
					break;
				}
#ifdef ENABLE_BOOT_BEEPS
				if ((boot_counter_10ms % 25) == 0)
					AUDIO_PlayBeep(BEEP_880HZ_40MS_OPTIONAL);
#endif
			}
		}
/*
#ifdef ENABLE_PWRON_PASSWORD
		if (gEeprom.POWER_ON_PASSWORD < 1000000)
		{
			bIsInLockScreen = true;
			UI_DisplayLock();
			bIsInLockScreen = false;
		}
#endif
*/
		BOOT_ProcessMode(BootMode);

		GPIO_ClearBit(&GPIOA->DATA, GPIOA_PIN_VOICE_0);

		gUpdateStatus = true;

	}

	taskEXIT_CRITICAL();

	xTimerStart(hwStatusTimer500, 0);
	xTimerStart(hwStatusTimer, 0);
	//UART_printf("Ready... \r\n");
	while (true) {
		SystickHandlerA();
		APP_TimeSlice10ms();
		if (gCurrentFunction != FUNCTION_POWER_SAVE || !gRxIdleMode) {	
			CheckRadioInterrupts();
		}
		APP_Update();
		vTaskDelay(pdMS_TO_TICKS(5));
	}
}



void main_task_init(void) {

    xTaskCreateStatic(
		main_task,
		"MAIN",
		ARRAY_SIZE(main_task_stack),
		NULL,
		tskIDLE_PRIORITY,
		main_task_stack,
		&main_task_buffer
	);

}
