#include <mega16a.h>
#include <delay.h>

void main(void) //The Rotary Encoder Volume used creates an edge with each step change.
{
    unsigned char SevenSegmentCA[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
    unsigned char digits[4] = {0};
    unsigned char i = 0, n = 0;
    unsigned char digitIdx = 0;
    
    unsigned char previous_state_clk = 1;
    
    DDRA = 0x00;
    PORTA = 0x00;
    
    DDRB = 0xFF;
    PORTB = 0x00;
    
    DDRC = 0xFF;
    PORTC = 0xFF;
    
    DDRD = 0xFF;
    PORTD = 0x00;
    
    previous_state_clk = ((PINA >> 0) & 0x01);
    
    while(1)
    {
        if(((PINA >> 0) & 0x01) != previous_state_clk) //positive & negative edges of clk
        {
            previous_state_clk = ((PINA >> 0) & 0x01);
            if(((PINA >> 1) & 0x01) == ((PINA >> 0) & 0x01))
                PORTB--;
            else
                PORTB++;
        } 
         
        i = PORTB; 
        for (n=0; n<4; n++)
        {
           digits[n] = i%10;
           i = i/10; 
        }
        PORTD = (1 << digitIdx);                         
        PORTC = SevenSegmentCA[digits[digitIdx]];  
        digitIdx++;   
        if(digitIdx > 3)
            digitIdx = 0;
        delay_ms(2);
    }
}
