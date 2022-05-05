/*
 * Copyright (c) 2017-2022 JL1TTD Hidenori Ishii
 *
 * File:   timebase.h
 * Author: JL1TTD Hidenori Ishii
 *
 * Device:  PIC16F15313
 *
 * Created on Nov. 1st, 2021, 22:16
 */

#ifndef TIMEBASE_H
#define	TIMEBASE_H

////////////////////////////////////////////
// Timebase params

#define GATE_10ms   0
#define GATE_100ms  1
#define GATE_1s     2
#define GATE_10s    3
#define GATE_MIN    GATE_10ms
#define GATE_MAX    GATE_10s

//#define T3BASE100ms
// Timer3 setting
#if (_XTAL_FREQ == 12800000)
#define T1_10ms     31
#define T1_100ms    319
#define T1_1s       3199
#define T1_10s      31999
#elif (_XTAL_FREQ == 10000000)
#define T1_10ms     24
#define T1_100ms    249
#define T1_1s       2499
#define T1_10s      24999
#endif

#define T2_2R5K     249

extern int8_t gate_time_index;

void timebase_initialize(void);
void set_gate_time(void);

inline void quick_open(void);

#endif	/* TIMEBASE_H */