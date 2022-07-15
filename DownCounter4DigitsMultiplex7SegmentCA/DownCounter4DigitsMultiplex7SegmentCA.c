#include <mega16.h>
#include <delay.h>
#include <stdint.h>

void main(void)
{
    unsigned char SevenSegmentCA[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
    unsigned char digits[4] = {0};
    int16_t i = 9999, j = 0;
    unsigned char n = 0;
    unsigned int delay_cnt = 0;
    unsigned char digitIdx = 0;
    
    DDRC = 0xFF;
    PORTC = 0xFF;
    
    DDRD = 0xFF;
    PORTD = 0x00;
    
    j = i;
    for (n=0; n<4; n++)
    {
    digits[n] = j%10;
    j = j/10; 
    }
                    
    while(1)
    {         
       PORTD = (1 << digitIdx);                         
       PORTC = SevenSegmentCA[digits[digitIdx]];  
       digitIdx++;   
       if(digitIdx > 3)
            digitIdx = 0;
       
       delay_ms(2);
       
       delay_cnt++;
       if(delay_cnt >= 500)
       {
          delay_cnt = 0;
          i--;
          if(i < 0)
            i = 9999; 
            
          j = i;
          for (n=0; n<4; n++)
          {
            digits[n] = j%10;
            j = j/10; 
          }
       }
       
    }
}