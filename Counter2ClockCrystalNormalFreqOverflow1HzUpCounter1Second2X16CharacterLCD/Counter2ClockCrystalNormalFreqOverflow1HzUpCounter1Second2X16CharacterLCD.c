#include <mega16a.h>
#include <delay.h>
#include <stdio.h>
#include <stdint.h>

// Alphanumeric LCD functions
#include <alcd.h>

unsigned char sec = 0;

// Timer 2 overflow interrupt service routine (Internal Interrupt)
interrupt [TIM2_OVF] void isr_ovf_timer2(void)  //1ms
{              
    sec++;
    if(sec >= 60)  
        sec = 0;
}

void main(void)
{    
    char lcd_str[20] = {0};
      
    DDRD = 0xFF;  //LCD DIR
    PORTD = 0x00; //LCD PORT
    
    // Timer2, Normal Mode
    // Freq_ClockCrystal = 32.768 KHz, Prescaler = 128, Bottom = 0, Top = 255 
    // T_ovf = 1 s, Freq_ovf = 1 Hz
    ASSR = (1 << 3); // Enabling Counter 2 (ClockCrystal, RTC)
    TCCR2 = 0x05;    // Prescaler = 128       
    TCNT2 = 0;       // Bottom = 0  
    OCR2 = 255;      // compare match and generate oc2
    TIMSK = (1 << 6);    // Enabling Timer 2 overflow interrupt
      
    // Global enable interrupts
    #asm("sei")
     
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
      
    sprintf(lcd_str, "second = %02u", sec);
    lcd_gotoxy(0, 0);
    lcd_puts(lcd_str);
            
    while(1)
    {  
        sprintf(lcd_str, "second = %02u", sec);
        lcd_gotoxy(0, 0);
        lcd_puts(lcd_str);
    }
}
