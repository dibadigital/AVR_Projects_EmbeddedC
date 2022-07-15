#include <mega16.h>
#include <delay.h>

//void main(void)
//{
//    DDRB = 0xFF;
//    PORTB = 0x00;
//    
//    while(1)
//    {
//        PORTB |= (1<<7);
//        delay_ms(500); 
//        PORTB &= ~(1<<7);
//        delay_ms(500);
//    }
//}

//void main(void)
//{
//    DDRB = 0xFF;
//    PORTB = 0x00;
//    
//    while(1)
//    {
//        PORTB ^= (1<<7);
//        delay_ms(500);
//    }
//}

#define PB PORTB
#define PINB_ON(x) PB|=(1<<x)
#define PINB_OFF(x) PB&=~(1<<x)

void main(void)
{
    DDRB = 0xFF;
    PORTB = 0x00;
    
    while(1)
    {
        PINB_ON(7);
        delay_ms(500);
        PINB_OFF(7);
        delay_ms(500);
    }
}
