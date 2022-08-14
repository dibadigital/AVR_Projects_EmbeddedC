#include <mega16a.h>
#include <delay.h>

void main(void)
{
   DDRB = 0xFF;
   PORTB = 0x00;
   
    while(1)
    {
        PORTB = 0x0F;
        delay_ms(500); 
        PORTB = 0xF0;
        delay_ms(500);   
    }
}
