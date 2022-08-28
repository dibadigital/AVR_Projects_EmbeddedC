#ifndef _lcd2x16_4wires_H
#define _lcd2x16_4wires_H

#include <mega16a.h>
#include <delay.h>

// RS : PORTC.0
// RW : PORTC.1
// E  : PORTC.2
// DB4: PORTC.4
// DB5: PORTC.5
// DB6: PORTC.6
// DB7: PORTC.7

#define DATA_CONTROL_PORT PORTC
#define DATA_CONTROL_DDR  DDRC

#define Num_RS_PIN 0
#define Num_RW_PIN 1
#define Num_E_PIN 2

#define RS (1<<Num_RS_PIN)  //00000001
#define RW (1<<Num_RW_PIN)  //00000010
#define E  (1<<Num_E_PIN)   //00000100

void lcd_init(void);
void lcd_clear(void);
void lcd_gotoxy(unsigned char x, unsigned char y);
void lcd_putchar(char ch);
void lcd_puts(char *str);

#endif