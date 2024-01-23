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

#include <string.h>

#include "app/chFrScanner.h"
#ifdef ENABLE_FMRADIO
	#include "app/fm.h"
#endif
#ifdef ENABLE_MESSENGER
	#include "app/messenger.h"
#endif
#include "app/scanner.h"
#include "bitmaps.h"
#include "driver/keyboard.h"
#include "driver/st7565.h"
#include "external/printf/printf.h"
#include "functions.h"
#include "helper/battery.h"
#include "misc.h"
#include "settings.h"
#include "ui/battery.h"
#include "ui/helper.h"
#include "ui/ui.h"
#include "ui/status.h"
#include "gui/gui.h"


#define STATUS_SPACE 2

void UI_DisplayStatus()
{
	gUpdateStatus = false;
	memset(gFrameBuffer[0], 0, sizeof(gFrameBuffer[0]));

	GUI_drawBattery();

	switch (gSetting_battery_text) {
		default:
		case 0:
			break;

		case 1:	{	// voltage
			const uint16_t voltage = (gBatteryVoltageAverage <= 999) ? gBatteryVoltageAverage : 999; // limit to 9.99V
			UI_printf(&font_small, TEXT_ALIGN_LEFT, 18, 0, 4, true, false, "%u.%02uV", voltage / 100, voltage % 100);
			break;
		}

		case 2: {	// percentage
			const uint8_t gBatteryPercentage = BATTERY_VoltsToPercent(gBatteryVoltageAverage);
			UI_printf(&font_small, TEXT_ALIGN_LEFT, 18, 0, 4, true, false, "% 3i%%", gBatteryPercentage);
			break;
		}
	}

	// USB-C charge indicator
	if (gChargingWithTypeC) {
		UI_printf(&font_small, TEXT_ALIGN_LEFT, UI_nextX + STATUS_SPACE, 0, 4, true, false, "\\");
	}

	// POWER-SAVE indicator
	if (gCurrentFunction == FUNCTION_TRANSMIT) {
		UI_printf(&font_small, TEXT_ALIGN_LEFT, UI_nextX + STATUS_SPACE, 0, 4, true, false, "\"");
	}
	else if (FUNCTION_IsRx()) {
		UI_printf(&font_small, TEXT_ALIGN_LEFT, UI_nextX + STATUS_SPACE, 0, 4, true, false, "$");
	}
	else if (gCurrentFunction == FUNCTION_POWER_SAVE) {
		UI_printf(&font_small, TEXT_ALIGN_LEFT, UI_nextX + STATUS_SPACE, 0, 4, true, false, "PS");
	}

	// KEY-LOCK indicator
	if (gEeprom.KEY_LOCK) {
		UI_printf(&font_small, TEXT_ALIGN_LEFT, UI_nextX + STATUS_SPACE, 0, 4, true, false, "]");		
	}
	else if (gWasFKeyPressed) {
		UI_printf(&font_small, TEXT_ALIGN_LEFT, UI_nextX + STATUS_SPACE, 0, 4, true, false, "[");
	}

	//x += 8;
	//unsigned int x1 = x;

#ifdef ENABLE_MESSENGER
	if (hasNewMessage > 0) { // New Message indicator
		if (hasNewMessage == 1) {
			UI_printf(&font_small, TEXT_ALIGN_LEFT, UI_nextX + STATUS_SPACE, 0, 4, true, false, "#");
		}
			//memcpy(line + x, BITMAP_NEWMSG, sizeof(BITMAP_NEWMSG));
		//x1 = x + sizeof(BITMAP_NEWMSG);
	}
	//x += sizeof(BITMAP_NEWMSG);
#endif

#ifdef ENABLE_DTMF_CALLING
	if (gSetting_KILLED) {

		//memset(line + x, 0xFF, 10);
		//x1 = x + 10;
	}
	else
#endif
#ifdef ENABLE_FMRADIO
	if (gFmRadioMode) { // FM indicator

		//memcpy(line + x, BITMAP_FM, sizeof(BITMAP_FM));
		//x1 = x + sizeof(BITMAP_FM);
	}
	else
#endif
	{ // SCAN indicator
		if (gScanStateDir != SCAN_OFF || SCANNER_IsScanning()) {
			char * s = "";
			if (IS_MR_CHANNEL(gNextMrChannel) && !SCANNER_IsScanning()) { // channel mode
				switch(gEeprom.SCAN_LIST_DEFAULT) {
					case 0: s = "1"; break;
					case 1: s = "2"; break;
					case 2: s = "*"; break;
				}
			}
			else {	// frequency mode
				s = "S";
			}

			UI_printf(&font_small, TEXT_ALIGN_LEFT, UI_nextX + STATUS_SPACE, 0, 4, true, false, "%c", s);
			//UI_PrintStringSmallBufferNormal(s, line + x + 1);
			//x1 = x + 10;
		}
	}
	//x += 10;  // font character width

	if(!SCANNER_IsScanning()) {
		uint8_t dw = (gEeprom.DUAL_WATCH != DUAL_WATCH_OFF) + (gEeprom.CROSS_BAND_RX_TX != CROSS_BAND_OFF) * 2;
		if(dw == 1 || dw == 3) { // DWR - dual watch + respond
			if(gDualWatchActive) {
				UI_printf(&font_small, TEXT_ALIGN_LEFT, UI_nextX + STATUS_SPACE, 0, 4, true, false, "DW");
				//memcpy(line + x + (dw==1?0:2), BITMAP_TDR1, sizeof(BITMAP_TDR1) - (dw==1?0:5));
			} else {

				//memcpy(line + x + 3, BITMAP_TDR2, sizeof(BITMAP_TDR2));
			}
		}
		else if(dw == 2) { // XB - crossband
			UI_printf(&font_small, TEXT_ALIGN_LEFT, UI_nextX + STATUS_SPACE, 0, 4, true, false, "XB");
			//memcpy(line + x + 2, BITMAP_XB, sizeof(BITMAP_XB));
		}
	}
	//x += sizeof(BITMAP_TDR1) + 1;

#ifdef ENABLE_VOX
	// VOX indicator
	if (gEeprom.VOX_SWITCH) {

		UI_printf(&font_small, TEXT_ALIGN_LEFT, UI_nextX + STATUS_SPACE, 0, 4, true, false, "VOX");
		//memcpy(line + x, BITMAP_VOX, sizeof(BITMAP_VOX));
		//x1 = x + sizeof(BITMAP_VOX) + 1;
	}
	//x += sizeof(BITMAP_VOX) + 1;
#endif

	// **************

	UI_statusUpdate();
}
