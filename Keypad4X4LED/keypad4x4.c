#include "keypad4x4.h"

void KeypadInit(void)
{
    DDRA = 0x0F;
    PORTA = 0xFF;
}

unsigned char KeypadRead(void)
{
    unsigned char x = 16;
    
    R1 = 0; R2 = 1; R3 = 1; R4 = 1;
    delay_ms(1);
    if (C1 == 0){delay_ms(200); x = 7;}
    if (C2 == 0){delay_ms(200); x = 8;}
    if (C3 == 0){delay_ms(200); x = 9;}
    if (C4 == 0){delay_ms(200); x = 10;}
    
    R1 = 1; R2 = 0; R3 = 1; R4 = 1;
    delay_ms(1);
    if (C1 == 0){delay_ms(200); x = 4;}
    if (C2 == 0){delay_ms(200); x = 5;}
    if (C3 == 0){delay_ms(200); x = 6;}
    if (C4 == 0){delay_ms(200); x = 11;}
    
    R1 = 1; R2 = 1; R3 = 0; R4 = 1;
    delay_ms(1);
    if (C1 == 0){delay_ms(200); x = 1;}
    if (C2 == 0){delay_ms(200); x = 2;}
    if (C3 == 0){delay_ms(200); x = 3;}
    if (C4 == 0){delay_ms(200); x = 12;}
    
    R1 = 1; R2 = 1; R3 = 1; R4 = 0;
    delay_ms(1);
    if (C1 == 0){delay_ms(200); x = 14;}
    if (C2 == 0){delay_ms(200); x = 0;}
    if (C3 == 0){delay_ms(200); x = 15;}
    if (C4 == 0){delay_ms(200); x = 13;}
    
    return x; 
}

