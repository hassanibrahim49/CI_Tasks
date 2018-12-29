/*
 * BT_Config.h
 *
 *  Created on: Jul 24, 2018
 *      Author: Asmer Amen
 */

#ifndef BT_CONFIG_H_
#define BT_CONFIG_H_

#include "UART_Conf.h"	//make sure Interrupt is defined


extern void BT_voidInit();

extern U8 BT_u8ReciveChar();
//extern U8* BT_u8ReciveString(void);

extern void BT_voidTransmitChar(U8 const charToSend);
extern void BT_voidTransmitString(U8* const stringToSend);



#endif /* BT_CONFIG_H_ */
