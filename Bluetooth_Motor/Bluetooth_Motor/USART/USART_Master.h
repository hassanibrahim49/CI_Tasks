/*
 * USART_Master.h
 *
 * Created: 10/30/2018 6:38:07 PM
 *  Author: deel1
 */ 


#ifndef USART_MASTER_H_
#define USART_MASTER_H_


#define FOSC 1843200 // Clock Speed
#define BAUD 9600
#define MYUBRR (FOSC/(16*BAUD) ) - 1

unsigned char Mode ;
unsigned char Timer_interval ;
unsigned char Motor_speed ;

void USART_Init( unsigned int ubrr);
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );


#endif /* USART_MASTER_H_ */
