/*
 * DIO.h
 *	AVR Digital Input Output, self-written library headerfile
 *  Created on: Aug 26, 2017
 *      Author: Asmer Amen
 */

#include"Types.h"

#ifndef DIO_H_
#define DIO_H_

#include "ATmega32_Registers.h"

/*
 * Prototypes of implemented functions
 */
		//	Pins
extern void DIO_voidSetPinDirection(U8 DIO_u8LocalPinToSet, U8 DIO_u8DIOLocalDirection);
extern void DIO_voidWritePin(U8 DIO_u8LocalPinToSet, U8 DIO_u8DIOLocalValue);
extern U8 DIO_u8ReadPin(U8 DIO_u8LocalPintToRead);
		//	Ports
extern void DIO_voidSetPortDirection(U8 DIO_u8LocalPortToSet, U8 DIO_u8DIOLocalDirection);
extern void DIO_voidWritePort(U8 DIO_u8LocalPortToSet, U8 DIO_u8ValueToSet);
extern U8 DIO_u8ReadPort(U8 DIO_u8LocalPortToRead);
		//	Nibbles
extern void DIO_voidSetLowerNibbleDirection(U8 DIO_u8LocalPortToSet, U8 DIO_u8DIOLowerNibbleDirection);
extern void DIO_voidSetUpperNibbleDirection(U8 DIO_u8LocalPortToSet, U8 DIO_u8DIOUpperNibbleDirection);
extern void DIO_voidWriteLowerNibble(U8 DIO_u8LocalPortToSet, U8 DIO_u8ValueToSet);
extern void DIO_voidWriteUpperNibble(U8 DIO_u8LocalPortToSet, U8 DIO_u8ValueToSet);
extern U8 DIO_u8ReadLowerNibble(U8 DIO_u8LocalPortToRead);
extern U8 DIO_u8ReadUpperNibble(U8 DIO_u8LocalPortToRead);


/* define pin output or input */
enum PIN_MODE{
DIO_u8PinIp,
DIO_u8PinOp
};

enum PORT_MODE{
DIO_u8PortIp,
DIO_u8PortOp
};

enum PIN_STATE{
	DIO_u8Low,
	DIO_u8High
};

	/* Pin codes from 0 -> 31  */
enum PIN_Code{
/* Port A */
 DIO_u8PinA0,
 DIO_u8PinA1,
 DIO_u8PinA2,
 DIO_u8PinA3,
 DIO_u8PinA4,
 DIO_u8PinA5,
 DIO_u8PinA6,
 DIO_u8PinA7,

 /* Port B */
 DIO_u8PinB0,
 DIO_u8PinB1,
 DIO_u8PinB2,
 DIO_u8PinB3,
 DIO_u8PinB4,
 DIO_u8PinB5,
 DIO_u8PinB6,
 DIO_u8PinB7,

 /* Port C */
 DIO_u8PinC0,
 DIO_u8PinC1,
 DIO_u8PinC2,
 DIO_u8PinC3,
 DIO_u8PinC4,
 DIO_u8PinC5,
 DIO_u8PinC6,
 DIO_u8PinC7,

 /* Port D */
 DIO_u8PinD0,
 DIO_u8PinD1,
 DIO_u8PinD2,
 DIO_u8PinD3,
 DIO_u8PinD4,
 DIO_u8PinD5,
 DIO_u8PinD6,
 DIO_u8PinD7,
};

#endif /* DIO_H_ */
