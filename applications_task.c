/* Copyright 2024 joaquim.org
 * https://github.com/joaquimorg
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
#include <stdio.h>
#include <stdbool.h>

#include "settings.h"
#include "applications_task.h"
#include "task_main.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "driver/keyboard.h"
#include "driver/backlight.h"

#ifdef ENABLE_UART
	#include "driver/uart.h"
#endif

#include "misc.h"
#include "audio.h"
#include "gui/ui.h"
#include "gui/gui.h"
#include "ui/status.h"
#include "apps/apps.h"
#include "apps/welcome.h"
#include "apps/main_vfo.h"
#include "apps/settings_menu.h"

#define QUEUE_LENGTH    10
#define ITEM_SIZE       sizeof( APP_Messages_t )

StackType_t app_task_stack[configMINIMAL_STACK_SIZE + 100];
StaticTask_t app_task_buffer;

static StaticQueue_t appTasksQueue;
QueueHandle_t appTasksMsgQueue;
uint8_t appQueueStorageArea[ QUEUE_LENGTH * ITEM_SIZE ];

/*-----------------------------------------------------------*/

static app_t *currentApplication;
static APPS_t currentApp;

TimerHandle_t idleTimer;
StaticTimer_t idleTimerBuffer;

TimerHandle_t renderTimer;
StaticTimer_t renderTimerBuffer;
/*-----------------------------------------------------------*/

static APPS_Popup_t currentAppPopup;
static bool popupAutoClose = false;
static bool autoReturntoMain = true;

/*-----------------------------------------------------------*/

void idle_timer_callback(TimerHandle_t xTimer) {

	(void)xTimer;

	app_push_message(APP_MSG_TIMEOUT);

    //xTimerStart(xTimer, 0);

}

void render_timer_callback(TimerHandle_t xTimer) {

	if (currentApplication->render) {
        UI_updateDisplay = currentApplication->render();
    }

    if (currentApplication->showStatusLine) {
        UI_DisplayStatus();
        UI_updateStatus = true;
    }

    if ( currentAppPopup != APP_POPUP_NONE ) {
        if (currentApplication->renderPopup) {
            UI_updateDisplay = currentApplication->renderPopup(currentAppPopup);
        }       
    }

    UI_statusUpdate();
    UI_displayUpdate();

    xTimerStart(xTimer, 0);

}

void keyboard_callback(KEY_Code_t key, KEY_State_t state) {
    xTimerReset(idleTimer, 0);

    if ( currentAppPopup != APP_POPUP_NONE ) {
        if (currentApplication->keyhandlerPopup) {
            currentApplication->keyhandlerPopup(key, state, currentAppPopup);
        }
    } else {
        if (currentApplication->keyhandler) {
            currentApplication->keyhandler(key, state);
        }
    }

    if ( !BACKLIGHT_IsOn() ) {
        app_push_message(APP_MSG_WAKEUP);
    }

    if ( state != KEY_RELEASED && state != KEY_LONG_PRESSED_CONT ) {
        main_push_message_value(MAIN_MSG_PLAY_BEEP, BEEP_1KHZ_60MS_OPTIONAL);
    }
}

/*-----------------------------------------------------------*/

void app_task(void* arg) {
	(void)arg;

    currentAppPopup = APP_POPUP_NONE;

    appTasksMsgQueue = xQueueCreateStatic(QUEUE_LENGTH, ITEM_SIZE, appQueueStorageArea, &appTasksQueue);

    keyboard_init(keyboard_callback);    

    renderTimer = xTimerCreateStatic("render", pdMS_TO_TICKS(50), pdFALSE, NULL, render_timer_callback, &renderTimerBuffer);
    idleTimer = xTimerCreateStatic("idle", pdMS_TO_TICKS(5000), pdTRUE, NULL, idle_timer_callback, &idleTimerBuffer);

    load_application(APP_WELCOME);
    
    xTimerStart(idleTimer, 0);
    xTimerStart(renderTimer, 0);
    //UART_printf("APPs Ready\r\n");
    
    while(true) {

        APP_Messages_t msg;
    	if (xQueueReceive(appTasksMsgQueue, &msg, 50)) {

			switch(msg.message) {
                case APP_MSG_TIMEOUT:
                    if ( currentApp != APP_MAIN_VFO && autoReturntoMain ) {
                        load_application(APP_MAIN_VFO);
                    } else {
                        if( currentAppPopup != APP_POPUP_NONE && popupAutoClose) {
                            currentAppPopup = APP_POPUP_NONE;
                            xTimerReset( idleTimer, 0 );
                        } else {
                            main_push_message(MAIN_MSG_BKLIGHT_OFF);
                        }
                    }
                    break;
                case APP_MSG_TIMEOUT_RETURN_MAIN:
                    autoReturntoMain = true;
                    break;

	            case APP_MSG_TIMEOUT_NO_RETURN_MAIN:
                    autoReturntoMain = false;
                    break;

				case APP_MSG_WAKEUP:
					main_push_message(MAIN_MSG_BKLIGHT_ON);
					break;

                case APP_MSG_IDLE:
					//global_status.isRX = false;
					break;

                case APP_MSG_RX:
                    //global_status.isRX = true;
                    xTimerReset( idleTimer, 0 );
					if ( !BACKLIGHT_IsOn() ) {
						main_push_message(MAIN_MSG_BKLIGHT_ON);
					}
                    break;

                case APP_MSG_TX:
                    break;
                default:
                    break;
            }

        }

        keyboard_task();

    }
}


void app_push_message_value(APP_MSG_t msg, uint32_t value) {
    APP_Messages_t appMSG = { msg, value };
    BaseType_t xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;
    xQueueSendToBackFromISR(appTasksMsgQueue, (void *)&appMSG, &xHigherPriorityTaskWoken);
}

void app_push_message(APP_MSG_t msg) {
    app_push_message_value(msg, 0);
}

/*-----------------------------------------------------------*/

void change_application(app_t *application) {
    if ( currentApplication != application ) {
        currentApplication = application;        
        xTimerStop(renderTimer, 0);
        currentApplication->init();
        UI_updateDisplay = true;
        UI_displayUpdate();
        xTimerStart(renderTimer, 0);
    }    
}

void load_application(APPS_t application) {
    switch (application)
    {
    case APP_WELCOME:
        change_application(&APPWelcome);
        break;
    case APP_MAIN_VFO:
        //strcpy(global_status.statusMessage, "VFO\0");
        change_application(&APPMainVFO);
        break;
    case APP_MENU:
        //strcpy(global_status.statusMessage, "MENU\0");
        change_application(&APPMainMenu);
        break;

    default:
        break;
    }
    currentApp = application;
}

/*-----------------------------------------------------------*/

void application_showPopup(APPS_Popup_t popup, bool autoClose) {
    currentAppPopup = popup;
    popupAutoClose = autoClose;
    xTimerReset( idleTimer, 0 );
}

void application_closePopup(void) {
    currentAppPopup = APP_POPUP_NONE;
    popupAutoClose = false;
    xTimerReset( idleTimer, 0 );
}

/*-----------------------------------------------------------*/

void applications_task_init(void) {

    xTaskCreateStatic(
		app_task,
		"APP",
		ARRAY_SIZE(app_task_stack),
		NULL,
		2 + tskIDLE_PRIORITY,
		app_task_stack,
		&app_task_buffer
	);

}