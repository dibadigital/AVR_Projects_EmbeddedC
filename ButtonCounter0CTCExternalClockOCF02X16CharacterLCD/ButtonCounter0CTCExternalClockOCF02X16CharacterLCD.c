#include <mega16a.h>
#include <delay.h>
#include <stdio.h>

// Alphanumeric LCD functions
#include <alcd.h>

void main(void)
{
    char lcd_str[20] = {0};    
    
    DDRB = 0x00;
    PORTB = 0x01;
    
    DDRC = 0xFF;  //LCD DIR
    PORTC = 0x00; //LCD PORT  
    
    DDRD = 0xFF;
    PORTD = 0x00;
              
    // Counter0, External Clock T0, Falling Edge    
    // Normal Mode
    // Normal port operation, oc0 disconnected
    TCCR0 = 0x06;
    TCCR0 |= (1 << 3);
      
    TCNT0 = 0;
    OCR0 = 9;
    
    // Alphanumeric LCD initialization
    // Connections are specified in the
    // Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
    // RS - PORTC Bit 0
    // RD - PORTC Bit 1
    // EN - PORTC Bit 2
    // D4 - PORTC Bit 4
    // D5 - PORTC Bit 5
    // D6 - PORTC Bit 6
    // D7 - PORTC Bit 7
    // Characters/line: 16
    lcd_init(16);
    
    lcd_clear();
    
    while (1)
    {        
        if((TIFR & (1 << 1)) == 0x02)
        {
            PORTD.0 = !PORTD.0;
            TIFR = (1 << 1);  //Alternatively, OCF0 is cleared by writing a logic one to the flag.
        }
        
        sprintf(lcd_str, "%3u", TCNT0);
        lcd_gotoxy(0,0);
        lcd_puts(lcd_str);
    }
}