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

#ifndef FONT_N_16
#define FONT_N_16

#include "font.h"

// https://www.dafont.com/pt/superstar-2.font?fpp=50&l[]=10&l[]=1

const uint8_t font_n_16Bitmaps[] PROGMEM = {
  0xDB, 0xFF, 0x7E, 0x7E, 0xFF, 0xDB, 0x30, 0xCF, 0xFF, 0x30, 0xC0, 0x6F, 
  0xE0, 0xFF, 0xF0, 0xF0, 0x01, 0x81, 0xC1, 0xC1, 0xC1, 0xC1, 0xC1, 0xC1, 
  0xC0, 0xC0, 0x00, 0x7D, 0xFF, 0x3E, 0xFF, 0xFE, 0xF9, 0xFF, 0x7C, 0x7F, 
  0xB6, 0xDB, 0x60, 0x7D, 0xFF, 0x18, 0xF7, 0xDE, 0x30, 0x7F, 0xFE, 0x7D, 
  0xFF, 0x18, 0xF1, 0xC0, 0xF1, 0xFF, 0x7C, 0x0C, 0x38, 0xF3, 0xEE, 0xD9, 
  0xBF, 0xFF, 0x0C, 0xFF, 0xFF, 0x07, 0xEF, 0xE0, 0xF1, 0xFF, 0x7C, 0x7D, 
  0xFB, 0x07, 0xEF, 0xF8, 0xF1, 0xFF, 0x7C, 0xFF, 0xFC, 0x18, 0x71, 0xC3, 
  0x0E, 0x18, 0x30, 0x7D, 0xFF, 0x1F, 0xF7, 0xD8, 0xF1, 0xFF, 0x7C, 0x7D, 
  0xFF, 0x1E, 0x3F, 0xEF, 0xC1, 0xBF, 0x7C, 0xF3, 0xC0
};

const GFXglyph font_n_16Glyphs[] PROGMEM = {
  {     0,   8,   6,   9,    0,   -8 },   // 0x2A '*'
  {     6,   6,   6,   7,    0,   -6 },   // 0x2B '+'
  {    11,   3,   4,   4,    0,   -3 },   // 0x2C ','
  {    13,   6,   2,   7,    0,   -4 },   // 0x2D '-'
  {    15,   2,   2,   3,    0,   -1 },   // 0x2E '.'
  {    16,   9,   9,  10,    0,   -8 },   // 0x2F '/'
  {    27,   7,   9,   8,    0,   -8 },   // 0x30 '0'
  {    35,   3,   9,   4,    0,   -8 },   // 0x31 '1'
  {    39,   7,   9,   8,    0,   -8 },   // 0x32 '2'
  {    47,   7,   9,   8,    0,   -8 },   // 0x33 '3'
  {    55,   7,   9,   8,    0,   -8 },   // 0x34 '4'
  {    63,   7,   9,   8,    0,   -8 },   // 0x35 '5'
  {    71,   7,   9,   8,    0,   -8 },   // 0x36 '6'
  {    79,   7,   9,   8,    0,   -8 },   // 0x37 '7'
  {    87,   7,   9,   8,    0,   -8 },   // 0x38 '8'
  {    95,   7,   9,   8,    0,   -8 },   // 0x39 '9'
  {   103,   2,   5,   3,    0,   -6 }    // 0x3A ':'
};

const GFXfont font_n_16 PROGMEM = {
  (uint8_t  *)font_n_16Bitmaps, 
  (GFXglyph *)font_n_16Glyphs, 0x2A, 0x3A,  17 };


#endif
