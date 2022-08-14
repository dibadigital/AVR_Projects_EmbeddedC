#include <mega16a.h>
#include <delay.h>

#define PB PORTB
#define PINB_ON(x) PB|=(1<<x)
#define PINB_OFF(x) PB&=~(1<<x)

void main(void)
{
     unsigned char i=0;
     
     DDRB = 0xFF;
     PORTB = 0x00;
     
     while(1)
     {
          PINB_ON(i);
          delay_ms(500);
          i++;
          i = (i<8)? i : 0;
          PORTB = (i!=0)? PORTB : 0;
     }
}
