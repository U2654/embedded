// Original code from https://github.com/agra-uni-bremen/sifive-hifive1
#pragma once

#include "inttypes.h"

#define FONT_W 6
#define FONT_H 1
#define FONT_N 128
#define CHAR_W (FONT_W+1)

void printChar(uint8_t ch);
void printText(const char* text);
void cls();
