#include <mega16.h>
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
//        if(PINA.0 == 0 && PINA.1 == 0)
//        {
//            PORTB = 0x00;
//        }
//        else if(PINA.0 == 0)
//        {
//            PORTB |= 0x01;
//        } 
//        else if(PINA.1 == 0)
//        {
//            PORTB |= 0x02;
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
//        if((PINA & (1 << 0)) == 0 && (PINA & (1 << 1)) == 0)
//        {
//            PORTB = 0x00;
//        }
//        else if((PINA & (1 << 0)) == 0)
//        {
//            PORTB |= 0x01;
//        } 
//        else if((PINA & (1 << 1)) == 0)
//        {
//            PORTB |= 0x02;
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
//        if((PINA & (1 << 0)) == 0 && (PINA & (1 << 1)) == 0)
//        {
//            PORTB &= ~(1 << 0);     
//            PORTB &= ~(1 << 1);
//        }
//        else if((PINA & (1 << 0)) == 0)
//        {
//            PORTB |= (1 << 0);
//        } 
//        else if((PINA & (1 << 1)) == 0)
//        {
//            PORTB |= (1 << 1);
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
        if(((PINA >> 0) & 0x01) == 0x00 && ((PINA >> 1) & 0x01) == 0x00)
        {
            PORTB &= ~(1 << 0);     
            PORTB &= ~(1 << 1);
        }
        else if(((PINA >> 0) & 0x01) == 0x00)
        {
            PORTB |= (1 << 0);
        } 
        else if(((PINA >> 1) & 0x01) == 0x00)
        {
            PORTB |= (1 << 1);
        }
    }
}