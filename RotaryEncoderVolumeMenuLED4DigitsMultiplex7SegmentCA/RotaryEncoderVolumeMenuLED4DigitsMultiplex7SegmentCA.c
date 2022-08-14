#include <mega16a.h>
#include <delay.h>
#include <stdint.h>

void main(void) //The Rotary Encoder Volume used creates an edge with each step change.
{
    unsigned char SevenSegmentCA[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
    unsigned char digits[4] = {0};  
    unsigned char j = 0;
    unsigned char n = 0;
    unsigned char digitIdx = 0;
    
    unsigned char previous_state_clk = 1, previous_state_sw = 1;
    unsigned char menu_cnt = 1;  
    unsigned char delay_cnt = 0; 
    unsigned char select = 0;  
    unsigned char i = 0; // 0 to 255
    
    DDRA = 0x00;
    PORTA = 0x00;
    
    DDRB = 0xFF;
    PORTB = 0x00;
    
    DDRC = 0xFF;
    PORTC = 0xFF;
    
    DDRD = 0xFF;
    PORTD = 0x00;
    
    previous_state_clk = ((PINA >> 0) & 0x01);
    
    while(1)
    {
        if(((PINA >> 0) & 0x01) != previous_state_clk) //positive & negative edges of clk
        {
            previous_state_clk = ((PINA >> 0) & 0x01);
            if(select == 0)
            {
                if(((PINA >> 1) & 0x01) == ((PINA >> 0) & 0x01)) 
                {
                    if(menu_cnt > 1)
                        menu_cnt--;
                }
                else
                {
                    if(menu_cnt < 4)
                        menu_cnt++;  
                }  
            }
        }  
        
        if(((PINA >> 2) & 0x01) == 0x01)  
        {
            previous_state_sw = 1;
        }       
        if(previous_state_sw == 1 && ((PINA >> 2) & 0x01) == 0x00)  
        {  
            delay_ms(200);
            previous_state_sw = 0;
            select = !select;  
            if(select == 0)
            {
                PORTB = 0x00;
                i = 0; 
                delay_cnt = 0;
            }
        }
        
        if(select == 1)
        {   
            if(delay_cnt == 100) //200ms   
            {     
                delay_cnt = 0;
                switch(menu_cnt)
                {
                    case 1:   //Menu 1 : BlinkingLED
                        PORTB = ~PORTB;
                    break;  
                
                    case 2:   //Menu 2 : UpCounterLED
                        i++;
                        PORTB = i;
                    break; 
                
                    case 3:   //Menu 3 : RingCounterLED
                        PORTB = (1 << i);
                        i++;
                        if(i >= 8)
                            i = 0;
                    break;   
                
                    case 4:   //Menu 4 : RingUpDownCounterLED
                        PORTB = PORTB ^ (1 << i);
                        i++;
                        if(i >= 8)
                            i = 0; 
                    break;
                }       
            }
        }
         
        j = menu_cnt; 
        for (n=0; n<4; n++)
        {
           digits[n] = j%10;
           j = j/10; 
        }
        PORTD = (1 << digitIdx);                         
        PORTC = SevenSegmentCA[digits[digitIdx]];  
        digitIdx++;   
        if(digitIdx > 3)
            digitIdx = 0;
        delay_ms(2);    
        
        delay_cnt++;
    }
}
