#ifndef _calculator_H
#define _calculator_H

#include <mega16a.h> 
#include <delay.h>
#include <stdio.h>
#include <stdint.h>

#include <alcd.h>

#define R1 PORTA.0
#define R2 PORTA.1
#define R3 PORTA.2
#define R4 PORTA.3

#define C1 PINA.4
#define C2 PINA.5
#define C3 PINA.6
#define C4 PINA.7

extern const unsigned char KeypadMatrix[4][4];
extern unsigned char C_previous[4];
extern unsigned char key, key_previous;
extern unsigned char debouncer, keyReady;

extern uint32_t number, result, val2, lcd_var;
extern unsigned char op;  
extern unsigned char flag_val2, flag_equal; 

void KeypadInit(void);
unsigned char GetEdge(void);
unsigned char KeypadRead(void);
unsigned char KeypadFunc(void);

void calculator_process (void);
void digit_process (void);
void operator_process (void);
void clear_process (void);
void equal_process (void);
void lcd_process(void);
void lcd_error(void);

#endif
