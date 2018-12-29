/*
 * Timer.c
 *
 *  Created on: May 3, 2018
 *      Author: Hassan Ibrahim
 */

#include "../all-includes.h"

// Clear Timer interrupt function
extern void Timer0_Void_Clear(void) {
	/*
	 TIMSK : Timer Interrupt Mask Register
	 TIMSK = 0bxxxxxx10;
	 */

	// Bit0 : TOIE0 : Timer/Counter0 Overflow interrupt Enable : Enabled in Normal  Mode only
	Clr_Bit(TIMSK, 0);

	// Bit1 : OCIE0 : Timer/Counter0 Output compare match Interrupt Enable : Enabled in Compare match Mode only
	Clr_Bit(TIMSK, 1);

} // End of Timer0_Void_Clear

// Timer in Normal Mode
extern void Timer0_Void_Initialize_NormalMode(void) {

	/*
	 TCNT0 : Timer Counter Register
	 It counts from 0 to 255 in Normal Mode
	 */

	// initialize counter to start from 0
	TCNT0 = 0;

	/*
	 TCCR0 : Timer Counter Control Register
	 TCCR0 = 0b00000101;
	 */

	// Bit 7 : FOC0 : Force Output Compare : This bit is only active when specifies a Non PWM mode
	Clr_Bit(TCCR0, 7);

	// Bit 6:3 : WGM01:0 : WaveForm generation mode
	// WGM01:0 : 00 : Timer counter works in Normal Mode
	Clr_Bit(TCCR0, 6);
	Clr_Bit(TCCR0, 3);

	// Bit 4:5 : COM01:0 : Compare Match output mode
	// Com01:0 : 00 : Timer counter works in Normal Mode : OC0 is disconnected
	Clr_Bit(TCCR0, 4);
	Clr_Bit(TCCR0, 5);

	// Bit 2:0 : CS02:0 : Clock Select : Pre-scaler
	// CS01:0 : 100 : 256 Pre-scaler
	Set_Bit(TCCR0, 2);
	Clr_Bit(TCCR0, 1);
	Clr_Bit(TCCR0, 0);

	/*
	 TIMSK : Timer Interrupt Mask Register
	 TIMSK = 0bxxxxxx01;
	 */

	// Bit0 : TOIE0 : Timer/Counter0 Overflow interrupt Enable : Enabled in Normal  Mode only
	Set_Bit(TIMSK, 0);

	// Bit1 : OCIE0 : Timer/Counter0 Output compare match Interrupt Enable : Enabled in Compare match Mode only
	Clr_Bit(TIMSK, 1);

	/*
	 TIFR : Timer Interrupt Flag Register
	 TIFR = 0bxxxxxx01;
	 */

	// Bit0 : TOV0 : Timer/Counter0 Overflow Flag : Enabled in Normal  Mode only
	Set_Bit(TIFR, 0);

	// Bit1 : OCF0 : Timer/Counter0 Output compare match Flag : Enabled in Compare match Mode only
	Clr_Bit(TIFR, 1);

} // End of Timer0_Void_Initialize_NormalMode

// Timer in Compare match Mode
extern void Timer0_Void_Initialize_CompareMatchMode(void) {

	/*
	 OCR0 : Output Compare Register
	 It counts from 0 to Number in Compare Match Mode
	 */

	// Initialize Output Compare register (OCR0)
	// 4000000         :    1 second
	// 4000000 / 256   :    1 second
	// 15625           :    1 second
	// 15625 / 200 = 78.125
	// Each 78.125 count will generate interrupt request
	OCR0 = 200;

	/*
	 TCNT0 : Timer Counter Register
	 It counts from 0 to 255 in Normal Mode
	 */

	// initialize counter to start from 0
	TCNT0 = 0;

	/*
	 TCCR0 : Timer Counter Control Register
	 TCCR0 = 0b00001101;
	 */

	// Bit 7 : FOC0 : Force Output Compare : This bit is only active when specifies a Non PWM mode
	Clr_Bit(TCCR0, 7);

	// Bit 6:3 : WGM01:0 : WaveForm generation mode
	// WGM01:0 : 10 : Timer counter works in Compare Match Mode
	Clr_Bit(TCCR0, 6);
	Set_Bit(TCCR0, 3);

	// Bit 4:5 : COM01:0 : Compare Match output mode
	// Com01:0 : 00 : Timer counter works in Normal Mode : OC0 is disconnected
	Clr_Bit(TCCR0, 4);
	Clr_Bit(TCCR0, 5);

	// Bit 2:0 : CS02:0 : Clock Select : Pre-scaler
	// CS01:0 : 100 : 256 Pre-scaler
	Set_Bit(TCCR0, 2);
	Clr_Bit(TCCR0, 1);
	Clr_Bit(TCCR0, 0);

	/*
	 TIMSK : Timer Interrupt Mask Register
	 TIMSK = 0bxxxxxx10;
	 */

	// Bit0 : TOIE0 : Timer/Counter0 Overflow interrupt Enable : Enabled in Normal  Mode only
	Clr_Bit(TIMSK, 0);

	// Bit1 : OCIE0 : Timer/Counter0 Output compare match Interrupt Enable : Enabled in Compare match Mode only
	Set_Bit(TIMSK, 1);

	/*
	 TIFR : Timer Interrupt Flag Register
	 TIFR = 0bxxxxxx10;
	 */

	// Bit0 : TOV0 : Timer/Counter0 Overflow Flag : Enabled in Normal  Mode only
	Clr_Bit(TIFR, 0);

	// Bit1 : OCF0 : Timer/Counter0 Output compare match Flag : Enabled in Compare match Mode only
	Set_Bit(TIFR, 1);

} // End of Timer0_Void_Initialize_CompareMatchMode

// Timer in PWM Mode
extern void Timer0_Void_Initialize_PWMmode() {


	/*
	 TCCR0 : Timer Counter Control Register
	 TCCR0 = 0b01110101;
	 */

	TCCR0=0b01110101;

	// Clearing older timer modes
	TIMSK=0b00000000;

	/*
		 OCR0 : Output Compare Register
		 It counts from 0 to Number in Compare Match Mode
	*/
		// Initializing the counter with 255 to start from 0
	OCR0=255;

} // End of Timer0_Void_Initialize_NormalMode


// timer 2 normal mode
extern void timer2_normal_mode_init(void){

		/* Timer initial value*/
	TCNT2 = 0;
	/* enable overflow interrupt */
	TIMSK |= (1<<TOIE2);
	/* Configure the timer control register
	 * 1. Non PWM mode FOC2=1
	 * 2. Normal Mode WGM21=0 & WGM20=0
	 * 3. Normal Mode COM20=0 & COM21=0
	 * 4. clock = F_CPU/1024 CS20=1 CS21=1 CS22=1
	 */
	TCCR2 = (1<<FOC2) | (1<<CS22) |(1<<CS21) | (1<<CS20);


}
