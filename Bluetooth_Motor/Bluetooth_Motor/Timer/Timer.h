/*
 * Timer.h
 *
 *  Created on: May 3, 2018
 *      Author: ihass
 */

#ifndef TIMER_TIMER_H_
#define TIMER_TIMER_H_

#include "../all-includes.h"

// Clear Timer interrupt function
extern void Timer0_Void_Clear(void);

// Timer in Normal Mode
extern void Timer0_Void_Initialize_NormalMode(void);

// Timer in Compare match Mode
extern void Timer0_Void_Initialize_CompareMatchMode(void);

// Timer in PWM Mode
extern void Timer0_Void_Initialize_PWMmode();

//timer 2 normal mode
extern void timer2_normal_mode_init(void) ;

#endif /* TIMER_TIMER_H_ */
