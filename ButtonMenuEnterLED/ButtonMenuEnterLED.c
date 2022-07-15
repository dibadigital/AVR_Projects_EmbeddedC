#include <mega16.h>
#include <delay.h>

//void main(void)  // This Code isn't good idea if the  delay is high.
//{
//    unsigned char menu_cnt = 0, select = 0;
//    unsigned char sw0_previous_state = 0, sw1_previous_state = 0; 
//    unsigned char i = 0; // 0 to 255
//    
//    DDRA = 0x00;
//    PORTA = 0xFF;
//    
//    DDRB = 0xFF;
//    PORTB = 0x00;
//    
//    while(1)
//    {
//        if(((PINA >> 0) & 0x01) == 0x01)
//        {  
//            sw0_previous_state = 1; 
//        } 
//        
//        if(sw0_previous_state == 1 && ((PINA >> 0) & 0x01) == 0x00)
//        {
//            delay_ms(200);
//            sw0_previous_state = 0;  
//            
//            menu_cnt++;
//            if(menu_cnt > 3)
//                menu_cnt = 0; 
//            
//            select = 0;
//        }
//        
//        if(((PINA >> 1) & 0x01) == 0x01)
//        {      
//            sw1_previous_state = 1;    
//        } 
//        
//        if(sw1_previous_state == 1 && ((PINA >> 1) & 0x01) == 0x00)
//        {       
//            delay_ms(200);
//            sw1_previous_state = 0;
//            
//            PORTB = 0x00;
//            i = 0;
//            select = 1;
//        } 
//        
//        if(select == 0) 
//        {
//            PORTB = (1 << menu_cnt);
//        }
//        else
//        {
//            switch(menu_cnt)
//            {
//                case 0:   //Menu 0 : BlinkingLED
//                    PORTB = ~PORTB;
//                break;  
//                
//                case 1:   //Menu 1 : UpCounterLED
//                    i++;
//                    PORTB = i;
//                break; 
//                
//                case 2:   //Menu 2 : RingCounterLED
//                    PORTB = (1 << i);
//                    i++;
//                    if(i >= 8)
//                        i = 0;
//                break;   
//                
//                case 3:   //Menu 3 : RingUpDownCounterLED
//                    PORTB = PORTB ^ (1 << i);
//                    i++;
//                    if(i >= 8)
//                        i = 0; 
//                break;
//            }
//            delay_ms(200);
//        }  
//        
//    }
//}

//void main(void)
//{
//    unsigned char menu_cnt = 0, select = 0;
//    unsigned char sw0_previous_state = 0, sw1_previous_state = 0; 
//    unsigned char i = 0; // 0 to 255
//    unsigned char delay_cnt = 0;
//    
//    DDRA = 0x00;
//    PORTA = 0xFF;
//    
//    DDRB = 0xFF;
//    PORTB = 0x00;
//    
//    while(1)
//    {
//        if(((PINA >> 0) & 0x01) == 0x01)
//        {  
//            sw0_previous_state = 1; 
//        } 
//        
//        if(sw0_previous_state == 1 && ((PINA >> 0) & 0x01) == 0x00)
//        {
//            delay_ms(200);
//            sw0_previous_state = 0;  
//            
//            menu_cnt++;
//            if(menu_cnt > 3)
//                menu_cnt = 0; 
//            
//            select = 0;
//        }
//        
//        if(((PINA >> 1) & 0x01) == 0x01)
//        {      
//            sw1_previous_state = 1;    
//        } 
//        
//        if(sw1_previous_state == 1 && ((PINA >> 1) & 0x01) == 0x00)
//        {       
//            delay_ms(200);
//            sw1_previous_state = 0;
//            
//            PORTB = 0x00;
//            i = 0;
//            select = 1;
//        } 
//        
//        if(select == 0) 
//        {
//            PORTB = (1 << menu_cnt);
//        }
//        else
//        {
//            if(delay_cnt >= 100)
//            {   
//                delay_cnt = 0;
//                switch(menu_cnt)
//                {
//                    case 0:   //Menu 0 : BlinkingLED
//                        PORTB = ~PORTB;
//                    break;  
//                
//                    case 1:   //Menu 1 : UpCounterLED
//                        i++;
//                        PORTB = i;
//                    break; 
//                
//                    case 2:   //Menu 2 : RingCounterLED
//                        PORTB = (1 << i);
//                        i++;
//                        if(i >= 8)
//                            i = 0;
//                    break;   
//                
//                    case 3:   //Menu 3 : RingUpDownCounterLED
//                        PORTB = PORTB ^ (1 << i);
//                        i++;
//                        if(i >= 8)
//                            i = 0; 
//                    break;
//                } 
//            }
//            delay_cnt++;
//            delay_ms(20);
//        }    
//    }
//}

void main(void)     //Added heart beat LED
{
    unsigned char menu_cnt = 0, select = 0;
    unsigned char sw0_previous_state = 0, sw1_previous_state = 0; 
    unsigned char i = 0; // 0 to 255
    unsigned char delay_cnt = 0;
    unsigned char heartbeat_delay = 0;
    
    DDRA = 0x00;
    PORTA = 0xFF;
    
    DDRB = 0xFF;
    PORTB = 0x00;
    
    DDRC = 0xFF;
    PORTC = 0x00;
    
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
            
            menu_cnt++;
            if(menu_cnt > 3)
                menu_cnt = 0; 
            
            select = 0;
        }
        
        if(((PINA >> 1) & 0x01) == 0x01)
        {      
            sw1_previous_state = 1;    
        } 
        
        if(sw1_previous_state == 1 && ((PINA >> 1) & 0x01) == 0x00)
        {       
            delay_ms(200);
            sw1_previous_state = 0;
            
            PORTB = 0x00;
            i = 0; 
            delay_cnt = 0;
            select = 1;
        } 
        
        if(select == 0) 
        {
            PORTB = (1 << menu_cnt);
        }
        else
        {
            if(delay_cnt >= 20)  //20*50ms = 1000ms = 1s
            {   
                delay_cnt = 0;
                switch(menu_cnt)
                {
                    case 0:   //Menu 0 : BlinkingLED
                        PORTB = ~PORTB;
                    break;  
                
                    case 1:   //Menu 1 : UpCounterLED
                        i++;
                        PORTB = i;
                    break; 
                
                    case 2:   //Menu 2 : RingCounterLED
                        PORTB = (1 << i);
                        i++;
                        if(i >= 8)
                            i = 0;
                    break;   
                
                    case 3:   //Menu 3 : RingUpDownCounterLED
                        PORTB = PORTB ^ (1 << i);
                        i++;
                        if(i >= 8)
                            i = 0; 
                    break;
                } 
            }
            delay_cnt++;
        }
        
        if(heartbeat_delay == 0) 
        {
            heartbeat_delay = 10;     
                    
            // PORTC.0 = ~PORTC.0;
            // PORTC ^= (1 << 0);
            if(((PORTC >> 0) & 0x01) == 0x00)
                PORTC |= (1 << 0); 
            else
                PORTC &= ~(1 << 0);
        } 
        else
        {
            heartbeat_delay--;
        }        
        delay_ms(50);   
    }
}