#include <mega16a.h>
#include <delay.h>
#include <stdio.h>

// Alphanumeric LCD functions
#include <alcd.h>

#include "calculator.h"

void main(void)
{
    unsigned char flag_keypad = 0;
        
    DDRC = 0xFF;  //LCD DIR
    PORTC = 0x00; //LCD PORT
    
    KeypadInit();
    
    // Alphanumeric LCD initialization
    // RS - PORTC Bit 0
    // RD - PORTC Bit 1
    // EN - PORTC Bit 2
    // D4 - PORTC Bit 4
    // D5 - PORTC Bit 5
    // D6 - PORTC Bit 6
    // D7 - PORTC Bit 7
    // Characters/line: 16
    lcd_init(16);
    
    lcd_process(); 
    
    while (1)
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
    }
}
