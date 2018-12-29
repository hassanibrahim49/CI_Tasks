/*
 * LCD Driver source code.
 * LCD.c
 *
 *  Created on: Sep 8, 2017
 *      Author: Asmer Amen
 */

#include <avr/delay.h>

#include "Types.h"
#include "utilss.h"
#include "DIO.h"
#include "LCD.h"

#include <stdlib.h>

extern void LCD_voidInit(void)
{
	// Control Pins:
	/* RS: A0, R\W: A1, E: A2 */
	DIO_voidSetPinDirection(LCD_RS, DIO_u8PinOp);
	DIO_voidSetPinDirection(LCD_RW, DIO_u8PinOp);
	DIO_voidSetPinDirection(LCD_E, DIO_u8PinOp);

	// Data Pins:
	/* Connected to Port D */
	DIO_voidSetPortDirection('C', DIO_u8PortOp);

	_delay_ms(50);
		/* review the datasheet for re-configuration */

	/* Display Clear */
	LCD_voidWriteCommand(0b00000001);
	_delay_ms(10);

	/* Return Home  */
	LCD_voidWriteCommand(0b00000010);
	_delay_ms(10);

	/*Entry Mode Set */
	LCD_voidWriteCommand(0b00000110);
	_delay_ms(10);

	/* Display ON OFF Control, crusor 0n */
	LCD_voidWriteCommand(0b00001110);
	_delay_ms(10);

	/* Function Set  */
	LCD_voidWriteCommand(0b00111000);
	_delay_ms(10);


} /* end of function LCD_voidInit */


extern void LCD_voidWriteCommand(U8 command)
{
		/*  RS -> 0, to command */
	DIO_voidWritePin(LCD_RS,DIO_u8Low);

		/* RW -> 0, to write */
	DIO_voidWritePin(LCD_RW,DIO_u8Low);

		/* Read the command */
	DIO_voidWritePort('C', command);
	//	PORTD = command;

		/* Enable */
	DIO_voidWritePin(LCD_E,DIO_u8High);
	_delay_ms(2); // 2 ms to excute.
	DIO_voidWritePin(LCD_E,DIO_u8Low);


}/* end of function LCD_voidWriteCommand */


extern void LCD_voidDisplay(U8 data)
{
		/*  RS -> 1, to Display Data */
	DIO_voidWritePin(LCD_RS,DIO_u8High);

		/* RW -> 0, to write */
	DIO_voidWritePin(LCD_RW,DIO_u8Low);

		/* Enable */
	DIO_voidWritePin(LCD_E,DIO_u8High);

		/* Read the command */
	DIO_voidWritePort('C', data);


	_delay_ms(2); // 2 ms to excute.
	DIO_voidWritePin(LCD_E,DIO_u8Low);
	_delay_ms(5);

}/* end of function LCD_voidDisplay */

extern void LCD_voidString(U8* const stringToPrint)
{
	U8 index =0;

	while(stringToPrint[index] != '\0')
	{
		/* write char on LCD */
		LCD_voidDisplay(stringToPrint[index]);

		/* next char */
		index++;

		_delay_ms(2);
	}	/* end While */
}/* end of function LCD_voidDisplay */

extern void LCD_voidInteger(S32 const IntegerToPrint)
{
	U8 intToStr[3];
	itoa(IntegerToPrint, intToStr, 10); //convert decimal integer to string
	LCD_voidString(intToStr);
	_delay_ms(2);

}/* end of function LCD_voidDisplay */

extern void LCD_voidClear()
{
	/* Display Clear */
	LCD_voidWriteCommand(0b00000001);
	_delay_ms(10);
}/* end of function LCD_voidClear */
