#ifndef _traffic_light_H
#define _traffic_light_H

#include <mega16a.h>
#include <delay.h>
#include <stdint.h>

#define STATE_G 0
#define STATE_Y 1
#define STATE_R 2

#define iG 60
#define iY 20
#define iR 80

extern signed char i;
extern uint16_t delay_cnt;
extern unsigned char digitIdx;
extern unsigned char digits[2];
extern unsigned char flag_change_state;

void calculate_digits(signed char j);
void show(unsigned char s);

#endif
