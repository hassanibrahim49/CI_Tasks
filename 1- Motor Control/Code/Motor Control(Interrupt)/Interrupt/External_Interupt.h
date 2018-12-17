/*


 * External_Interupt.h
 *  Created on: Aug 4, 2017
 *      Author: ihass
 */

#ifndef External_Interupt_DEFENTIONS_H_
#define External_Interupt_DEFENTIONS_H_

#include "../all-includes.h"

/*PINA is the definition of the INPUT Pins*/
//#define SREG *((u8 volatile*)(0x3F))

// A function that Enables the interrupt Registers
void ExternalInterrupt_voidInitialzie();

// Enabling Global interrupt flag
void Sei();

// Disabling Global interrupt flag
void Cli();

#endif /* External_Interupt_DEFENTIONS_H_ */
