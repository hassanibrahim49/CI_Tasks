/*
 * UART_Interface.c
 *
 *  Created on: Oct 7, 2017
 *      Author: Asmer Amen
 */
#include "UART_Conf.h"
#include "utilss.h"
#include "Types.h"
#include "DIO.h"

void UART_voidInit()
{

	DIO_voidSetPinDirection(DIO_u8PinD0, DIO_u8PinIp);	//	Rx
	DIO_voidSetPinDirection(DIO_u8PinD1, DIO_u8PinOp);	//	Tx
/*
	UCSRA |=0b00000010;
    UCSRB = 0b00011000;
    UCSRC = 0b10000110;
    UBRRL = 103;
    UBRRH&=0b01110000;
*/


	UCSRA |= (RXC<<7) | (TXC<<6) | (UDRE<<5) |  (FE<<4) | (DOR<<3) | (PE<<2) | (U2X<<1) | (MPCM<<0);
//	UCSRA |= (PE<<2) | (U2X<<1) | (MPCM<<0);
	UCSRB |= (RXCIE<<7) | (TXCIE<<6) | (UDRIE<<5) |  (RXEN<<4) | (TXEN<<3) | (UCSZ2<<2) | (RXB8<<1) | (TXB8<<0);
	//	UCSRC
	UCSRC_UBRRH |= (URSEL_C<<7) | (UMSEL<<6) | (UPM1<<5) |  (UPM0<<4) | (USBS<<3) | (UCSZ1<<2) | (UCSZ0<<1) | (UCPOL<<0);
	//	UBRR
	UCSRC_UBRRH |= (URSEL_BR<<7)| (UBRR11<<3) | (UBRR10<<2) | (UBRR9<<1) | (UBRR8<<0);
	UBRRL = 103;

	#ifdef INTERRUPT
		set_bit(SREG, 7);
	#endif

}


U8 UART_u8Recive(void)
{
//	while(get_bit(UCSRA, 7) ==0);
	while((UCSRA&0b10000000)==0);
	return UDR;
}

void UART_voidTransmit(U8 const data)
{
	UDR = data;
	while(get_bit(UCSRA, 5)==0);
}
