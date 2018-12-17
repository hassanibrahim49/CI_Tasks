
#define BAUD_RATE 9600
#define F_CPU 8000000ul

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "waveform.h"

int main(void)
{
	WAVE_Init();
	
	sei();

    while(1)
    { 
		WAVE_MainFunction();
		//_delay_ms(500);
    }
    return 0;
}
