/*


 * DIO.h
 *  Created on: Aug 4, 2017
 *      Author: ihass
 */

#ifndef DIO_DEFENTIONS_H_
#define DIO_DEFENTIONS_H_

#include "../all-includes.h"

/* Set Pin Direction Function (DDR) Register */
extern void DIO_Void_SetPinDirection(u8 u8PinNumber, u8 u8PinDirection);

/* Set Pin Direction Function (PORT) Register  */
extern void DIO_Void_WritePin(u8 u8PinNumber, u8 u8PinValue);

/* Set Pin Direction Function (PORT) Register, In HIGH Nibble */
extern void DIO_Void_WriteHighNibble(u8 u8PinNumber, u8 u8PinValue);

/* Set Pin Direction Function (PORT) Register, In LOW Nibble */
extern void DIO_Void_WriteLowNibble(u8 u8PinNumber, u8 u8PinValue);

/* Read pin function */
extern u8 DIO_ReadPin(u8 u8PinNumber);

#endif /* DIO_DEFENTIONS_H_ */
