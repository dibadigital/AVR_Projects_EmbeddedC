#include <mega16a.h>
#include <delay.h>
#include "traffic_light.h"

void main(void)
{
    unsigned char s = 0;
    
    DDRB = 0xFF;
    PORTB = 0x00;
    
    DDRC = 0xFF;
    PORTC = 0xFF;
    
    DDRD = 0xFF;
    PORTD = 0x00;
     
    calculate_digits(i);
        
    while(1)
    {
       switch(s)
       {
            case STATE_G:
                show(s);
                PORTB = 0x01;
                if(flag_change_state == 1)
                {
                    flag_change_state = 0;
                    s = STATE_Y;
                }
            break;
            
            case STATE_Y:
                show(s);
                PORTB = 0x02; 
                if(flag_change_state == 1)
                {
                    flag_change_state = 0;
                    s = STATE_R;
                }
            break;
            
            case STATE_R:
                show(s);
                PORTB = 0x04;
                if(flag_change_state == 1)
                {
                    flag_change_state = 0;
                    s = STATE_G;
                }
            break;
       } 
    }
}
