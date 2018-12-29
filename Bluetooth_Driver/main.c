// Service Layer
#include "utilss.h"
#include "Types.h"
#include <avr/delay.h>
#define F_CPU 8000000

// MCAL Layer

//#include "DIO.h"
#include <avr/interrupt.h>

// HAL Layer
#include "LCD.h"
#include "BT_Config.h"
/*
 *
14 $01A USART, RXC USART, Rx Complete
15 $01C USART, UDRE USART Data Register Empty
16 $01E USART, TXC USART, Tx Complete
*/



volatile U8 Rvalue;
U8 (*recieve)() = BT_u8ReciveChar;
/* RXC ISR	*/
ISR(USART_RXC_vect)
{

	Rvalue = (*recieve)();
	LCD_voidClear();
	LCD_voidDisplay(Rvalue);
	_delay_ms(1000);
}

ISR(_VECTOR(14))
{
	LCD_voidInteger(9);
	_delay_ms(1000);
}

ISR(_VECTOR(15))
{
	LCD_voidInteger(8);
	_delay_ms(1000);
}


int main(void)
{

	BT_voidInit();
	LCD_voidInit();
	LCD_voidInteger(1);

	while(1)
	{
		LCD_voidInteger(3);
		BT_voidTransmitString("ASMER ");
		LCD_voidInteger(4);

		_delay_ms(2000);

	}


	return 0;
}
