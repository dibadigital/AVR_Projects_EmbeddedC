#include <mega16.h>
#include <delay.h>

void main(void)
{
    unsigned char SevenSegmentCC[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
    signed char i = 9;
    
    DDRC = 0xFF;
    PORTC = 0x00;
    
    DDRD = 0xFF;
    PORTD = 0xFE;
    
    while(1)
    {
       PORTC = SevenSegmentCC[i];
       i--;
       if(i < 0)
        i = 9;
       delay_ms(1000); 
    }
}