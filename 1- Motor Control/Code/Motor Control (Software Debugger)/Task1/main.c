/*
 * Task1.c
 *
 * Created: 10/21/2018 6:16:18 PM
 * Author : WRL
 */ 

#define F_CPU 8000000UL		// 8 MHz
#define BAUD_RATE 9600

#include <avr/io.h>
#include <avr/interrupt.h>
#include "softwaredebugger.h"

int main(void)
{
	//DDRB=0b11111111; // ensure that Pin3 in POrt B is output as this is the OC0 pin that wll produce the PWM.		37hex=55 portb 38hex=56
	//TCCR0=0b01110101; //Configure TCCR0 as explained in the article												53hex=83
	//TIMSK=0b00000000; //																							59hex=89
	//OCR0=255; // Set OCR0 to 255 so that the duty cycle is initially 0 and the motor is not rotating				5chex=92
	
	/*
		For motor speed control
		>@W55255;					DDRB=0b11111111
		>@W83117;					TCCR0=0b01110101
		>@W89000;					TIMSK=0b00000000
		>@W92000;					OCR0=0						FOR MAX SPEED
		>@W92255;					OCR0=255						FOR MIN SPEED
	*/
	
	SDEBUG_Init();

	sei();

	while(1)
	{
		SDEBUG_MainFunction();
	}
	return 0;
}
