#include <mega16a.h>
#include <delay.h>

#include "keypad4x4.h"

void main(void)
{   
    unsigned char a = 0;
    
    DDRB = 0xFF;
    PORTB = 0x00;
    
    KeypadInit();
    
    while(1)
    {
        a = KeypadRead();
        if (a < 16)
        {
            PORTB = a;    
        } 
    }
}
