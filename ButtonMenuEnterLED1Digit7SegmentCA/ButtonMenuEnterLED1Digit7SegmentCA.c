#include <mega16a.h>
#include <delay.h>
#include <stdint.h>

void main(void)
{
    unsigned char SevenSegmentCA[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};    
    unsigned char sw0_previous_state = 0, sw1_previous_state = 0;
    unsigned char menu_cnt = 0;  
    unsigned char delay_cnt = 0; 
    unsigned char select = 0;  
    unsigned char i = 0; // 0 to 255
    
    DDRA = 0x00;
    PORTA = 0xFF;
    
    DDRB = 0xFF;
    PORTB = 0x00;
    
    DDRC = 0xFF;
    PORTC = 0xFF;
    
    
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
            PORTB = 0x00; 
            PORTC = SevenSegmentCA[menu_cnt+1];
        }
        else
        {
            if(delay_cnt >= 100)  //100*5ms = 200ms
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
        }
        
        delay_ms(2);
        delay_cnt++;
    }
}