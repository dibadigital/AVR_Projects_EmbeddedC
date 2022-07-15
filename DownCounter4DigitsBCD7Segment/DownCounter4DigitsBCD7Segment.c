#include <mega16.h>
#include <delay.h>
#include <stdint.h>

void main(void)
{
    int16_t x = 9999, x_copy = 0;  
    unsigned char digits[4] = {0}; 
    unsigned char n = 0;
    
    DDRC = 0xFF;
    PORTC = 0x00;   
    
    DDRD = 0xFF;
    PORTD = 0x00;  
    
    while(1)
    { 
       x_copy = x;
       for (n=0; n<4; n++)
       {
            digits[n] = x_copy%10;
            x_copy = x_copy/10; 
       }
       PORTC = (digits[3] << 4) | digits[2];  
       PORTD = (digits[1] << 4) | digits[0];
       delay_ms(500);
       x--;
       if(x < 0)
        x = 9999; 
    }
}