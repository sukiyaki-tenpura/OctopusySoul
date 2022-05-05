/*
 * Copyright (c) 2017-2022 JL1TTD Hidenori Ishii
 *
 * File:   frequency.h
 * Author: JL1TTD Hidenori Ishii
 *
 * Device:  PIC16F18313
 *
 * Created on Nov. 1st, 2021, 22:16
 */

#ifndef FREQUENCY_H
#define	FREQUENCY_H

#define CORRECT_SUBCOUNT

extern uint8_t  T0_prescaler_bits;
extern uint16_t prescaler_full_count;
extern uint16_t upper_count;
extern uint16_t upper_count_max;
extern volatile bool    ready_presentation;

extern volatile uint32_t    measure_count;
extern volatile bool    over_flow;
extern volatile bool    signal_detected;
extern volatile bool    measure_reset;

void frequency_initialize(void);
void measure_frequency(void);

#endif	/* FREQUENCY_H */
