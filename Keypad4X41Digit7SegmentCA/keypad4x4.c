#include "keypad4x4.h"

const unsigned char SevenSegmentCA[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
unsigned char number = 0;

void KeypadInit(void)
{
    DDRA = 0x0F;
    PORTA = 0xFF;
}

unsigned char KeypadRead(void)
{
    unsigned char x = 16;
    
    R1 = 0; R2 = 1; R3 = 1; R4 = 1;
    delay_ms(1);  //Because half of the port is input and half of the port is output.
    if (C1 == 0){x = 7;}
    if (C2 == 0){x = 8;}
    if (C3 == 0){x = 9;}
    if (C4 == 0){x = 10;}
    
    R1 = 1; R2 = 0; R3 = 1; R4 = 1;
    delay_ms(1);  //Because half of the port is input and half of the port is output.
    if (C1 == 0){x = 4;}
    if (C2 == 0){x = 5;}
    if (C3 == 0){x = 6;}
    if (C4 == 0){x = 11;}
    
    R1 = 1; R2 = 1; R3 = 0; R4 = 1;
    delay_ms(1);  //Because half of the port is input and half of the port is output.
    if (C1 == 0){x = 1;}
    if (C2 == 0){x = 2;}
    if (C3 == 0){x = 3;}
    if (C4 == 0){x = 12;}
    
    R1 = 1; R2 = 1; R3 = 1; R4 = 0;
    delay_ms(1);  //Because half of the port is input and half of the port is output.
    if (C1 == 0){x = 14;}
    if (C2 == 0){x = 0;}
    if (C3 == 0){x = 15;}
    if (C4 == 0){x = 13;}

    return x; 
}

void SevenSegmentInit(void)
{
    DDRC = 0xFF;
    PORTC = 0x00;

    DDRD = 0x0FF;
    PORTD = 0x01;    
}

void SevenSegmentUpdate(void)
{
    PORTC = SevenSegmentCA[number];
}

//void TimerHandler(void)
//{
//    delay_ms(2);
//}
