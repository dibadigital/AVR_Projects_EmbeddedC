#include <mega16.h>
#include <delay.h>

void main(void)
{
    signed char x = 99;
    unsigned char a = 0, b = 0;
    
    DDRC = 0xFF;
    PORTC = 0x00;
    
    while(1)
    {
       a = x/10;
       b = x%10;
       PORTC = (a << 4) | b;
       delay_ms(500);
       x--;
       if(x < 0)
        x = 99; 
    }
}