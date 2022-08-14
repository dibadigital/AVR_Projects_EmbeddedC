#ifndef _keypad4x4_led_7seg_H
#define _keypad4x4_led_7seg_H

#include <mega16a.h> 
#include <delay.h>
#include <stdint.h>

#define R1 PORTA.0
#define R2 PORTA.1
#define R3 PORTA.2
#define R4 PORTA.3

#define C1 PINA.4
#define C2 PINA.5
#define C3 PINA.6
#define C4 PINA.7

extern const unsigned char SevenSegmentCA[10];
extern unsigned char digitIdx;
extern unsigned char digits[4];

extern const unsigned char KeypadMatrix[4][4];
extern unsigned char C_previous[4];
extern unsigned char key, key_previous;
extern unsigned char debouncer, keyReady;
extern int16_t number;

extern unsigned char delay_cnt; 
extern unsigned char flag_blinking;

void LEDInit(void);
void BlinkingFunc(void);

void KeypadInit(void);
unsigned char GetEdge(void);
unsigned char KeypadRead(void);
unsigned char KeypadFunc(void);

void SevenSegmentInit(void);
void SevenSegmentWrite(uint16_t number);
void SevenSegmentUpdate(void);

void TimerHandler(void);

#endif
