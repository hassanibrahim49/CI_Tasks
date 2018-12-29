/*
 * USART_Master.h
 *
 * Created: 10/30/2018 6:38:49 PM
 *  Author: deel1
 */ 

#include <avr/io.h>
#include "USART_Master.h"
void USART_Init( unsigned int ubrr)
{
	/*Set baud rate */
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	//Enable receiver and transmitter 
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
}

void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) );
	/* Put data into buffer, sends the data */
	UDR = data;
}
unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) );
	/* Get and return received data from buffer */
	return UDR;
}

unsigned char UART ;


void ISR (USART_RXC_vect){
	UART = UDR ;	
	Mode = (UDR & 1) ;
	Timer_interval = (UDR & (0b01110000));
	Motor_speed = (UDR & (0b00001110));
}