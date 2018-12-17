/*This C file has the detailed  declarations of the functions */

/* Including all the files that have the Declarations */
#include "../all-includes.h"


/* This function is to check if the pin is INPUT or OUTPUT
 * So i need to know two things :
 * 1- What #Pin will be set ? --> So i defined (u8PinNumber) Variable
 * 2- What #Direction will be set (OUTPUT or INPUT) ? -->  So i defined (u8PinDirection) Variable   */
extern void DIO_Void_SetPinDirection ( u8 u8PinNumber  , u8 u8PinDirection )
{
	u8 Port,Pin;
	Port = u8PinNumber /8 ;
	Pin  = u8PinNumber %8 ;
	if (Port == 0)
	{
		Assign_Bit(DDRA,Pin,u8PinDirection);
	}

	else if (Port == 1)
	{
		Assign_Bit(DDRB,Pin,u8PinDirection);
	}

	else if (Port == 2)
	{
		Assign_Bit(DDRC,Pin,u8PinDirection);
	}

	else if (Port == 3)
	{
		Assign_Bit(DDRD,Pin,u8PinDirection);
	}

}

/* If the function was OUTPUT, Then i need to know two things :
 * 1- What #Pin will be set as OUTPUT ? --> So i defined (u8PinNumber) Variable
 * 2- What #Value will be set as OUTPUT (0V or 5V) ? -->  So i defined (u8PinValue) Variable */
extern void DIO_Void_WritePin ( u8 u8PinNumber , u8 u8PinValue )
{
	u8 Port,Pin;
	Port = u8PinNumber /8 ;
	Pin  = u8PinNumber %8 ;
	if (Port == 0)
	{
		Assign_Bit(PORTA,Pin,u8PinValue);
	}

	else if (Port == 1)
	{
		Assign_Bit(PORTB,Pin,u8PinValue);
	}

	else if (Port == 2)
	{
		Assign_Bit(PORTC,Pin,u8PinValue);
	}

	else if (Port == 3)
	{
		Assign_Bit(PORTD,Pin,u8PinValue);
	}

}

/* To set the High Nibble of a Port */
extern void DIO_Void_WriteHighNibble ( u8 Port , u8 u8PinValue )
{
//	u8 Port,Pin;
//	Port = u8PinNumber /8 ;
//	Pin  = u8PinNumber %8 ;
	if (Port == 0)
	{
		Assign_High_Nibble(PORTA,u8PinValue);
	}

	else if (Port == 1)
	{
		Assign_High_Nibble(PORTB,u8PinValue);
	}

	else if (Port == 2)
	{
		Assign_High_Nibble(PORTC,u8PinValue);
	}

	else if (Port == 3)
	{
		Assign_High_Nibble(PORTD,u8PinValue);
	}

}


/* To set the Low Nibble of a Port */
extern void DIO_Void_WriteLowNibble ( u8 Port , u8 u8PinValue )
{
//	u8 Port,Pin;
//	Port = u8PinNumber /8 ;
//	Pin  = u8PinNumber %8 ;
	if (Port == 0)
	{
		Assign_Low_Nibble(PORTA,u8PinValue);
	}

	else if (Port == 1)
	{
		Assign_Low_Nibble(PORTB,u8PinValue);
	}

	else if (Port == 2)
	{
		Assign_Low_Nibble(PORTC,u8PinValue);
	}

	else if (Port == 3)
	{
		Assign_Low_Nibble(PORTD,u8PinValue);
	}

}

/* If the function was INPUT, Then i just need to know one thing :
 * #The number of Pin That i will read from it --> So i defined (u8PinNumber) Variable */
extern u8  DIO_ReadPin ( u8 u8PinNumber )
{
	u8 Port, Pin, x;
	Port = u8PinNumber /8 ;
	Pin  = u8PinNumber %8 ;

	if (Port == 0)
	{
		x= Get_Bit(PINA,Pin);
	}

	else if (Port == 1)
	{
		x= Get_Bit(PINB,Pin);
	}

	else if (Port == 2)
	{
		x= Get_Bit(PINC,Pin);
	}

	else if (Port == 3)
	{
		x= Get_Bit(PIND,Pin);
	}

	return x;

}
