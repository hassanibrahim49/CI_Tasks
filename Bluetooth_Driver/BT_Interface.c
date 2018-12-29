/*
 * BT_Interface.c
 *
 *  Created on: Jul 24, 2018
 *      Author: win8
 */



#include"BT_Config.h"
#include"LCD.h"
#include<avr/delay.h>
#include<stdlib.h>
void BT_voidInit(void){
	UART_voidInit();
}

U8 BT_u8ReciveChar(void){
	return UART_u8Recive();
}

//U8* BT_u8ReciveString(void){
//	volatile char * word;
//	volatile unsigned int i = 0;
//	LCD_voidInteger(0);
//	while(1){
////		word[i] = getchar();
//		word[i] = UART_u8Recive();
//		LCD_voidDisplay(word[i]);
//		if(word[i] == '\n') break;
//		i++;
//	}
//	i--;
//	word[--i] = ' ';
//	LCD_voidInteger(sizeof (word));
////	word[i] = '\0';
////	LCD_voidString(word);
////	_delay_ms(2000);
//
//	return *word;
//
//}
void BT_voidTransmitChar(U8 const charToSend){
	UART_voidTransmit(charToSend);
}

void BT_voidTransmitString(U8* const stringToSend){

	U8 index =0;

	while(stringToSend[index] != '\0')
	{
		/* write char on LCD */
		UART_voidTransmit(stringToSend[index]);

		/* next char */
		index++;

	}	/* end While */
}
