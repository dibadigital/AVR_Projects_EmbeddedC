#include <mega16a.h>
#include <delay.h>

void main(void)
{
    unsigned char i = 0;  //0 to 255
    
    DDRB = 0xFF;
    PORTB = 0x00;
    
    while(1)
    {
      i--;
      PORTB = i;
      delay_ms(300);  
    }
}
