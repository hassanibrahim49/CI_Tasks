/*
 * ISR.c
 *
 *  Created on: Apr 25, 2018
 *      Author: ihass
 */

#include "../all-includes.h"
#include "avr/io.h"

u8 UART;
ISR( USART_RXC_vect) {
	UART = UDR;
}
