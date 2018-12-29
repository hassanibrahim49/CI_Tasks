/*
 * LCD Driver header file
 * LCD.h
 *
 *  Created on: Sep 8, 2017
 *      Author: Asmer Amen
 */

#ifndef LCD_H_
#define LCD_H_


/* Text replacements of the LCD pins */
#define LCD_RS  DIO_u8PinA0
#define LCD_RW  DIO_u8PinA1
#define LCD_E	DIO_u8PinA2


/* Function Prototypes */
extern void LCD_voidInit(void);
extern void LCD_voidWriteCommand(U8 command);
extern void LCD_voidDisplay(U8 data);
extern void LCD_voidString(U8* const stringToPrint);
extern void LCD_voidInteger(S32 const IntegerToPrint);
extern void LCD_voidClear();
#endif /* LCD_H_ */
