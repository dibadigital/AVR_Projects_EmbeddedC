#include <mega16a.h>
#include <delay.h>

void main(void)
{
    unsigned char SevenSegmentCA[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
    unsigned char digits[2] = {0};
    unsigned char i = 0, n = 0;
    unsigned char digitIdx = 0;
    
    DDRA = 0x00;
    PORTA = 0xFF;
    
    DDRC = 0xFF;
    PORTC = 0xFF;
    
    DDRD = 0xFF;
    PORTD = 0x00;
    
    while(1)
    {    
       i = PINA; 
       
       for (n=0; n<2; n++)
       {
           digits[n] = i%10;
           i = i/10; 
       }
       
       PORTD = (1 << digitIdx);                         
       PORTC = SevenSegmentCA[digits[digitIdx]];  
       digitIdx++;   
       if(digitIdx > 1)
            digitIdx = 0;
       delay_ms(2);
       
    }
}
