#include <mega16a.h>
#include <delay.h>

#include "keypad4x4.h"

void main(void)
{   
    unsigned char a = 0;
    
    KeypadInit();
    SevenSegmentInit();
    
    while(1)
    {
        a = KeypadRead();
        if (a < 10)
            number = a;
        SevenSegmentUpdate();         
        //TimerHandler();
    }
}
