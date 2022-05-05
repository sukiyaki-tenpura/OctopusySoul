/*
 * Copyright (c) 2017-2022 JL1TTD Hidenori Ishii
 *
 * File:   OctopusySoul.c
 * Author: JL1TTD Hidenori Ishii
 *
 * Created on Nov. 1st, 2021, 22:16
 *
 *      Product Revision  :  4.3.0
        Device            :  PIC16F15313, PIC16F18313
        Compiler          :  MPLAB XC8 v2.32 and above or later
        MPLAB X IDE       :  MPLAB X IDE v6.00 and above or later
 */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "device_config.h"
#include "timebase.h"
#include "frequency.h"
#include "i2c_software_driver.h"
#include "lcd_st7032.h"
#include "display.h"
#include "OctopusySoul.h"

#ifndef ONE_BUTTON
static void set_and_show_gatetime() {
    set_gate_time();
    display_gatetime();
    __delay_ms(200);
}
#endif

/*
    Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    i2c_init();

    // Enable Interrupts
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;

    lcd_init();

    frequency_initialize();
    timebase_initialize();

    // display splash
    // \xc0\xba\xc0\xde\xcf\xbc\xb2  タコタ゛マシイ \xca\xcb\xdf\xdd ハヒ゜ン \xb6\xb3\xdd\xc0 カウンタ
    // \xc4\xab\xc1\xac\xdd  トォチャン
    //                     "0123456789ABCDEF"
//  lcd_put_line((uint8_t*)"tkdamsi 8pincunt");
    lcd_put_line((uint8_t*)"\xc0\xba\xc0\xde\xcf\xbc\xb2 \xca\xcb\xdf\xdd\xb6\xb3\xdd\xc0");
    lcd_setpos(0,1);
    //                     "0123456789ABCDEF"
//  lcd_put_line((uint8_t*)"V.43tocynaJL1TTD");
    lcd_put_line((uint8_t*)"V.43\xc4\xab\xc1\xac\xdd@JL1TTD");
    __delay_ms(1500);
    lcd_clear();

    display_gatetime();

    while (1) {
        if (ready_presentation) {
            display_count();
            ready_presentation = false;
        } else {
            __delay_us(400);
        }
#ifdef ONE_BUTTON
        // gate time selection
        if (PORTAbits.RA3 == 0) {
            __delay_ms(10);
            gate_time_index++;
            if (gate_time_index > GATE_MAX) {
                gate_time_index = GATE_MIN;
            }
            set_gate_time();
            display_gatetime();
            __delay_ms(200);
        }
#else
        // gate time selection
        if (PORTAbits.RA4 == 0) {
            __delay_ms(10);
            gate_time_index++;
            if (gate_time_index > GATE_MAX) {
                gate_time_index = GATE_MIN;
            }
            set_and_show_gatetime();
        }
        if (PORTAbits.RA3 == 0) {
            __delay_ms(10);
            gate_time_index--;
            if (gate_time_index < GATE_MIN) {
                gate_time_index = GATE_MAX;
            }
            set_and_show_gatetime();
        }
#endif
    }
}