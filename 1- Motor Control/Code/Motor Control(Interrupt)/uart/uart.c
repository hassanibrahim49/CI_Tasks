/*
 * uart.c
 *
 *  Created on: Oct 24, 2018
 *      Author: ihass
 */

#include "../all-includes.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/* Initialization function */
extern void uart_init(void) {
	/* Enabling the BoudRate from the UBRRH and UBRRL Registers */
	/* The High register --> Like if we want to send 300 , and it is a ( 8 bit )    */
	UBRRH = 0;
	/* The Low register --> Like if we want to send 300 , and it is a ( 8 bit )    */
	UBRRL = 25;//51;
	/* Enabling the Rx, Tx and the Rx interrupt --> Data Sheet ( p.161 ) */
	UCSRB = 0b10011000;
	/* Setting the 8-bits mode from the UCSRC Register  */
	UCSRC = 0b10000110;
	/* The only thing that i need from the UCSRA Register the bit no. 6 which enabling the complete send flag  */
	UCSRA = 0;

}

/* Sending Function */
extern void uart_send_char(u8 data) {
	if (Get_Bit(UCSRA,6) != 1) {
		UDR = data;
	}
	/* Clearing Tx Flag */
	Set_Bit(UCSRA, 6);
}


