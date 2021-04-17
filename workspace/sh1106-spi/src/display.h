// Copyright (c) 2017 Wladimir J. van der Laan
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef H_DISPLAY

#include <stdint.h>

/** Display width in pixels */
#define DISP_W 128
#define DISP_MEM_W 132
#define DISP_W_OFFS ((DISP_MEM_W-DISP_W)/2)
/** Display height in pixels */
#define DISP_H 64

#define OLED_CS	   15
#define OLED_CS_OFS 2	//Chip select offset -  0 = pin 10(2), 1 = ?, 2 = 15(9), 3 = 16(10)
#define OLED_SDIN  11
#define OLED_SCLK  13
#define OLED_RES   17
#define OLED_DC    16


/** Initialize pmodoled module */
void oled_init();
/** Initialize SPI */
void spi_init(void);
/** write a byte to OLED spi */
void spi(uint8_t data);
/** wait for completion of queued spi bytes */
void spi_complete(void);
/** set mode to data */
void mode_data(void);
/** set mode to commands */
void mode_cmd(void);

void setDisplayOn(uint8_t on);
void setChargePumpVoltage(uint8_t voltage);
void invertColor(uint8_t invert);
void setEntireDisplayOn(uint8_t allWhite);
void setDisplayStartLine(uint8_t startline);
void setDisplayOffset(uint8_t something);
void flipDisplay(uint8_t flip);
void setContrast(uint8_t contrast);
void fadeIn(uint64_t millis);
void fadeOut(uint64_t millis);

void set_x(unsigned col);
void set_row(unsigned row);
void set_xrow(unsigned col, unsigned row);
/** clear (visible portion of) screen, reset pointers */
void oled_clear(void);

#endif
