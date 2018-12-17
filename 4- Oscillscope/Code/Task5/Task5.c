/*
 * Task3.c
 *
 * Created: 11/12/2018 10:57:11 PM
 *  Author: dell pc
 */ 
 #include <avr/io.h>
 #include <avr/interrupt.h>
 /*****************************************************************************/
 void setup(){
	OSCI_Init();
	sei();
 }

 void loop(){
	OSCI_MainFunction();
 }