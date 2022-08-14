#ifndef _lcd2x16_8wires_H
#define _lcd2x16_8wires_H

#include <mega16a.h>
#include <delay.h>

// RS : PORTC.0
// RW : PORTC.1
// E  : PORTC.2
// DB0: PORTD.0
// DB1: PORTD.1
// DB2: PORTD.2
// DB3: PORTD.3
// DB4: PORTD.4
// DB5: PORTD.5
// DB6: PORTD.6
// DB7: PORTD.7

#define DATA_PORT PORTD
#define DATA_DDR  DDRD

#define CONTROL_PORT PORTC
#define CONTROL_DDR  DDRC

#define Num_RS_PIN 0
#define Num_RW_PIN 1
#define Num_E_PIN 2

#define RS (1<<Num_RS_PIN)  //00000001
#define RW (1<<Num_RW_PIN)  //00000010
#define E (1<<Num_E_PIN)    //00000100

void lcd_init(void);
void lcd_clear(void);
void lcd_gotoxy(unsigned char x, unsigned char y);
void lcd_putchar(char ch);
void lcd_puts(char *str);

#endif
