#ifndef _keypad4x4_H
#define _keypad4x4_H

#include <mega16a.h> 
#include <delay.h>

#define R1 PORTA.0
#define R2 PORTA.1
#define R3 PORTA.2
#define R4 PORTA.3

#define C1 PINA.4
#define C2 PINA.5
#define C3 PINA.6
#define C4 PINA.7

void KeypadInit(void);
unsigned char KeypadRead(void);

#endif
