/*
 * main.c
 *
 *  Created on: Dec 29, 2018
 *      Author: sayed mohsen
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include "Timer/Timer.h"
#include "ADC/ADC.h"
#include "USART/USART_Master.h"

#define BAUD_RATE  9600
#define AUTOMATIC_MODE 0
#define MANUAL_MODE 1

unsigned char max_number_of_overflows;
unsigned char counter = 0;
extern unsigned char Mode;
extern unsigned char Timer_interval;
extern unsigned char Motor_speed;
 
void turn_off_motor(void) {
	OCR0 = 0;

}
void turn_on_motor(unsigned char speed) {
	OCR0 = speed;
}

ISR (TIMER2_OVF_vect) {
	counter++;
	if (counter == max_number_of_overflows) {
		turn_off_motor() ;
		counter = 0;
	}
}

void set_time(unsigned char interval) {
	/*
	 * if F_cpu=4Mhz
	 * F_timer = 4000000/1024 = 3906 HZ
	 *
	 */
	unsigned int number_of_counts;
	number_of_counts = interval * 3906;
	max_number_of_overflows = number_of_counts / 256;
}

void motor_manual_mode(unsigned char interval, unsigned char speed) {
	/* speed == duty_cycle */
	turn_on_motor(speed);
	set_time(interval);
	timer2_normal_mode_init();
}
void motor_autmoatic_mode(void) {
	unsigned char speed = 	
	ADC_u8ReadADC();
	turn_on_motor(speed) ;
}

void Task_init(void) {
	/* ADC0 : TEMP_sensor on PA0 pin  */
	DDRA &= ~(1 << 0);
	/* OC0 : motor connected to PB3 pin */
	DDRB |= (1 << 3);
	/*initial value :TURn off motor */
	turn_off_motor();

	/* enable global interrupts */
	SREG |= (1 << 7);

}

int main(void) {
	/*...Initialization... */
	USART_Init(BAUD_RATE);
	Timer0_Void_Initialize_PWMmode();
	ADC_voidInitializeADC();
	Task_init();

	while (1) {
		if (Mode == MANUAL_MODE) {
			motor_manual_mode(Timer_interval, Motor_speed);
		} else if (Mode == AUTOMATIC_MODE) {
			motor_autmoatic_mode();
		} else {
			turn_off_motor();
		}

	}
}

