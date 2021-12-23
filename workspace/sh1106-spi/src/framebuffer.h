// Original code from https://github.com/agra-uni-bremen/sifive-hifive1
/*
 * framebuffer.hpp
 *
 *  Created on: Feb 3, 2020
 *      Author: dwd
 */

#pragma once
#include "display.h"

extern uint8_t framebuffer[DISP_W][DISP_H/8];

void fb_init();
void fb_flush();

void fb_set_pixel(uint8_t x, uint8_t y, uint8_t p);
void fb_set_pixel_direct(uint8_t x, uint8_t y, uint8_t p);
uint8_t fb_get_pixel(uint8_t x, uint8_t y);

