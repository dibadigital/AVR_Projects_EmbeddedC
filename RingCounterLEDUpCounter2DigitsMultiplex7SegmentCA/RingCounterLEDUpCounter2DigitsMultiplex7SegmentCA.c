#include <mega16a.h>
#include <delay.h>

void main(void)
{
    unsigned char SevenSegmentCA[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
    unsigned char digits[2] = {0};
    unsigned char i = 0, j = 0, n = 0;
    unsigned int delay_cnt_7seg = 0, delay_cnt_led = 0;
    unsigned char digitIdx = 0; 
    unsigned char x = 0;
    
    DDRB = 0xFF;
    PORTB = 0x00;
    
    DDRC = 0xFF;
    PORTC = 0xFF;
    
    DDRD = 0xFF;
    PORTD = 0x00;
    
    while(1)
    {
        PORTD = (1 << digitIdx);                         
        PORTC = SevenSegmentCA[digits[digitIdx]];  
        digitIdx++;   
        if(digitIdx > 1)
            digitIdx = 0;
       
        delay_ms(2);
       
        delay_cnt_7seg++;
        if(delay_cnt_7seg >= 500)
        {
            delay_cnt_7seg = 0;
            i++;
            if(i > 99)
                i = 0; 
            
            j = i;
            for (n=0; n<2; n++)
            {
                digits[n] = j%10;
                j = j/10; 
            }
        } 
        
        delay_cnt_led++;
        if(delay_cnt_led >= 100)
        {
            delay_cnt_led = 0;
            PORTB = (1 << x);
            x++;
            if(x >= 8)  
            {
                x = 0;
            }
        }
    }
}