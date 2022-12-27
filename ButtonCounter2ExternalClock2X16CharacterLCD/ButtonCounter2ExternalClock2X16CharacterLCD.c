#include <mega16a.h>
#include <delay.h>
#include <stdio.h>

// Alphanumeric LCD functions
#include <alcd.h>

void main(void)
{
    char lcd_str[20] = {0};    
    
    DDRC = 0x00;
    PORTC = 0x40;
    
    DDRD = 0xFF;  //LCD DIR
    PORTD = 0x00; //LCD PORT
              
    // Counter2, External Clock TOSC1, Falling Edge    
    // Normal Mode
    // Normal port operation, oc0 disconnected
    ASSR = (1 << 3);    // Enabling Counter 2 
    TCCR2 = 0x01;       // Prescaler = 1  
    TCNT2 = 0;          // Bottom = 0  
    OCR2 = 255;         // compare match and generate oc2
    
    // Alphanumeric LCD initialization
    // Connections are specified in the
    // Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
    // RS - PORTD Bit 0
    // RD - PORTD Bit 1
    // EN - PORTD Bit 2
    // D4 - PORTD Bit 4
    // D5 - PORTD Bit 5
    // D6 - PORTD Bit 6
    // D7 - PORTD Bit 7
    // Characters/line: 16
    lcd_init(16);
    
    lcd_clear();
    
    while (1)
    {
        sprintf(lcd_str, "%3u", TCNT2);
        lcd_gotoxy(0,0);
        lcd_puts(lcd_str);
    }
}