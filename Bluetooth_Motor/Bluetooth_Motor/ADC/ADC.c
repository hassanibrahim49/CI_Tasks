/*
 * ADC.c
 *
 *  Created on: Aug 26, 2017
 *      Author: ihass
 */

#include "../all-includes.h"

extern void ADC_voidInitializeADC(void) {

	/*
	 ADMUX : ADC Multiplexer Selection Register
	 ADMUX = 0b01100001;
	 */

	// Bit 7:6 - REFS1:0: Reference Selection Bits
	// REFS1:0    REFS0:1     : AVCC With external capacitor at AREF pin
	Clr_Bit(ADMUX, 7);
	Set_Bit(ADMUX, 6);

	// Bit 5 - ADLAR : ADC Left Adjust Result
	// Making this bit 1 will make Left Adjust to the Register
	Set_Bit(ADMUX, 5);

	// Bits 4:0 - Mux4:0 : Analog channel and gain selection Bits
	// MUX4:0  : 00001 : ADC0
	Clr_Bit(ADMUX, 4);
	Clr_Bit(ADMUX, 3);
	Clr_Bit(ADMUX, 2);
	Clr_Bit(ADMUX, 1);
	Clr_Bit(ADMUX, 0);

	/*
	 ADCSRA : ADC Control and Status Register
	 ADCSRA = 0b10000011;
	 */

	// Bit 7 : ADEN : ADC Enable
	Set_Bit(ADCSRA, 7);		// ADCSRA=0b10000000;

	// ADC Enable and Prescaler of 8
	// 1000000 / 8 = 125000
	Set_Bit(ADCSRA, 2);
	Set_Bit(ADCSRA, 1);
	Set_Bit(ADCSRA, 0);

}

extern unsigned char  ADC_u8ReadADC(void) {

	// Bit 6 : ADSC : ADC Start conversion
	Set_Bit(ADCSRA, 6);

	// Bit 4 : ADIF : ADC Interrupt Flag ( Polling on the ADC Interrupt Flag )
	while (Get_Bit(ADCSRA,4) == 0) {
		// Do Nothing
	};

	// Bit 4 : This bit is set when an ADC conversion completes and the data registers are updated
	// Clearing the ADC flag by writing logical one
	Set_Bit(ADCSRA, 4);

	// Return ADCH value
	return ADCH;
}
