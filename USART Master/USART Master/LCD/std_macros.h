/*
 * std_macros.h
 *
 *  Created on: Oct 4, 2018
 *      Author: Mora
 */

#ifndef LCD_DRIVER_STD_MACROS_H_
#define LCD_DRIVER_STD_MACROS_H_


#include <avr/io.h>
#define F_CPU 12000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#define SETBIT(REG,BIT)  (REG |= 1 << BIT)
#define CLRBIT(REG,BIT)  (REG &= ~(1 << BIT))
#define TOGBIT(REG,BIT)  (REG ^= 1 << BIT)
#define READBIT(REG,BIT)  ((REG >> BIT) & 1)



#endif /* LCD_DRIVER_STD_MACROS_H_ */
