#include <mega16a.h>
#include <delay.h>

#include "keypad4x4_7seg.h"

void main(void)
{   
    unsigned char flag_keypad = 0;
    
    KeypadInit();
    SevenSegmentInit();
    
    while(1)
    {  
        if(GetEdge() == 1) //To avoid holding the key
        {
            if(KeypadRead() != 16) 
                flag_keypad = 1;
        }
    
        if(flag_keypad == 1)
        {       
            unsigned char flag_stop = KeypadFunc();
            if(flag_stop == 1)
                flag_keypad = 0;
        }
        
        SevenSegmentUpdate();  
        //TimerHandler();
    }
}
