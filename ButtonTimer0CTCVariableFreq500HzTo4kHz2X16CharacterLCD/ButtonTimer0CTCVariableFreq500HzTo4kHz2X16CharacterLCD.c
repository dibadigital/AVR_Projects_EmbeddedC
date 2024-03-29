#include <mega16a.h>
#include <delay.h>
#include <stdio.h>

// Alphanumeric LCD functions
#include <alcd.h>

void main(void)
{    
    char lcd_str[20] = {0}; 
    
    DDRA = 0x00;
    PORTA = 0xFF;
    
    DDRB = 0xFF;
    PORTB = 0x00; 
    
    DDRC = 0xFF;  //LCD DIR
    PORTC = 0x00; //LCD PORT
    
    // Timer0, CTC Mode
    // Freq_osc = 8 MHz, Prescaler = 64, Bottom = 0, OCR0 =~ 15 to 124 
    // T_ovf =  128 us to 1 ms, Freq_ovf =  7.8125 kHz to 1 kHz
    // T_oc0 =~ 250 us to 2 ms, Freq_oc0 =~ 4 kHz to 500 Hz
    TCCR0 = 0x03;      // Prescaler = 64 
    TCCR0 |= (1 << 3); // CTC Mode
    TCCR0 |= (1 << 4); // Toggle oc0 on compare match  
    OCR0 = 15;         // compare match and generate oc0
     
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
    
    while(1)
    {  
        if (PINA.0 == 0)
        {          
            if (OCR0 < 124)
            {
                OCR0++;
            }
        } 
        
        if (PINA.1 == 0)
        {          
            if (OCR0 > 15)
            {
                OCR0--;
            }
        }   
        
        delay_ms(10);   
        sprintf(lcd_str, "OCR0 = %3u", OCR0);
        lcd_gotoxy(0, 0);
        lcd_puts(lcd_str);
        
        sprintf(lcd_str, "FreqOC = %07.2f", 0.5*((8000000.0/64)/(OCR0-0+1)));
        lcd_gotoxy(0, 1);
        lcd_puts(lcd_str);
    }
}