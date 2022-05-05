/*
 * Copyright (c) 2017-2022 JL1TTD Hidenori Ishii
 *
 * File:   device_config.c
 * Author: JL1TTD Hidenori Ishii
 *
 * Device:  PIC16F18313
 *
 * Created on Nov. 1st, 2021, 22:16
 */
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "device_config.h"

// Configuration bits:

// CONFIG1
#pragma config FEXTOSC = ECH    // FEXTOSC External Oscillator mode Selection bits->EC (external clock) above 8 MHz
#pragma config RSTOSC = EXT1X   // Power-up default value for COSC bits->EXTOSC operating per FEXTOSC bits
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit->CLKOUT function is disabled; I/O or oscillator function on OSC2
#pragma config CSWEN = ON       // Clock Switch Enable bit->Writing to NOSC and NDIV is allowed
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable->Fail-Safe Clock Monitor is enabled

// CONFIG2
#pragma config MCLRE = OFF      // Master Clear Enable bit->MCLR/VPP pin function is digital input; MCLR internally disabled; Weak pull-up under control of port pin's WPU control bit.
#pragma config PWRTE = ON       // Power-up Timer Enable bit->PWRT enabled
#pragma config WDTE = OFF       // Watchdog Timer Enable bits->WDT disabled; SWDTEN is ignored
#pragma config LPBOREN = OFF    // Low-power BOR enable bit->ULPBOR disabled
#pragma config BOREN = SLEEP    // Brown-out Reset Enable bits->Brown-out Reset enabled while running, disabled in Sleep; SBOREN is ignored
#pragma config BORV = LOW       // Brown-out Reset Voltage selection bit->Brown-out voltage (Vbor) set to 2.45V
#pragma config PPS1WAY = OFF    // PPSLOCK bit One-Way Set Enable bit->The PPSLOCK bit can be set and cleared repeatedly (subject to the unlock sequence)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable bit->Stack Overflow or Underflow will cause a Reset
#pragma config DEBUG = OFF      // Debugger enable bit->Background debugger disabled

// CONFIG3
#pragma config WRT = OFF    // User NVM self-write protection bits->Write protection off
#pragma config LVP = OFF     // Low Voltage Programming Enable bit->HV on MCLR/VPP must be used for programming.

// CONFIG4
#pragma config CP = OFF    // User NVM Program Memory Code Protection bit->User NVM code protection disabled
#pragma config CPD = OFF   // Data NVM Memory Code Protection bit->Data NVM code protection disabled

void SYSTEM_Initialize(void)
{
    ////////////////////////// Peripheral Module Disable
    PMD0 = 0b01000011;  // CLKRMD CLKR disabled; SYSCMD SYSCLK enabled; FVRMD FVR disabled; IOCMD IOC enabled; NVMMD NVM enabled;
    PMD1 = 0b10000000;  // TMR0MD TMR0 enabled; TMR1MD TMR1 enabled; TMR4MD TMR4 enabled; TMR5MD TMR5 disabled; TMR2MD TMR2 enabled;
    PMD2 = 0b01100110;  // DACMD DAC disabled; CMP1MD CMP1 disabled; ADCMD ADC disabled; CMP2MD CMP2 disabled;
    PMD3 = 0b01100010;  // disable CWG2,1 PWM6 CCP2 enable PWM5 CCP1
    PMD4 = 0b00100010;  // disable UART1 MSSP1 need enable MSSP1 for hard I2C
    PMD5 = 0b00000000;  // disable - enable all CLC DSM

    ////////////////////////// OSCILLATOR_Initialize
    // NOSC EXTOSC; NDIV 1;
    OSCCON1 = 0x70;
    // CSWHOLD may proceed; SOSCPWR Low power; SOSCBE crystal oscillator;
    OSCCON3 = 0x00;
    // LFOEN disabled; ADOEN disabled; SOSCEN disabled; EXTOEN disabled; HFOEN disabled;
    OSCEN = 0x00;
    // HFFRQ 12_MHz;
    OSCFRQ = 0x04;
    // HFTUN 0;
    OSCTUNE = 0x00;

    // WDTPS 1:65536; SWDTEN OFF;
    WDTCON = 0x16;

// RA0 SOFT I2C SCL
// RA1 SOFT I2C SDA
// RA2 F input
// RA3 SW0 set
// RA4 brigde port PWM5 to TIMER1
// RA5 EXTOSC in
    //////////////////////// PIN_MANAGER_Initialize
    // ANSELx registers
    ANSELA  = 0x00;
    // TRISx registers
	TRISA   = 0b101100;     // RA5 i RA4 o RA3 i RA2 i RA1 o RA0 o
    // WPUx registers
    WPUA    = 0b001000;
    // ODx registers
    ODCONA  = 0b000000;
    // SLRCONx 0: max out speed
    SLRCONA = 0b000011;
    // INLVLx 1:ST in
    INLVLA  = 0b001000;

    // LATx registers
    PORTA   = 0b00001000;   // RA clear
    LATA    = 0b00000011;
}

