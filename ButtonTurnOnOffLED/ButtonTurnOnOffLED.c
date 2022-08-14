#include <mega16a.h>
#include <delay.h>

//void main(void)
//{
//    DDRA = 0x00;
//    PORTA = 0xFF;
//    
//    DDRB = 0xFF;
//    PORTB = 0x00;
//    
//    while(1)
//    {
//        if(PINA.0 == 0)
//        {
//            PORTB = 0xFF;
//        }
//        else
//        {
//            PORTB = 0x00;
//        }
//    }
//}

//void main(void)
//{
//    DDRA = 0x00;
//    PORTA = 0xFF;
//    
//    DDRB = 0xFF;
//    PORTB = 0x00;
//    
//    while(1)
//    {
//        if((PINA & (1 << 0)) == 0)
//        {
//            PORTB = 0xFF;
//        }
//        else
//        {
//            PORTB = 0x00;
//        }
//    }
//}

void main(void)
{
    DDRA = 0x00;
    PORTA = 0xFF;
    
    DDRB = 0xFF;
    PORTB = 0x00;
    
    while(1)
    {
        if(((PINA >> 0) & 0x01) == 0x00)
        {
            PORTB = 0xFF;
        }
        else
        {
            PORTB = 0x00;
        }
    }
}
