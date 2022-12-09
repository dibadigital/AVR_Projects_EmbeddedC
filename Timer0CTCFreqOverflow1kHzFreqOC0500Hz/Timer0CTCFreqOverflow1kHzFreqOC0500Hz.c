#include <mega16a.h>
#include <delay.h>

void main(void)
{    
    DDRB = 0xFF;
    PORTB = 0x00;
    
    // Timer0, CTC Mode
    // Freq_osc = 8 MHz, Prescaler = 64, Bottom = 0, OCR0 = 124 
    // T_ovf = 1 ms, Freq_ovf = 1 kHz
    // T_oc0 = 2 ms, Freq_oc0 = 500 Hz
    TCCR0 = 0x03;      // Prescaler = 64 
    TCCR0 |= (1 << 3); // CTC Mode
    TCCR0 |= (1 << 4); // Toggle oc0 on compare match  
    OCR0 = 124;        // compare match and generate oc0
    
    while(1)
    {  
        
    }
}