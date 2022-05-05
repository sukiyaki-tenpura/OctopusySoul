/*
 * Copyright (c) 2017-2022 JL1TTD Hidenori Ishii
 *
 * File:   display.c
 * Author: JL1TTD Hidenori Ishii
 *
 * Created on Nov. 1st, 2021, 22:16
 *
 * shrinking source code Apr. 2nd, 2022, 11:51
 */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "device_config.h"
#include "timebase.h"
#include "frequency.h"
#include "lcd_st7032.h"
#include "display.h"

#define DIGIT_MAX    10

static uint16_t prev_display_count;
static bool     force_draw = true;
static uint8_t  result_string[17] = {0};

void display_count(void)
{
    if (over_flow) {
        strcpy((char*)result_string, "Over flow!");
        force_draw = true;
        goto puts_result;
    }
    if (!signal_detected || measure_count == 0) {
        strcpy((char*)result_string, "No Signal!");
        force_draw = true;
        goto puts_result;
    }
    if (force_draw) {
        force_draw = false;
    } else if ((uint16_t)measure_count == prev_display_count) {
        return;
    }
    prev_display_count = (uint16_t)measure_count;

    uint32_t bcd_lo = 0;
    uint8_t  bcd_hi = 0;
    uint32_t bin_temp = measure_count;

    uint32_t msb = 0x80000000;
    uint8_t isBcdLoLsb = false;
    uint8_t isBcdNoZero = false;
    uint8_t isBcdHiLsb  = false;
    uint32_t bcdMask;
    uint32_t bcdComp;
    uint32_t bcdAdd;

    uint8_t loop = 0;
    while (true) {
        loop++;
        isBcdLoLsb = ((bin_temp & msb) != 0);
        bin_temp <<= 1;
        isBcdNoZero |= isBcdLoLsb;
        isBcdHiLsb = ((bcd_lo & 0x80000000) != 0);
        bcd_lo <<= 1;
        bcd_lo += isBcdLoLsb;
        bcd_hi <<= 1;
        bcd_hi += isBcdHiLsb;
        if (loop >= 32) {
            break;
        }
        if (!isBcdNoZero) {
            continue;
        }
        bcdMask = 0x0000000F;
        bcdComp = 0x00000005;
        bcdAdd  = 0x00000003;
        for (int j = 0; j < 8; j++) {
            if ((bcd_lo & bcdMask) >= bcdComp) {
                bcd_lo += bcdAdd;
            }
            bcdMask <<= 4;
            bcdComp <<= 4;
            bcdAdd <<= 4;
        }
        if ((bcd_hi & 0x0F) >= 0x05) {
            bcd_hi += 0x03;
        }
    }

    //                           "0123456789ABCDEF"
    strcpy((char*)result_string, "   .   ,     MHz");

    uint8_t digit;
    int8_t pos = 10 - (2 - gate_time_index);
    if (gate_time_index == GATE_10s) {
        result_string[pos] = ',';
        pos++;
    }
    loop = 0;
    while (pos >= 0) {
        if (loop < 8) {
            digit = bcd_lo & 0x0F;
            bcd_lo >>= 4;
        } else {
            digit = bcd_hi & 0x0F;
            bcd_hi >>= 4;
        }
        loop++;
        result_string[pos--] = digit + '0';
        if (pos == 3||pos == 7||pos == 11) {
            pos--;
        }
    }
    if (result_string[0] == '0') {
        result_string[0] = ' ';
        if (result_string[1] == '0') {
            result_string[1] = ' ';
        }
    }
puts_result:
    lcd_setpos(0, 0);
    lcd_put_line((uint8_t*)result_string);
}

static uint8_t gatetime_title[][9] = {
    " 10m Sec",
    "100m Sec",
    "   1 Sec",
    "  10 Sec",
};
void display_gatetime(void)
{
    force_draw = true;
    lcd_clear();
    lcd_put_line((uint8_t*)"Wait...");
    lcd_setpos(8,1);
    lcd_put_line((uint8_t*)gatetime_title[gate_time_index]);
}
