#include <mega16a.h>
#include <delay.h>

void main(void)
{
    unsigned char SevenSegmentCA[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
    unsigned char i = 0;
    
    DDRC = 0xFF;
    PORTC = 0xFF;
    
    DDRD = 0xFF;
    PORTD = 0x01;
    
    while(1)
    {
       PORTC = SevenSegmentCA[i];
       i++;
       if(i > 9)
        i = 0;
       delay_ms(1000); 
    }
}
