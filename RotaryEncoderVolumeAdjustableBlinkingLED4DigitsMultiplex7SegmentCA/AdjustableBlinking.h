#ifndef _AdjustableBlinking_H
#define _AdjustableBlinking_H

#include <mega16.h> 
#include <delay.h>
#include <stdint.h>

extern const unsigned char SevenSegmentCA[10];
extern unsigned char digits[4];
extern unsigned char digitIdx;
extern unsigned char previous_state_clk, previous_state_sw;
extern int16_t key_cnt;  
extern unsigned char delay_cnt; 
extern unsigned char flag_blinking;

void RotaryEncoderVolInit(void);
void RotaryEncoderVolRead(void);
void BlinkingFunc(void);
void LEDInit(void);
void SevenSegmentInit(void);
void SevenSegmentWrite(uint16_t number);
void SevenSegmentUpdate(void);
void TimerHandler(void);

#endif
