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
    
    // Timer0, PhaseCorrectPWM Mode
    // Freq_osc = 8 MHz, Prescaler = 64, Bottom = 0, OCR0 =~ 25 to 229 (Duty Cycle =~ 90% to 10%)
    // T_ovf =~ 4 ms, Freq_ovf = 245 Hz
    // T_oc0 =~ 4 ms, Freq_oc0 = 245 Hz
    TCCR0 = 0x03;      // Prescaler = 64
    TCCR0 |= (1 << 6); // PhaseCorrectPWM Mode
    TCCR0 |= (1 << 4); // Set oc0 on compare match when up-counting, Clear oc0 on compare match when down-counting (inverting mode)  
    TCCR0 |= (1 << 5); // Set oc0 on compare match when up-counting, Clear oc0 on compare match when down-counting (inverting mode)
    TCNT0 = 0;
    OCR0 = 229;        // compare match and generate oc0
     
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
        if (PINA.1 == 0)
        {          
            if (OCR0 < 229)
            {
                OCR0++;
            }
        } 
        
        if (PINA.0 == 0)
        {          
            if (OCR0 > 25)
            {
                OCR0--;
            }
        }   
        
        delay_ms(20);     
        sprintf(lcd_str, "OCR = %3u", OCR0);
        lcd_gotoxy(0, 0);
        lcd_puts(lcd_str);
        
        sprintf(lcd_str, "Duty = %2d", 100*(255-OCR0)/(255-0));
        lcd_gotoxy(0, 1);
        lcd_puts(lcd_str);
    }
}