// See LICENSE for license details.

#include "encoding.h"
#include "platform.h"
#include "wrap.h"
#include "display.h"
#include "font.h"

#include <string.h>

extern void _init();

void delay(uint32_t f_milliseconds)
{
    volatile uint64_t *now = (volatile uint64_t*)(CLINT_CTRL_ADDR + CLINT_MTIME);
    volatile uint64_t then = *now + f_milliseconds*(RTC_FREQ / 2000);
    while (*now < then);
}

const char* text = "Oled example...";

int main (void)
{
	// init oled inclusive spi
	oled_init();

	// short break
	delay(2000);

	uint32_t textpos = 0;
	while (1)
	{
		printChar(text[textpos]);
		if(textpos % ((DISP_W / CHAR_W) * (DISP_H/8)) == ((DISP_W / CHAR_W) * (DISP_H/8))-1)
		{
			delay(200);
		}
		if (textpos + 1 >= strlen(text))
		{
			textpos = 0;
			delay(1000);
		}
		else
		{
			textpos++;
		}
	}
}

