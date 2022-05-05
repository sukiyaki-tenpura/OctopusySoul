/*
 * Copyright (c) 2017-2022 JL1TTD Hidenori Ishii
 *
 * File:   lcd_st7032.h
 * Author: JL1TTD Hidenori Ishii
 *
 * Created on March 28, 2017, 0:28 AM
 */

#ifndef LCD_ST7032_H
#define	LCD_ST7032_H

#define DETER_LCD_FUNC

//#define LCD_RESET   LATCbits.LATC3
//#define LCD_ADDR    0x3e
// for software i2c (0x3e rol 1)
#define LCD_ADDR    0x7c

// 5V 21 3.3V 55
#define CONTRAST_DEFAULT    33


void lcd_command(uint8_t command);
void lcd_homepos(void);
void lcd_setpos(uint8_t column, uint8_t line);
#ifndef DETER_LCD_FUNC
void lcd_putc(uint8_t c_data);
#endif
void lcd_put_line(uint8_t* s_data);

void lcd_init(void);
void lcd_clear(void);
#ifndef DETER_LCD_FUNC
void lcd_contrast(uint8_t contrast);
#endif

#endif	/* LCD_ST7032_H */
