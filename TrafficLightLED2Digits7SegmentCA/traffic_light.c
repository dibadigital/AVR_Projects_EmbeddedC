#include "traffic_light.h"

const unsigned char SevenSegmentCA[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
signed char i = iG;
uint16_t delay_cnt = 0;
unsigned char digitIdx = 0;
unsigned char digits[2] = {0};
unsigned char flag_change_state = 0;

void calculate_digits(signed char j)
{
   unsigned char n = 0;
    
   for (n=0; n<2; n++)
   {
        digits[n] = j%10;
        j = j/10; 
   }
}

void show(unsigned char s)
{     
    if(s != STATE_Y) 
        PORTD = (1 << digitIdx);  
    else
        PORTD = 0x00;                    
    PORTC = SevenSegmentCA[digits[digitIdx]];  
    digitIdx++;   
    if(digitIdx > 1)
        digitIdx = 0;
    delay_ms(2);
    
    delay_cnt++;
    if(delay_cnt >= 500)
    {
        delay_cnt = 0;
        i--;
        if(i < 0)  
        {
            switch(s)
            {
                case STATE_G:
                    i = iY;
                break;
                
                case STATE_Y:
                   i = iR;
                break;
                
                case STATE_R:
                  i = iG;
                break;
            }   
            flag_change_state = 1; 
        }
            
        calculate_digits(i);
    } 
}