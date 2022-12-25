#include <mega16a.h>
#include <delay.h>
#include <stdio.h>
#include <stdint.h>

// Alphanumeric LCD functions
#include <alcd.h>

uint16_t i = 0;
unsigned char flag = 0, sec = 0;

// Timer 0 overflow interrupt service routine (Internal Interrupt)
interrupt [TIM0_OVF] void isr_ovf_timer0(void)  //1ms
{                  
    TCNT0 = 131;
    i++;
    if(i > 1000) //1000*1ms = 1000 ms = 1 s
    {
        i = 0;
        flag = 1;
    }
    
}

void main(void)
{    
    char lcd_str[20] = {0}; 
    
    DDRB = 0xFF;
    PORTB = 0x00;
      
    DDRC = 0xFF;  //LCD DIR
    PORTC = 0x00; //LCD PORT
    
    // Timer0, Normal Mode
    // Freq_osc = 8 MHz, Prescaler = 64, Bottom = 131, Top = 255 
    // T_ovf = 1 ms, Freq_ovf = 1 kHz
    TCCR0 = 0x03;      // Prescaler = 64       
    TCNT0 = 131;       // Bottom = 131  
    OCR0 = 255;        // compare match and generate oc0
    TIMSK = 0x01;      // Enabling Timer 0 overflow interrupt
      
    // Global enable interrupts
    #asm("sei")
     
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
      
    sprintf(lcd_str, "second = %02u", sec);
    lcd_gotoxy(0, 0);
    lcd_puts(lcd_str);
            
    while(1)
    {  
        if(flag == 1)
        {
            flag = 0;   
            sec++;
            if(sec >= 60)  
                sec = 0;
            sprintf(lcd_str, "second = %02u", sec);
            lcd_gotoxy(0, 0);
            lcd_puts(lcd_str);
        }
    }
}