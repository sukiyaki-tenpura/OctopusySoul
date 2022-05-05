/*
 * Copyright (c) 2017-2022 JL1TTD Hidenori Ishii
 *
 * File:   device_config.c
 * Author: JL1TTD Hidenori Ishii
 *
 * Device:  PIC16F15313
 *
 * Created on Nov. 1st, 2021, 22:16
 */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "device_config.h"

// Configuration bits:

// CONFIG1
#pragma config FEXTOSC = ECH    // External Oscillator mode selection bits->EC above 8MHz; PFM set to high power
#pragma config RSTOSC = EXT1X    // Power-up default value for COSC bits->EXTOSC operating per FEXTOSC bits
#pragma config CLKOUTEN = OFF    // Clock Out Enable bit->CLKOUT function is disabled; i/o or oscillator function on OSC2
#pragma config CSWEN = ON    // Clock Switch Enable bit->Writing to NOSC and NDIV is allowed
#pragma config FCMEN = OFF    // Fail-Safe Clock Monitor Enable bit->FSCM timer disabled

// CONFIG2
#pragma config MCLRE = OFF    // Master Clear Enable bit->MCLR pin function is port defined function
#pragma config PWRTE = ON     // Power-up Timer Enable bit->PWRT enabled
#pragma config LPBOREN = OFF    // Low-Power BOR enable bit->ULPBOR disabled
#pragma config BOREN = OFF    // Brown-out reset enable bits->Brown-out reset disabled
#pragma config BORV = LO    // Brown-out Reset Voltage Selection->Brown-out Reset Voltage (VBOR) set to 1.9V on LF, and 2.45V on F Devices
#pragma config ZCD = OFF    // Zero-cross detect disable->Zero-cross detect circuit is disabled at POR.
#pragma config PPS1WAY = OFF    // Peripheral Pin Select one-way control->The PPSLOCK bit can be set and cleared repeatedly by software
#pragma config STVREN = ON    // Stack Overflow/Underflow Reset Enable bit->Stack Overflow or Underflow will cause a reset

// CONFIG3
#pragma config WDTCPS = WDTCPS_31    // WDT Period Select bits->Divider ratio 1:65536; software control of WDTPS
#pragma config WDTE = OFF    // WDT operating mode->WDT Disabled, SWDTEN is ignored
#pragma config WDTCWS = WDTCWS_7    // WDT Window Select bits->window always open (100%); software control; keyed access not required
#pragma config WDTCCS = SC    // WDT input clock selector->Software Control

// CONFIG4
#pragma config BBSIZE = BB512    // Boot Block Size Selection bits->512 words boot block size
#pragma config BBEN = OFF    // Boot Block Enable bit->Boot Block disabled
#pragma config SAFEN = OFF    // SAF Enable bit->SAF disabled
#pragma config WRTAPP = OFF    // Application Block Write Protection bit->Application Block not write protected
#pragma config WRTB = OFF    // Boot Block Write Protection bit->Boot Block not write protected
#pragma config WRTC = OFF    // Configuration Register Write Protection bit->Configuration Register not write protected
#pragma config WRTSAF = OFF    // Storage Area Flash Write Protection bit->SAF not write protected
#pragma config LVP = OFF    // Low Voltage Programming Enable bit->High Voltage on MCLR/Vpp must be used for programming

// CONFIG5
#pragma config CP = OFF    // UserNVM Program memory code protection bit->UserNVM code protection disabled


void SYSTEM_Initialize(void)
{
    ////////////////////////// Peripheral Module Disable
    // CLKRMD CLKR disabled; SYSCMD SYSCLK enabled; FVRMD FVR disabled; IOCMD IOC disabled; NVMMD NVM enabled;
    PMD0 = 0x43;
    // TMR0MD TMR0 enabled; TMR1MD TMR1 enabled; TMR2MD TMR2 enabled; NCOMD DDS(NCO) disabled;
    PMD1 = 0x80;
    // ZCDMD ZCD disabled; CMP1MD CMP1 disabled; ADCMD ADC disabled; DAC1MD DAC1 disabled;
    PMD2 = 0x63;
    // CCP2MD CCP2 disabled; CCP1MD CCP1 enabled; PWM4MD PWM4 disabled; PWM3MD PWM3 disabled; PWM6MD PWM6 disabled; PWM5MD PWM5 enabled;
    PMD3 = 0x2E;
    // CWG1MD CWG1 disabled; MSSP1MD MSSP1 disabled; UART1MD EUSART disabled;
    PMD4 = 0x51;
    // all CLC enabled
    PMD5 = 0x00;

    // NOSC EXTOSC; NDIV 1;
    OSCCON1 = 0x70;
    // CSWHOLD may proceed;
    OSCCON3 = 0x00;
    // MFOEN disabled; LFOEN disabled; ADOEN disabled; EXTOEN disabled; HFOEN disabled;
    OSCEN = 0x00;
    // HFFRQ 12_MHz;
    OSCFRQ = 0x04;
    // MFOR not ready;
    OSCSTAT = 0x00;
    // HFTUN 0;
    OSCTUNE = 0x00;

// RA0 SOFT I2C SCL
// RA1 SOFT I2C SDA
// RA2 F input
// RA3 SW0 set
// RA4 SW1 select (for test Gate out)
// RA5 EXTOSC in
    //////////////////////// PIN_MANAGER_Initialize
    // ANSELx registers
    ANSELA  = 0x00;
    // TRISx registers
	TRISA   = 0b111100;     // RA5 i RA4 i(o) RA3 i RA2 i RA1 o RA0 o
    // WPUx registers
    WPUA    = 0b011000;
    // ODx registers
    ODCONA  = 0b000000;
    // SLRCONx 0: max out speed
    SLRCONA = 0b000011;
    // INLVLx 1:ST in 0:TTL in
    INLVLA  = 0b011011;

    // LATx registers
    PORTA   = 0b011000;   // RA clear
    LATA    = 0b000011;
}
