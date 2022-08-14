#include <mega16a.h>
#include <delay.h>

void main(void)
{
    unsigned char i = 0;
    
    DDRB = 0xFF;
    PORTB = 0x00;
    
    while(1)
    {
        PORTB = 1 << i;
        i++;
        if(i >= 8)  
        {
            i = 0;
        }
        delay_ms(300);    
    }
}
