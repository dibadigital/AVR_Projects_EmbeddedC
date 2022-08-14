#include <mega16a.h>
#include <delay.h>

//void main(void)
//{
//    unsigned char i = 0;
//    unsigned char select = 0;
//    
//    DDRB = 0xFF;
//    PORTB = 0x00;
//    
//    while(1)
//    {      
//    
//        if(select == 0)
//        {
//           PORTB = PORTB | (1 << i);
//        }
//        else
//        {
//           PORTB = 0xFE << i;
//        }                    
//        
//        i++;
//        if(i >= 8)
//        {
//            select = !select;
//            i = 0;
//        }  
//        delay_ms(300);
//    }
//}

void main(void)
{
    unsigned char i = 0;

    DDRB = 0xFF;
    PORTB = 0x00;
    
    while(1)
    {      
        PORTB = PORTB ^ (1 << i);                 
        
        i++;
        if(i >= 8)
        {
            i = 0;
        }  
        delay_ms(300);
    }
}
