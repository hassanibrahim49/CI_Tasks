#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"

#include <avr/io.h>

#include "Task5.h"

int main(void)
{
	setup();
	while (1)
	{
		loop();
	}
}