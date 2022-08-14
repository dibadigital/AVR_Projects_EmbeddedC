#include <mega16a.h>
#include <delay.h>

//void main(void)
//{
//    signed char x = 99;
//    unsigned char a = 0, b = 0;
//    
//    DDRC = 0xFF;
//    PORTC = 0x00;
//    
//    while(1)
//    {
//       a = x/10;
//       b = x%10;
//       PORTC = (a << 4) | b;
//       delay_ms(500);
//       x--;
//       if(x < 0)
//        x = 99; 
//    }
//}

unsigned char show_BCD(unsigned char x);

void main(void)
{
    signed char i = 99;
    
    DDRC = 0xFF;
    PORTC = 0x00;
    
    while(1)
    {
       PORTC = show_BCD(i);
       delay_ms(500);
       i--;
       if(i< 0)
        i = 99; 
    }
}

unsigned char show_BCD(unsigned char x)
{
    unsigned char a = 0, b = 0; 
    unsigned char y = 0;
    
    a = x/10;  
    b = x%10;  
    y = (a << 4) | b;
    
    return y;
}
