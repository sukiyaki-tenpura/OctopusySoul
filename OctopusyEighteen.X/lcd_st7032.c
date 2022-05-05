/*
 * Copyright (c) 2017-2022 JL1TTD Hidenori Ishii
 *
 * File:   lcd_st7032.c
 * Author: JL1TTD Hidenori Ishii
 *
 * Created on March 28, 2017, 0:28 AM
 */

#include <xc.h>
#include <stdio.h>
#include <stdint.h>

#include "device_config.h"
#include "i2c_software_driver.h"
#include "lcd_st7032.h"


////////////////////////////////////////////////////////////////////////////////
// AQM1602


void lcd_command(uint8_t command) {
    i2c_start();
    i2c_send(LCD_ADDR);
    i2c_send(0x80);
    i2c_send(command);
    i2c_stop();
    __delay_us(27);
}

void lcd_setpos(uint8_t column, uint8_t line) {
    lcd_command(0x80 | (uint8_t)(line << 6) | column);        // line0 column0 = 0x00, line1 column0 = 0x40
}
#ifndef DETER_LCD_FUNC
void lcd_putc(uint8_t c_data) {
    i2c_start();
    i2c_send(LCD_ADDR);
    i2c_send(0xC0);
    i2c_send(c_data);
    i2c_stop();
    __delay_us(27);
}
#endif
void lcd_put_line(uint8_t* s_data) {
    i2c_start();
    i2c_send(LCD_ADDR);
    i2c_send(0x40);
    for (int8_t i=0; i<16; i++) {
        if (*s_data == 0) {
            i2c_send(' ');
        } else {
            i2c_send(*s_data++);
        }
        __delay_us(27);
    }
    i2c_stop();
    __delay_us(27);
}

void lcd_clear(void) {
    lcd_command(0x01);
    __delay_us(1100);
}

#ifndef DETER_LCD_FUNC
void lcd_homepos(void) {
    lcd_command(0x02);
    __delay_us(1100);
}
void lcd_contrast(uint8_t contrast) {
    lcd_command(0x39);
    lcd_command(0x70 | (contrast & 0x0F));
    lcd_command(0x50 | 0x04 | ((contrast >> 4) & 0x03));
    lcd_command(0x38);

}
#endif

void lcd_init(void) {
    lcd_command(0x38);
    lcd_command(0x39);
    lcd_command(0x14);
    lcd_command(0x70 | (CONTRAST_DEFAULT & 0x0F));
    lcd_command(0x50 | 0x04 | ((CONTRAST_DEFAULT >> 4) & 0x03));
    lcd_command(0x6C);
    __delay_ms(210);
    lcd_command(0x38);
    lcd_command(0x01);
    __delay_us(1100);
    lcd_command(0x0C);
    lcd_command(0x06);
}
