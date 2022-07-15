#include <mega16.h>
#include <delay.h>

//void main(void)
//{
//    unsigned char i = 0;
//    unsigned char sw0_previous_state = 0, sw1_previous_state = 0; 
//    unsigned char key_cnt = 0;
//    
//    DDRA = 0x00;
//    PORTA = 0xFF;
//    
//    DDRB = 0xFF;
//    PORTB = 0x00;
//    
//    while(1)
//    {     
//        if((PINA & (1 << 0)) == 0x01)
//        {  
//            sw0_previous_state = 1; 
//        } 
//        
//        if(sw0_previous_state == 1 && (PINA & (1 << 0)) == 0x00)
//        {
//            delay_ms(200);
//            sw0_previous_state = 0;  
//            key_cnt++;
//        }
//        
//        if((PINA & (1 << 1)) == 0x02)
//        {      
//            sw1_previous_state = 1;    
//        } 
//        
//        if(sw1_previous_state == 1 && (PINA & (1 << 1)) == 0x00)
//        {       
//            delay_ms(200);
//            sw1_previous_state = 0;
//            
//            for(i=0; i<key_cnt; i++)
//            {
//                PORTB = 0xFF;
//                delay_ms(200);
//                PORTB = 0x00;
//                delay_ms(200);
//            } 
//            key_cnt = 0;
//        }   
//        
//        PORTB = key_cnt;
//    }
//}

void main(void)
{
    unsigned char i = 0;
    unsigned char sw0_previous_state = 0, sw1_previous_state = 0; 
    unsigned char key_cnt = 0;
    
    DDRA = 0x00;
    PORTA = 0xFF;
    
    DDRB = 0xFF;
    PORTB = 0x00;
    
    while(1)
    {     
        if(((PINA >> 0) & 0x01) == 0x01)
        {  
            sw0_previous_state = 1; 
        } 
        
        if(sw0_previous_state == 1 && ((PINA >> 0) & 0x01) == 0x00)
        {
            delay_ms(200);
            sw0_previous_state = 0;  
            key_cnt++;
        }
        
        if(((PINA >> 1) & 0x01) == 0x01)
        {      
            sw1_previous_state = 1;    
        } 
        
        if(sw1_previous_state == 1 && ((PINA >> 1) & 0x01) == 0x00)
        {       
            delay_ms(200);
            sw1_previous_state = 0;
            
            for(i=0; i<key_cnt; i++)
            {
                PORTB = 0xFF;
                delay_ms(200);
                PORTB = 0x00;
                delay_ms(200);
            } 
            key_cnt = 0;
        }   
        
        PORTB = key_cnt;
    }
}