#include <mega16a.h>
#include <delay.h>

void main(void)
{
    unsigned char SevenSegmentCA[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
    unsigned char i = 0;
    int delay_cnt = 0;
    
    DDRC = 0xFF;
    PORTC = 0xFF;
    
    DDRD = 0xFF;
    PORTD = 0x01;
    
    while(1)
    { 
        // T = t_on + t_off = 1  us + 15 ms = 15 ms    
        // N_refresh = f = 1/T = 1/15ms = 1000/15 = 66.66 Hz
        //Duty Cycle = 100 * (t_on/(t_on+t_off)) = 100 * (1 us / 15 ms) = 0.006  
                
       PORTD.0 = 1;
       PORTC = SevenSegmentCA[i];     
       delay_us(1);        
       PORTD.0 = 0;
       delay_ms(15);
          
       delay_cnt++;
       if(delay_cnt > 40)
       {       
            delay_cnt = 0;
            i++;
            if(i > 9)
                i = 0;
       } 
    }
}
