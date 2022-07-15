#include <mega16.h>
#include <delay.h>

void main(void)
{
   DDRB = 0xFF;
   PORTB = 0x00;
   
    while(1)
    {
        PORTB = ~PORTB;
        delay_ms(500);    
    }
}