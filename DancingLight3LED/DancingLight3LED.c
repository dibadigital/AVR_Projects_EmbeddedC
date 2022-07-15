#include <mega16.h>
#include <delay.h>

void main(void)
{
    unsigned char a = 1, b = 1, c = 1, d = 1;
    unsigned int t1 = 0, t2 = 0, t3 = 0, t4 = 0;
 
    DDRA = 0xFF;
    PORTA = 0x00;
     
    DDRB = 0xFF;
    PORTB = 0x00;
    
    DDRC = 0xFF;
    PORTC = 0x00;
    
    DDRD = 0xFF;
    PORTD = 0x00;
    
    while(1)
    {       
       t1++;
       t2++;
       t3++;
       t4++;
       
       delay_ms(1);
       
       if(t1 == 63) //63 ms
       {
          t1 = 0; 
          PORTA = a;
          a = a << 1;
          a = (a == 0) ? 1 : a;
       } 
       
       if(t2 == 210) //210 ms
       {
          t2 = 0;  
          PORTB = b;
          b = b << 1;
          b = (b == 0) ? 1 : b;
       }
       
       if(t3 == 474) //474 ms
       {
          t3 = 0;
          PORTC = c;
          c = c << 1;
          c = (c == 0) ? 1 : c;
       }
       
       if(t4 == 688) //688 ms
       {
          t4 = 0; 
          PORTD = d;
          d = d << 1;
          d = (d == 0) ? 1 : d;
       } 
    }
}