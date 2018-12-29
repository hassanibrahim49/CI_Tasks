/*
 * UART_Conf.h
 *
 *  Created on: Oct 7, 2017
 *      Author: Asmer Amen
 */

#ifndef UART_CONF_H_
#define UART_CONF_H_

#include "Types.h"
#include "ATmega32_Registers.h"

//	#define POLLING
	#define INTERRUPT



/*
 * 		UCSRA Register
 * 		USART Control and Status Register A
 *
 * 		Bit7 - Bit2: Flags
 * 		RXC: USART Receive Complete
 * 		TXC: USART Transmit Complete
 * 		UDRE: USART Data Register Empty
 * 		FE: Frame Error
 * 		DOR: Data OverRun
 * 		PE: Parity Error
 *
 * 		Bit 1 – U2X: Double the USART Transmission Speed.
 * 		Only asynch. operations,
 * 		1 - > reduce the baud rate from 16 to 8, doubling the transfer rate.
 *
 *		Bit 0 – MPCM: Multi-processor Communication Mode
 *		1 -> all the incoming frames received by the USART receiver
 *		that do not contain address information will be ignored.
 */


// UCSRA |=0b00000010;
#define RXC		0
#define	TXC		0
#define	UDRE	0
#define	FE		0
#define	DOR		0
#define	PE		0
#define	U2X		1
#define MPCM	0


/*
 * 		UCSRB Register
 * 		USART Control and Status Register B
 *
 * 		Bit 7 – RXCIE: RX Complete Interrupt Enable
 * 		Bit 6 – TXCIE: TX Complete Interrupt Enable
 * 		Bit 5 – UDRIE: USART Data Register Empty Interrupt Enable
 * 		Bit 4 – RXEN: Receiver Enable
 * 		Bit 3 – TXEN: Transmitter Enable
 * 		Bit 2 – UCSZ2: Character Size
 * 		Bit 1 – RXB8: Receive Data Bit 8
 * 		Bit 0 – TXB8: Transmit Data Bit 8
 *
 */
#ifdef POLLING

#define RXCIE	0
#define TXCIE	0
#define UDRIE	0
#define RXEN	1
#define TXEN	1
#define UCSZ2	0
#define RXB8	0
#define TXB8	0

#endif

#ifdef INTERRUPT

#define RXCIE	1
#define TXCIE	1	//edited
#define UDRIE	0	//edited
#define RXEN	1
#define TXEN	1
#define UCSZ2	0
#define RXB8	0
#define TXB8	0

#endif

/*
 * 		UCSRC Register
 * 		USART Control and Status Register C
 */

#ifdef POLLING

#define	URSEL_C	1
#define	UMSEL	0
#define	UPM1	0
#define	UPM0	0
#define	USBS	0
#define	UCSZ1	1
#define	UCSZ0	1
#define	UCPOL	0

#endif

#ifdef INTERRUPT

#define	URSEL_C	1
#define	UMSEL	0
#define	UPM1	0
#define	UPM0	0
#define	USBS	0
#define	UCSZ1	1
#define	UCSZ0	1
#define	UCPOL	0

#endif

/*
 * 		UBRRL & UBRRH
 * 		USART Baud Rate Register
 */

#ifdef POLLING

#define	URSEL_BR	0	//Bit15

// 103 => 9600
#define UBRR11		0	//Bit11
#define UBRR10		0	//Bit10
#define UBRR9		0	//Bit9
#define UBRR8		0	//Bit8
#define UBRR7		0	//Bit7
#define UBRR6		1	//Bit6
#define UBRR5		1	//Bit5
#define UBRR4		0	//Bit4
#define UBRR3		0	//Bit3
#define UBRR2		1	//Bit2
#define UBRR1		1	//Bit1
#define UBRR0		1	//Bit0

#endif

#ifdef INTERRUPT

#define	URSEL_BR	0	//Bit7		//Bit15

// 103 => 9600
#define UBRR11		0	//Bit3		//Bit11
#define UBRR10		0	//Bit2		//Bit10
#define UBRR9		0	//Bit1		//Bit9
#define UBRR8		0	//Bit0		//Bit8

#define UBRR7		0	//Bit7
#define UBRR6		1	//Bit6
#define UBRR5		1	//Bit5
#define UBRR4		0	//Bit4
#define UBRR3		0	//Bit3
#define UBRR2		1	//Bit2
#define UBRR1		1	//Bit1
#define UBRR0		1	//Bit0

#endif

/* Prototypes	*/

extern void UART_voidInit();
extern U8 UART_u8Recive();
extern void UART_voidTransmit(U8 const data);


#endif /* UART_CONF_H_ */
