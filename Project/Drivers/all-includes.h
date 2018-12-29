/*
 * all-includes.h
 *
 *  Created on: Mar 28, 2018
 *      Author: Hassan Ibrahim
 */

#ifndef ALL_INCLUDES_H_
#define ALL_INCLUDES_H_

// Including Main functions and main registers
#include "avr/io.h"
#include <avr/interrupt.h>
#include "util/delay.h"

// From (Main Files) Folder
#include "Main Files/Variables.h"
#include "Main Files/Built-In-Functions.h"

// From (DIO) Folder
#include "DIO/DIO_Interfaces.h"
#include "DIO/DIO-Functions.h"

// From ( Interrupt ) Folder
#include "Interrupt/External_Interupt.h"

// From ( uart ) Folder
#include "uart/uart.h"

// From ( Timer ) Folder
#include "Timer/Timer.h"

#endif /* ALL_INCLUDES_H_ */
