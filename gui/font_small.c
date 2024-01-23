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


#ifndef FONT_SMALL
#define FONT_SMALL

#include "font.h"

//https://www.dafont.com/wendy.font?sort=date&psize=xs

// 0x22 '"' TX
// 0x23 '#' MSG
// 0x24 '$' RX
// 0x26 '&' RSSI Empty
// 0x3F '?' RSSI Sep
// 0x40 '@' RSSI Box
// 0x5B '[' F key
// 0x5D ']' Lock
// 0x5C '\' Charging

const uint8_t font_smallBitmaps[] PROGMEM = {
  0x00, 0xE8, 0xEA, 0x95, 0x12, 0x54, 0xA0, 0xFF, 0x8E, 0xAC, 0x9F, 0xE0, 
  0xEB, 0x57, 0x15, 0x5A, 0xA0, 0x92, 0x49, 0x1C, 0x00, 0x6A, 0x40, 0x95, 
  0x80, 0x6D, 0xFD, 0xF1, 0xC1, 0x00, 0x5D, 0x00, 0xC0, 0xE0, 0x80, 0x25, 
  0x48, 0xF6, 0xDE, 0x59, 0x2E, 0x00, 0xE7, 0xCE, 0xE7, 0x9E, 0x96, 0xF2, 
  0xF3, 0x9E, 0xF3, 0xDE, 0xE4, 0x92, 0xF7, 0xDE, 0xF7, 0x9E, 0xA0, 0xB0, 
  0x2A, 0x22, 0xCC, 0x88, 0xA8, 0x00, 0x0A, 0x00, 0xFF, 0x80, 0xF7, 0xDA, 
  0xF7, 0x5E, 0xF2, 0x4E, 0xD6, 0xDC, 0xF3, 0xCE, 0xF3, 0x48, 0xF2, 0xDE, 
  0xB7, 0xDA, 0xF8, 0x24, 0x9E, 0xB7, 0x5A, 0x92, 0x4E, 0xDD, 0x6B, 0x58, 
  0x80, 0xF6, 0xDA, 0xF6, 0xDE, 0xF7, 0xC8, 0xF7, 0x92, 0xF7, 0x5A, 0xF3, 
  0x9E, 0xE9, 0x24, 0xB6, 0xDE, 0xB6, 0xD4, 0x8C, 0x6B, 0x5D, 0x80, 0xB5, 
  0x5A, 0xB7, 0x9E, 0xE5, 0x4E, 0x1E, 0x68, 0x38, 0x00, 0x57, 0xE2, 0xE2, 
  0x00, 0xE0, 0xBF, 0xE5, 0xE0, 0xF7, 0xDA, 0xF7, 0x5E, 0xF2, 0x4E, 0xD6, 
  0xDC, 0xF3, 0xCE, 0xF3, 0x48, 0xF2, 0xDE, 0xB7, 0xDA, 0xF8, 0x24, 0x9E, 
  0xB7, 0x5A, 0x92, 0x4E, 0xDD, 0x6B, 0x58, 0x80, 0xF6, 0xDA, 0xF6, 0xDE, 
  0xF7, 0xC8, 0xF7, 0x92, 0xF7, 0x5A, 0xF3, 0x9E, 0xE9, 0x24, 0xB6, 0xDE, 
  0xB6, 0xD4, 0x8C, 0x6B, 0x5D, 0x80, 0xB5, 0x5A, 0xB7, 0x9E, 0xE5, 0x4E, 
  0xFE
};

const GFXglyph font_smallGlyphs[] PROGMEM = {
  {     0,   1,   1,   2,    0,    0 },   // 0x20 ' '
  {     1,   1,   5,   2,    0,   -4 },   // 0x21 '!'
  {     2,   7,   5,   8,    0,   -4 },   // 0x22 '"'
  {     7,   7,   5,   8,    0,   -4 },   // 0x23 '#'
  {    12,   7,   5,   8,    0,   -4 },   // 0x24 '$'
  {    17,   4,   4,   5,    0,   -3 },   // 0x25 '%'
  {    19,   3,   3,   4,    0,   -4 },   // 0x26 '&'
  {     0,   0,   0,   0,    0,    0 },   // 0x27 '''
  {    21,   2,   5,   3,    0,   -4 },   // 0x28 '('
  {    23,   2,   5,   3,    0,   -4 },   // 0x29 ')'
  {    25,   7,   5,   8,    0,   -4 },   // 0x2A '*'
  {    30,   3,   3,   4,    0,   -3 },   // 0x2B '+'
  {    32,   1,   2,   2,    0,    0 },   // 0x2C ','
  {    33,   3,   1,   4,    0,   -2 },   // 0x2D '-'
  {    34,   1,   1,   2,    0,    0 },   // 0x2E '.'
  {    35,   3,   5,   6,    0,   -4 },   // 0x2F '/'
  {    37,   3,   5,   4,    0,   -4 },   // 0x30 '0'
  {    39,   3,   5,   4,    0,   -4 },   // 0x31 '1'
  {    42,   3,   5,   4,    0,   -4 },   // 0x32 '2'
  {    44,   3,   5,   4,    0,   -4 },   // 0x33 '3'
  {    46,   3,   5,   4,    0,   -4 },   // 0x34 '4'
  {    48,   3,   5,   4,    0,   -4 },   // 0x35 '5'
  {    50,   3,   5,   4,    0,   -4 },   // 0x36 '6'
  {    52,   3,   5,   4,    0,   -4 },   // 0x37 '7'
  {    54,   3,   5,   4,    0,   -4 },   // 0x38 '8'
  {    56,   3,   5,   4,    0,   -4 },   // 0x39 '9'
  {    58,   1,   3,   2,    0,   -2 },   // 0x3A ':'
  {    59,   1,   4,   2,    0,   -2 },   // 0x3B ';'
  {    60,   3,   5,   4,    0,   -4 },   // 0x3C '<'
  {    62,   2,   3,   3,    0,   -3 },   // 0x3D '='
  {    63,   3,   5,   4,    0,   -4 },   // 0x3E '>'
  {    65,   3,   5,   4,    0,   -4 },   // 0x3F '?'
  {    68,   3,   3,   4,    0,   -4 },   // 0x40 '@'
  {    70,   3,   5,   4,    0,   -4 },   // 0x41 'A'
  {    72,   3,   5,   4,    0,   -4 },   // 0x42 'B'
  {    74,   3,   5,   4,    0,   -4 },   // 0x43 'C'
  {    76,   3,   5,   4,    0,   -4 },   // 0x44 'D'
  {    78,   3,   5,   4,    0,   -4 },   // 0x45 'E'
  {    80,   3,   5,   4,    0,   -4 },   // 0x46 'F'
  {    82,   3,   5,   4,    0,   -4 },   // 0x47 'G'
  {    84,   3,   5,   4,    0,   -4 },   // 0x48 'H'
  {    86,   1,   5,   2,    0,   -4 },   // 0x49 'I'
  {    87,   3,   5,   4,    0,   -4 },   // 0x4A 'J'
  {    89,   3,   5,   4,    0,   -4 },   // 0x4B 'K'
  {    91,   3,   5,   4,    0,   -4 },   // 0x4C 'L'
  {    93,   5,   5,   6,    0,   -4 },   // 0x4D 'M'
  {    97,   3,   5,   4,    0,   -4 },   // 0x4E 'N'
  {    99,   3,   5,   4,    0,   -4 },   // 0x4F 'O'
  {   101,   3,   5,   4,    0,   -4 },   // 0x50 'P'
  {   103,   3,   5,   4,    0,   -4 },   // 0x51 'Q'
  {   105,   3,   5,   4,    0,   -4 },   // 0x52 'R'
  {   107,   3,   5,   4,    0,   -4 },   // 0x53 'S'
  {   109,   3,   5,   4,    0,   -4 },   // 0x54 'T'
  {   111,   3,   5,   4,    0,   -4 },   // 0x55 'U'
  {   113,   3,   5,   4,    0,   -4 },   // 0x56 'V'
  {   115,   5,   5,   6,    0,   -4 },   // 0x57 'W'
  {   119,   3,   5,   4,    0,   -4 },   // 0x58 'X'
  {   121,   3,   5,   4,    0,   -4 },   // 0x59 'Y'
  {   123,   3,   5,   4,    0,   -4 },   // 0x5A 'Z'
  {   125,   3,   7,   4,    0,   -5 },   // 0x5B '['
  {   129,   5,   5,   6,    0,   -4 },   // 0x5C '\'
  {   133,   8,   3,   9,    0,   -3 },   // 0x5D ']'
  {     0,   0,   0,   0,    0,    0 },   // 0x5E '^'
  {   136,   3,   1,   4,    0,    0 },   // 0x5F '_'
  {     0,   0,   0,   0,    0,    0 },   // 0x60 '`'
  {   137,   3,   5,   4,    0,   -4 },   // 0x61 'a'
  {   139,   3,   5,   4,    0,   -4 },   // 0x62 'b'
  {   141,   3,   5,   4,    0,   -4 },   // 0x63 'c'
  {   143,   3,   5,   4,    0,   -4 },   // 0x64 'd'
  {   145,   3,   5,   4,    0,   -4 },   // 0x65 'e'
  {   147,   3,   5,   4,    0,   -4 },   // 0x66 'f'
  {   149,   3,   5,   4,    0,   -4 },   // 0x67 'g'
  {   151,   3,   5,   4,    0,   -4 },   // 0x68 'h'
  {   153,   1,   5,   2,    0,   -4 },   // 0x69 'i'
  {   154,   3,   5,   4,    0,   -4 },   // 0x6A 'j'
  {   156,   3,   5,   4,    0,   -4 },   // 0x6B 'k'
  {   158,   3,   5,   4,    0,   -4 },   // 0x6C 'l'
  {   160,   5,   5,   6,    0,   -4 },   // 0x6D 'm'
  {   164,   3,   5,   4,    0,   -4 },   // 0x6E 'n'
  {   166,   3,   5,   4,    0,   -4 },   // 0x6F 'o'
  {   168,   3,   5,   4,    0,   -4 },   // 0x70 'p'
  {   170,   3,   5,   4,    0,   -4 },   // 0x71 'q'
  {   172,   3,   5,   4,    0,   -4 },   // 0x72 'r'
  {   174,   3,   5,   4,    0,   -4 },   // 0x73 's'
  {   176,   3,   5,   4,    0,   -4 },   // 0x74 't'
  {   178,   3,   5,   4,    0,   -4 },   // 0x75 'u'
  {   180,   3,   5,   4,    0,   -4 },   // 0x76 'v'
  {   182,   5,   5,   6,    0,   -4 },   // 0x77 'w'
  {   186,   3,   5,   4,    0,   -4 },   // 0x78 'x'
  {   188,   3,   5,   4,    0,   -4 },   // 0x79 'y'
  {   190,   3,   5,   4,    0,   -4 },   // 0x7A 'z'
  {     0,   0,   0,   0,    0,    0 },   // 0x7B '{'
  {   192,   1,   7,   2,    0,   -5 }    // 0x7C '|'
};

const GFXfont font_small PROGMEM = {
  (uint8_t  *)font_smallBitmaps,    
  (GFXglyph *)font_smallGlyphs, 0x20, 0x7C,     9 };

// Approx. 859 bytes

#endif