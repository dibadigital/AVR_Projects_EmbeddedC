#include <mega16a.h>
#include <delay.h>

// Timer 0 overflow interrupt service routine (Internal Interrupt)
interrupt [TIM0_OVF] void isr_ovf_timer0(void)
{                  
    TCNT0 = 131;
}

void main(void)
{    
    DDRB = 0xFF;
    PORTB = 0x00;
    
    // Timer0, Normal Mode
    // Freq_osc = 8 MHz, Prescaler = 64, Bottom = 131, Top = 255 
    // T_ovf = 1 ms, Freq_ovf = 1 kHz
    // T_oc0 = 2 ms, Freq_oc0 = 500 Hz
    TCCR0 = 0x03;      // Prescaler = 64
    TCCR0 |= (1 << 4); // Toggle oc0 on compare match         
    TCNT0 = 131;       // Bottom = 131  
    OCR0 = 255;        // compare match and generate oc0
    TIMSK = 0x01;      // Enabling Timer 0 overflow interrupt
      
    // Global enable interrupts
    #asm("sei")
    
    while(1)
    {  
        
    }
}