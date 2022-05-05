/*
 * Copyright (c) 2017-2022 JL1TTD Hidenori Ishii
 *
 * File:   i2c_software_driver.h
 * Author: JL1TTD Hidenori Ishii
 *
 * Created on March 28, 2017, 0:28 AM
 */

#ifndef I2C_DRIVER_H
#define	I2C_DRIVER_H

#define SOFT_I2C


#ifdef SOFT_I2C
#define SDA         LATAbits.LATA0        // P7
#define SCL         LATAbits.LATA1        // P6
#endif

#ifdef	__cplusplus
extern "C" {
#endif

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_send(uint8_t data);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_DRIVER_H */

