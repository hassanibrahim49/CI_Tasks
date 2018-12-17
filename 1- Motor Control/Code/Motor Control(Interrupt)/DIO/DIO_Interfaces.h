/*
 * DIO_Private.h
 *
 *  Created on: Aug 12, 2017
 *      Author: ihass
 */

#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

/* Calling the header file that contains the (u8) Vriable */
#include "../all-includes.h"

/* Declaration of any pin */
#define DIO_OUTPUT     1
#define DIO_INPUT      0

#define DIO_HIGH     1
#define DIO_LOW      0

/* Defining PINS using ( enum ) method  */
typedef enum {
	/* Defining PORTA */
	DIO_PIN0_PPORTA,   // This means PIN 0
	DIO_PIN1_PPORTA,   // This means PIN 1
	DIO_PIN2_PPORTA,   // This means PIN 2
	DIO_PIN3_PPORTA,   // This means PIN 3
	DIO_PIN4_PPORTA,   // This means PIN 4
	DIO_PIN5_PPORTA,   // This means PIN 5
	DIO_PIN6_PPORTA,   // This means PIN 6
	DIO_PIN7_PPORTA,   // This means PIN 7

	/* Defining PORTB */
	DIO_PIN0_PPORTB,   // This means PIN 8
	DIO_PIN1_PPORTB,   // This means PIN 9
	DIO_PIN2_PPORTB,   // This means PIN 10
	DIO_PIN3_PPORTB,   // This means PIN 11
	DIO_PIN4_PPORTB,   // This means PIN 12
	DIO_PIN5_PPORTB,   // This means PIN 13
	DIO_PIN6_PPORTB,   // This means PIN 14
	DIO_PIN7_PPORTB,   // This means PIN 15

	/* Defining PORTC */
	DIO_PIN0_PPORTC,   // This means PIN 16
	DIO_PIN1_PPORTC,   // This means PIN 17
	DIO_PIN2_PPORTC,   // This means PIN 18
	DIO_PIN3_PPORTC,   // This means PIN 19
	DIO_PIN4_PPORTC,   // This means PIN 20
	DIO_PIN5_PPORTC,   // This means PIN 21
	DIO_PIN6_PPORTC,   // This means PIN 22
	DIO_PIN7_PPORTC,   // This means PIN 23

	/* Defining PORTD */
	DIO_PIN0_PPORTD,   // This means PIN 24
	DIO_PIN1_PPORTD,   // This means PIN 25
	DIO_PIN2_PPORTD,   // This means PIN 26
	DIO_PIN3_PPORTD,   // This means PIN 27
	DIO_PIN4_PPORTD,   // This means PIN 28
	DIO_PIN5_PPORTD,   // This means PIN 29
	DIO_PIN6_PPORTD,   // This means PIN 30
	DIO_PIN7_PPORTD,   // This means PIN 31

} PORTS;

#endif /* DIO_PRIVATE_H_ */
