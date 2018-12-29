/*
 * DIO.c
 *		AVR Digital Input Output, self-written library
 *  Created on: Aug 26, 2017
 *      Author: Asmer Amen
 */
#include "DIO.h"
#include"utilss.h"

/*
 *  States the Direction of the PIN: INPUT/OUTPUT
 */
extern void DIO_voidSetPinDirection(U8 DIO_u8LocalPinToSet, U8 DIO_u8DIOLocalDirection)
{
	if((DIO_u8LocalPinToSet>=0 && DIO_u8LocalPinToSet<=31) && (DIO_u8DIOLocalDirection==0 || DIO_u8DIOLocalDirection==1))
	{
		if( (DIO_u8LocalPinToSet / 8) == 0)
		{
			assign_bit(DDRA, (DIO_u8LocalPinToSet %8), DIO_u8DIOLocalDirection);
		}
		else if ( (DIO_u8LocalPinToSet / 8) == 1)
		{
			assign_bit(DDRB, (DIO_u8LocalPinToSet %8), DIO_u8DIOLocalDirection);
		}
		else if ( (DIO_u8LocalPinToSet / 8) == 2)
		{
			assign_bit(DDRC, (DIO_u8LocalPinToSet %8), DIO_u8DIOLocalDirection);
		}
		else if ( (DIO_u8LocalPinToSet / 8) == 3)
		{
			assign_bit(DDRD, (DIO_u8LocalPinToSet %8), DIO_u8DIOLocalDirection);
		}
	} /* end if */
} /*end function */

/*
 *  States the Value of the PIN: HIGH/LOW
 */
extern void DIO_voidWritePin(U8 DIO_u8LocalPinToSet, U8 DIO_u8DIOLocalValue)
{
	if((DIO_u8LocalPinToSet>=0 && DIO_u8LocalPinToSet<=31) && (DIO_u8DIOLocalValue==0 || DIO_u8DIOLocalValue==1))
	{
		if( (DIO_u8LocalPinToSet / 8) == 0)
		{
			assign_bit(PORTA, (DIO_u8LocalPinToSet % 8), DIO_u8DIOLocalValue);
		}
		else if ( (DIO_u8LocalPinToSet / 8) == 1)
		{
			assign_bit(PORTB, (DIO_u8LocalPinToSet % 8), DIO_u8DIOLocalValue);
		}
		else if ( (DIO_u8LocalPinToSet / 8) == 2)
		{
			assign_bit(PORTC, (DIO_u8LocalPinToSet % 8), DIO_u8DIOLocalValue);
		}
		else if ( (DIO_u8LocalPinToSet / 8) == 3)
		{
			assign_bit(PORTD, (DIO_u8LocalPinToSet %8), DIO_u8DIOLocalValue);
		}
	}/* end if */
}/* end function */


/*
 *  Reads the Value of the PIN: HIGH/LOW
 */
extern U8 DIO_u8ReadPin(U8 DIO_u8LocalPintToRead)
{
	U8 DIO_u8DataToBeRead;
	if((DIO_u8LocalPintToRead>=0) && (DIO_u8LocalPintToRead<=31))
	{
		if( (DIO_u8LocalPintToRead/8) == 0)
		{
			DIO_u8DataToBeRead = get_bit(PINA,(DIO_u8LocalPintToRead%8) );
		}
		else if((DIO_u8LocalPintToRead/8) == 1)
		{
			DIO_u8DataToBeRead = get_bit(PINB,(DIO_u8LocalPintToRead%8) );
		}
		else if((DIO_u8LocalPintToRead/8) == 2)
		{
			DIO_u8DataToBeRead = get_bit(PINC,(DIO_u8LocalPintToRead%8) );
		}
		else if((DIO_u8LocalPintToRead/8) == 3)
		{
			DIO_u8DataToBeRead = get_bit(PIND,(DIO_u8LocalPintToRead%8) );
		}
	}
	return DIO_u8DataToBeRead;
} /*end function */


/*
 *  States the Direction of the Port: INPUT/OUTPUT
 */
extern void DIO_voidSetPortDirection(U8 DIO_u8LocalPortToSet, U8 DIO_u8DIOLocalDirection)
{
	/* declare Port A as Output */
	if(DIO_u8LocalPortToSet == 'A')
	{
		if(DIO_u8DIOLocalDirection == DIO_u8PinOp)
		{
		DDRA = 0xFF;
		}
		else if(DIO_u8DIOLocalDirection == DIO_u8PinIp)
		{
		DDRA = 0x00;
		}
	}


	/* declare Port B as Output */
	if(DIO_u8LocalPortToSet == 'B')
	{
		if(DIO_u8DIOLocalDirection == DIO_u8PinOp)
		{
			DDRB = 0xFF;
		}
		else if(DIO_u8DIOLocalDirection == DIO_u8PinIp)
		{
			DDRB = 0x00;
		}
	}/* end Port B assigning */

	/* declare Port C as Output */
	if(DIO_u8LocalPortToSet == 'C')
	{
		if(DIO_u8DIOLocalDirection == DIO_u8PinOp)
		{
			DDRC = 0xFF;
		}
		else if(DIO_u8DIOLocalDirection == DIO_u8PinIp)
		{
			DDRC = 0x00;
		}
	} /* end Port C assigning */

	/* declare Port D as Output */
	if(DIO_u8LocalPortToSet == 'D')
	{
		if(DIO_u8DIOLocalDirection == DIO_u8PinOp)
		{
			DDRD = 0xFF;
		}
		else if(DIO_u8DIOLocalDirection == DIO_u8PinIp)
		{
			DDRD = 0x00;
		}
	}/* end Port C assigning */
} /* end DIO_voidSetPortDirection Function */


/*
 *  States the Value of the Port: HIGH/LOW
 */
extern void DIO_voidWritePort(U8 DIO_u8LocalPortToSet, U8 DIO_u8ValueToSet)
{
	/* Assign Port A with value */
	if(DIO_u8LocalPortToSet == 'A')
	{
			PORTA = DIO_u8ValueToSet;
	}

	/* Assign Port A with value */
	if(DIO_u8LocalPortToSet == 'B')
	{
		PORTB = DIO_u8ValueToSet;
	}

	/* Assign Port A with value */
	if(DIO_u8LocalPortToSet == 'C')
	{
		PORTC = DIO_u8ValueToSet;
	}

	/* Assign Port A with value */
	if(DIO_u8LocalPortToSet == 'D')
	{
		PORTD = DIO_u8ValueToSet;
	}
}/* end DIO_voidWritePort Function */



/*
 *  Reads the Value of the Port: HIGH/LOW
 */
extern U8 DIO_u8ReadPort(U8 DIO_u8LocalPortToRead)
{
	U8 DIO_u8DataToBeRead;

	if( DIO_u8LocalPortToRead == 'A')
	{
		DIO_u8DataToBeRead = PINA;
	}
	else if(DIO_u8LocalPortToRead == 'B')
	{
		DIO_u8DataToBeRead = PINB;
	}
	else if(DIO_u8LocalPortToRead == 'C')
	{
		DIO_u8DataToBeRead = PINC;
	}
	else if(DIO_u8LocalPortToRead == 'D')
	{
		DIO_u8DataToBeRead = PIND;
	}

	return DIO_u8DataToBeRead;
} /*end DIO_u8ReadPOrt function */



/*
 *  States the Direction of the Lower nibbles : OUTPUT or INPUT
 */
extern void DIO_voidSetLowerNibbleDirection(U8 DIO_u8LocalPortToSet, U8 DIO_u8DIOLowerNibbleDirection)
{	/* declare nibbles of Port A */
	if(DIO_u8LocalPortToSet == 'A')
	{
		assign_nibbleLow(DDRA ,DIO_u8DIOLowerNibbleDirection);
	}/* end Port A assigning */

	/* declare nibbles of Port B */
	if(DIO_u8LocalPortToSet == 'B')
	{
		assign_nibbleLow(DDRB ,DIO_u8DIOLowerNibbleDirection);
	}/* end Port B assigning */

	/* declare nibbles of Port C */
	if(DIO_u8LocalPortToSet == 'C')
	{
		assign_nibbleLow(DDRC ,DIO_u8DIOLowerNibbleDirection);
	} /* end Port C assigning */

	/* declare nibbles of Port D */
	if(DIO_u8LocalPortToSet == 'D')
	{
		assign_nibbleLow(DDRD,DIO_u8DIOLowerNibbleDirection);
	}/* end Port C assigning */
} /* end DIO_voidSetNibblesOfPortDirection Function */


/*
 *  States the Direction of the Upper nibbles : OUTPUT or INPUT
 */
extern void DIO_voidSetUpperNibbleDirection(U8 DIO_u8LocalPortToSet, U8 DIO_u8DIOUpperNibbleDirection)
{
	/* declare nibbles of Port A */
	if(DIO_u8LocalPortToSet == 'A')
	{
		assign_nibbleHigh(DDRA ,DIO_u8DIOUpperNibbleDirection);
	}/* end Port A assigning */

	/* declare nibbles of Port B */
	if(DIO_u8LocalPortToSet == 'B')
	{
		assign_nibbleHigh(DDRB ,DIO_u8DIOUpperNibbleDirection);
	}/* end Port B assigning */

	/* declare nibbles of Port C */
	if(DIO_u8LocalPortToSet == 'C')
	{
		assign_nibbleHigh(DDRC ,DIO_u8DIOUpperNibbleDirection);
	} /* end Port C assigning */

	/* declare nibbles of Port D */
	if(DIO_u8LocalPortToSet == 'D')
	{
		assign_nibbleHigh(DDRD,DIO_u8DIOUpperNibbleDirection);
	}/* end Port C assigning */
} /* end DIO_voidSetNibblesOfPortDirection Function */


/*
 *  States the Value of the lower nibble of Port: HIGH/LOW
 */
extern void DIO_voidWriteLowerNibble(U8 DIO_u8LocalPortToSet, U8 DIO_u8ValueToSet)
{
	/* Assign Port A with value */
	if(DIO_u8LocalPortToSet == 'A')
	{
		assign_nibbleLow(PORTA,DIO_u8ValueToSet);
	}

	/* Assign Port B with value */
	if(DIO_u8LocalPortToSet == 'B')
	{
		assign_nibbleLow(PORTB,DIO_u8ValueToSet);
	}

	/* Assign Port C with value */
	if(DIO_u8LocalPortToSet == 'C')
	{
		assign_nibbleLow(PORTC,DIO_u8ValueToSet);
	}

	/* Assign Port D with value */
	if(DIO_u8LocalPortToSet == 'D')
	{
		assign_nibbleLow(PORTD,DIO_u8ValueToSet);
	}
}/* end DIO_voidWriteLowerNibble Function */


/*
 *  States the Value of the upper nibble of Port: HIGH/LOW
 */
extern void DIO_voidWriteUpperNibble(U8 DIO_u8LocalPortToSet, U8 DIO_u8ValueToSet)
{
	/* Assign Port A with value */
	if(DIO_u8LocalPortToSet == 'A')
	{
		assign_nibbleHigh(PORTA,DIO_u8ValueToSet);
	}

	/* Assign Port B with value */
	if(DIO_u8LocalPortToSet == 'B')
	{
		assign_nibbleHigh(PORTB,DIO_u8ValueToSet);
	}

	/* Assign Port C with value */
	if(DIO_u8LocalPortToSet == 'C')
	{
		assign_nibbleHigh(PORTC,DIO_u8ValueToSet);
	}

	/* Assign Port D with value */
	if(DIO_u8LocalPortToSet == 'D')
	{
		assign_nibbleHigh(PORTD,DIO_u8ValueToSet);
	}
}/* end DIO_voidWriteUpperNibble Function */


/*
 *  Reads the Value of the lower nibble of the Port: HIGH/LOW
 */
extern U8 DIO_u8ReadLowerNibble(U8 DIO_u8LocalPortToRead)
{
	U8 DIO_u8DataToBeRead;

	if( DIO_u8LocalPortToRead == 'A')
	{
		DIO_u8DataToBeRead = get_nibbleLow(PINA);
	}
	else if(DIO_u8LocalPortToRead == 'B')
	{
		DIO_u8DataToBeRead = get_nibbleLow(PINB);
	}
	else if(DIO_u8LocalPortToRead == 'C')
	{
		DIO_u8DataToBeRead = get_nibbleLow(PINC);
	}
	else if(DIO_u8LocalPortToRead == 'D')
	{
		DIO_u8DataToBeRead = get_nibbleLow(PIND);
	}

	return DIO_u8DataToBeRead;
} /*end DIO_u8ReadLowerNibble function */



/*
 *  Reads the Value of the Upper nibble of the Port: HIGH/LOW
 */
extern U8 DIO_u8ReadUpperNibble(U8 DIO_u8LocalPortToRead)
{
	U8 DIO_u8DataToBeRead;

	if( DIO_u8LocalPortToRead == 'A')
	{
		DIO_u8DataToBeRead = get_nibbleHigh(PINA);
	}
	else if(DIO_u8LocalPortToRead == 'B')
	{
		DIO_u8DataToBeRead = get_nibbleHigh(PINB);
	}
	else if(DIO_u8LocalPortToRead == 'C')
	{
		DIO_u8DataToBeRead = get_nibbleHigh(PINC);
	}
	else if(DIO_u8LocalPortToRead == 'D')
	{
		DIO_u8DataToBeRead = get_nibbleHigh(PIND);
	}

	return DIO_u8DataToBeRead;
} /*end DIO_u8ReadUpperNibble function */
