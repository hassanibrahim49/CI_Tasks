/*
 * ATmega32_Register.h
 *
 *  Created on: Jul 24, 2018
 *      Author: win8
 */

#ifndef ATMEGA32_REGISTERS_H_
#define ATMEGA32_REGISTERS_H_


/*
 * DIO Registers
 */

#define DDRA *((U8*)0x3A) // casted
#define PINA *((U8*)0x39)
#define PORTA *((U8*)0x3B)

#define DDRB *((U8*)0x37)
#define PINB *((U8*)0x36)
#define PORTB *((U8*)0x38)

#define DDRC *((U8*)0x34)
#define PINC *((U8*)0x33)
#define PORTC *((U8*)0x35)

#define DDRD *((U8*)0x31)
#define PIND *((U8*)0x30)
#define PORTD *((U8*)0x32)


/*
 * Interrupt Registers
 */
#define SREG		*((U8*) 0x5F)		//Status Register

/*
 * UART Registers
 */
#define UCSRA		*((U8*)0x2B)
#define UCSRB 		*((U8*)0x2A)
#define UCSRC_UBRRH	*((U8*)0x40)
#define UDR			*((U8*)0x2C)
#define UBRRL 		*((U8*)0x29)


/*
 * SPI Registers
*/

#define SPCR	*((U8*)0x2D)
#define SPSR	*((U8*)0x2E)
#define SPDR	*((U8*)0x2F)


#endif /* ATMEGA32_REGISTERS_H_ */
