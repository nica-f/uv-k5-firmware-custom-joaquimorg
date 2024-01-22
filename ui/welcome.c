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

#include "driver/eeprom.h"
#include "driver/st7565.h"
#include "external/printf/printf.h"
#include "helper/battery.h"
#include "settings.h"
#include "misc.h"
#include "ui/helper.h"
#include "ui/welcome.h"
#include "ui/status.h"
#include "gui/gui.h"
#include "version.h"

void UI_DisplayReleaseKeys(void)
{
	const uint8_t popupW = 100;
	const uint8_t popupH = 40;

    uint8_t startX;
    uint8_t startY;

	memset(gFrameBuffer[0],  0, sizeof(gFrameBuffer[0]));
	UI_displayClear();

	GUI_showPopup(popupW, popupH, &startX, &startY);

	UI_drawString(&font_10, TEXT_ALIGN_CENTER, startX, startX + popupW - 2, startY + 5, "RELEASE", true, false);
	UI_drawString(&font_10, TEXT_ALIGN_CENTER, startX, startX + popupW - 2, startY + 25, "ALL KEYS", true, false);

	UI_statusUpdate();
	UI_displayUpdate();
}

void UI_DisplayWelcome(void)
{
	char WelcomeString0[16];
	char WelcomeString1[16];

	memset(gFrameBuffer[0],  0, sizeof(gFrameBuffer[0]));
	UI_displayClear();

	if (gEeprom.POWER_ON_DISPLAY_MODE == POWER_ON_DISPLAY_MODE_NONE || gEeprom.POWER_ON_DISPLAY_MODE == POWER_ON_DISPLAY_MODE_FULL_SCREEN) {
		//ST7565_FillScreen(0xFF);
	} else {
		memset(WelcomeString0, 0, sizeof(WelcomeString0));
		memset(WelcomeString1, 0, sizeof(WelcomeString1));

		if (gEeprom.POWER_ON_DISPLAY_MODE == POWER_ON_DISPLAY_MODE_VOLTAGE)
		{
			strcpy(WelcomeString0, "VOLTAGE");
			sprintf(WelcomeString1, "%u.%02uV %u%%",
				gBatteryVoltageAverage / 100,
				gBatteryVoltageAverage % 100,
				BATTERY_VoltsToPercent(gBatteryVoltageAverage));
		}
		else
		{
			EEPROM_ReadBuffer(0x0EB0, WelcomeString0, 16);
			EEPROM_ReadBuffer(0x0EC0, WelcomeString1, 16);
		}

		/*UI_PrintString(WelcomeString0, 0, 127, 0, 10);
		UI_PrintString(WelcomeString1, 0, 127, 2, 10);
		UI_PrintStringSmallBold(Version, 0, 127, 4);
		UI_PrintStringSmallNormal(__DATE__, 0, 127, 6);*/

		UI_drawString(&font_10, TEXT_ALIGN_CENTER, 0, 128, 12, WelcomeString0, true, false);
		UI_drawString(&font_10, TEXT_ALIGN_CENTER, 0, 128, 22, WelcomeString1, true, false);
    	UI_drawString(&font_10, TEXT_ALIGN_CENTER, 0, 128, 36, Version, false, true);
    	UI_drawString(&font_small, TEXT_ALIGN_CENTER, 0, 128, 48, __DATE__, true, false);;
		UI_drawString(&font_10, TEXT_ALIGN_CENTER, 0, 128, 60, "2024 - joaquim.org", true, false);

		UI_statusUpdate();  // blank status line
		UI_displayUpdate();
	}
}
