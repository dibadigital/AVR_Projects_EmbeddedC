#include <mega16.h>
#include <delay.h>

//void main(void)
//{
//    unsigned char i = 0;
//    unsigned char sw_previous_state = 0;
//    
//    DDRA = 0x00;
//    PORTA = 0xFF;
//    
//    DDRB = 0xFF;
//    PORTB = 0x00;
//    
//    while(1)
//    {  
//        if((PINA & (1 << 0)) == 1)
//        {      
//            sw_previous_state = 1;    
//        } 
//        
//        if(sw_previous_state == 1 && (PINA & (1 << 0)) == 0)
//        {       
//            delay_ms(200);
//            sw_previous_state = 0;
//            
//            for(i=0; i<5; i++)
//            {
//                PORTB = 0xFF;
//                delay_ms(200);
//                PORTB = 0x00;
//                delay_ms(200);
//            }
//        }
//    }
//}

void main(void)
{
    unsigned char i = 0;
    unsigned char sw_previous_state = 0;
    
    DDRA = 0x00;
    PORTA = 0xFF;
    
    DDRB = 0xFF;
    PORTB = 0x00;
    
    while(1)
    {  
        if(((PINA >> 0) & 0x01) == 0x01)
        {      
            sw_previous_state = 1;    
        } 
        
        if(sw_previous_state == 1 && ((PINA >> 0) & 0x01) == 0x00)
        {       
            delay_ms(200);
            sw_previous_state = 0;
            
            for(i=0; i<5; i++)
            {
                PORTB = 0xFF;
                delay_ms(200);
                PORTB = 0x00;
                delay_ms(200);
            }
        }
    }
}