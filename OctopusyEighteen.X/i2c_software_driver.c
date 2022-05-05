/*
 * Copyright (c) 2017-2022 JL1TTD Hidenori Ishii
 *
 * File:   i2c_software_driver.c
 * Author: JL1TTD Hidenori Ishii
 *
 * Created on March 28, 2017, 0:28 AM
 */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "device_config.h"
#include "i2c_software_driver.h"


void i2c_init()
{
    SCL = 1;
    SDA = 1;
}
void i2c_start()
{
    SDA = 0;
    SCL = 0;
}
void i2c_stop()
{
    SCL = 1;
    SDA = 1;
}
void i2c_send(uint8_t data)
{
    for (uint8_t i=0; i<8; i++) {
        if(data & 0x80) {
            SDA = 1;
        }
        SCL = 1;
        SCL = 0;
        SDA = 0;
        data <<= 1;
    }
    SCL = 1;
    SCL = 0;
}
