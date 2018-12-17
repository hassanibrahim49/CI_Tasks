/*
 * main.c
 *
 *  Created on: Oct 17, 2018
 *      Author: ihass
 */

#define F_CPU 4000000ul

#include "avr/io.h"
#include "all-includes.h"

extern u8 UART;

int main(void) {

	volatile float duty_cycle = 0;

	uart_init();
	Timer0_Void_Initialize_PWMmode();

	DDRD = 0xf0;
	DDRB = 0xff;
	DDRC = 0xff;

	uart_send_char('S');

	Set_Bit(SREG, 7);

	while (1) {

		if (UART == '5') {
			UART = 0;
			Toggle_Bit(PORTD, 7);
		}

		if (UART == '0') {
			UART = 0;
			duty_cycle -= 0.1;
			if (duty_cycle <= 0) {
				duty_cycle = 0;
			}
		}

		if (UART == '1') {
			UART = 0;
			duty_cycle += 0.1;
			if (duty_cycle >= 1) {
				duty_cycle = 1;
			}
		}

		if ( Get_Bit(PIND,2) == 1) {
			duty_cycle -= 0.1;
			if (duty_cycle <= 0) {
				duty_cycle = 0;
			}
			uart_send_char('U');
			_delay_ms(250);
		}

		if ( Get_Bit(PIND,3) == 1) {
			duty_cycle += 0.1;
			if (duty_cycle >= 1) {
				duty_cycle = 1;
			}
			uart_send_char('D');
			_delay_ms(250);
		}

		OCR0 = (u8) (255 * (1 - duty_cycle));
		PORTC = OCR0;
	}

	return 0;
}
