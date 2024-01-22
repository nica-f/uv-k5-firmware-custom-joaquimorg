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

#ifndef UI_UI_H
#define UI_UI_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "gui/ui.h"

/*
void UI_GenerateChannelString(char *pString, const uint8_t Channel);
void UI_GenerateChannelStringEx(char *pString, const bool bShowPrefix, const uint8_t ChannelNumber);
void UI_PrintString(const char *pString, uint8_t Start, uint8_t End, uint8_t Line, uint8_t Width);
void UI_PrintStringSmallNormal(const char *pString, uint8_t Start, uint8_t End, uint8_t Line);
void UI_PrintStringSmallBold(const char *pString, uint8_t Start, uint8_t End, uint8_t Line);
void UI_PrintStringSmallBufferNormal(const char *pString, uint8_t *buffer);
void UI_PrintStringSmallBufferBold(const char *pString, uint8_t * buffer);
void UI_DisplayFrequency(const char *string, uint8_t X, uint8_t Y, bool center);

void UI_DisplayPopup(const char *string);

void UI_DrawPixelBuffer(uint8_t (*buffer)[128], uint8_t x, uint8_t y, bool black);
void UI_DrawLineBuffer(uint8_t (*buffer)[128], int16_t x1, int16_t y1, int16_t x2, int16_t y2, bool black);
void UI_DrawDottedLineBuffer(uint8_t (*buffer)[128], int16_t x1, int16_t y1, int16_t x2, int16_t y2, bool black, int dotSpacing);
void UI_DrawRectangleBuffer(uint8_t (*buffer)[128], int16_t x1, int16_t y1, int16_t x2, int16_t y2, bool black);

void PutPixel(uint8_t x, uint8_t y, bool fill);
void PutPixelStatus(uint8_t x, uint8_t y, bool fill);
void DrawVLine(int sy, int ey, int nx, bool fill);
void GUI_DisplaySmallest(const char *pString, uint8_t x, uint8_t y, bool statusbar, bool fill);

void UI_displayClear();
*/

void UI_GenerateChannelString(__attribute__((unused)) char *pString, __attribute__((unused)) const uint8_t Channel);
void UI_GenerateChannelStringEx(__attribute__((unused)) char *pString, __attribute__((unused)) const bool bShowPrefix, __attribute__((unused)) const uint8_t ChannelNumber);
void UI_PrintString(__attribute__((unused)) const char *pString, __attribute__((unused)) uint8_t Start, __attribute__((unused)) uint8_t End, __attribute__((unused)) uint8_t Line, __attribute__((unused)) uint8_t Width);
void UI_PrintStringSmallNormal(__attribute__((unused)) const char *pString, __attribute__((unused)) uint8_t Start, __attribute__((unused)) uint8_t End, __attribute__((unused)) uint8_t Line);
void UI_PrintStringSmallBold(__attribute__((unused)) const char *pString, __attribute__((unused)) uint8_t Start, __attribute__((unused)) uint8_t End, __attribute__((unused)) uint8_t Line);
void UI_PrintStringSmallBufferNormal(__attribute__((unused)) const char *pString, __attribute__((unused)) uint8_t *buffer);
void UI_PrintStringSmallBufferBold(__attribute__((unused)) const char *pString, __attribute__((unused)) uint8_t * buffer);
void UI_DisplayFrequency(__attribute__((unused)) const char *string, __attribute__((unused)) uint8_t X, __attribute__((unused)) uint8_t Y, __attribute__((unused)) bool center);

void UI_DisplayPopup(__attribute__((unused)) const char *string);

void UI_DrawPixelBuffer(__attribute__((unused)) uint8_t (*buffer)[128], __attribute__((unused)) uint8_t x, __attribute__((unused)) uint8_t y, __attribute__((unused)) bool black);
void UI_DrawLineBuffer(__attribute__((unused)) uint8_t (*buffer)[128], __attribute__((unused)) int16_t x1, __attribute__((unused)) int16_t y1, __attribute__((unused)) int16_t x2, __attribute__((unused)) int16_t y2, __attribute__((unused)) bool black);
void UI_DrawDottedLineBuffer(__attribute__((unused)) uint8_t (*buffer)[128], __attribute__((unused)) int16_t x1, __attribute__((unused)) int16_t y1, __attribute__((unused)) int16_t x2, __attribute__((unused)) int16_t y2, __attribute__((unused)) bool black, __attribute__((unused)) int dotSpacing);
void UI_DrawRectangleBuffer(__attribute__((unused)) uint8_t (*buffer)[128], __attribute__((unused)) int16_t x1, __attribute__((unused)) int16_t y1, __attribute__((unused)) int16_t x2, __attribute__((unused)) int16_t y2, __attribute__((unused)) bool black);

void PutPixel(__attribute__((unused)) uint8_t x, __attribute__((unused)) uint8_t y, __attribute__((unused)) bool fill);
void PutPixelStatus(__attribute__((unused)) uint8_t x, __attribute__((unused)) uint8_t y, __attribute__((unused)) bool fill);
void DrawVLine(__attribute__((unused)) int sy, __attribute__((unused)) int ey, __attribute__((unused)) int nx, __attribute__((unused)) bool fill);
void GUI_DisplaySmallest(__attribute__((unused)) const char *pString, __attribute__((unused)) uint8_t x, __attribute__((unused)) uint8_t y, __attribute__((unused)) bool statusbar, __attribute__((unused)) bool fill);

//void UI_displayClear();

#endif
