/*
 * External_Interupt.c
 *
 *  Created on: Apr 25, 2018
 *      Author: ihass
 */

#include "avr/io.h"
#include "../all-includes.h"

// A function that Enables the interrupt Registers
void ExternalInterrupt_voidInitialzie() {

	/*
	 GICR : General Interrupt Control Register
	 Bits 7:5 : External interrupts requests
	 */

	// Bit 7 : INT1 : External interrupts request 1
	// Bit 6 : INT0 : External interrupts request 0
	// Bit 5 : INT2 : External interrupts request 2
	Set_Bit(GICR, 6);

	/*
	 MCUCR : MCU Control Register
	 Bits 0:3 : Interrupt sense Control
	 */

	// Bits 0:1 : INT0 : 11 : The rising edge of INT0 generates an interrupt request
	Set_Bit(MCUCR, 0);
	Set_Bit(MCUCR, 1);

	// Bits 2:3 : INT1 : 01 : Any logical change on INT1 generates an interrupt request
	//	Clr_Bit(MCUCR, 2);
	//	Set_Bit(MCUCR, 3);

	/*
	 SREG : status Register
	 */

	// Enabling Global Interrupt
	Set_Bit(SREG, 7);

}

// Enabling Global interrupt flag
void Sei() {
	/*
	 SREG : status Register
	 */
	// Enabling Global Interrupt
	Set_Bit(SREG, 7);

}

// Disabling Global interrupt flag
void Cli() {
	/*
	 SREG : status Register
	 */
	// Enabling Global Interrupt
	Clr_Bit(SREG, 7);

}
