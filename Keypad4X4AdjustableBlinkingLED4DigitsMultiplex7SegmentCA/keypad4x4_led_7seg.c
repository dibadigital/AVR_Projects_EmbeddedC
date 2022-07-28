#include "keypad4x4_led_7seg.h"

const unsigned char SevenSegmentCA[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
unsigned char digitIdx = 0;
unsigned char digits[4] = {0};

const unsigned char KeypadMatrix[4][4] = {{7,8,9,10},{4,5,6,11},{1,2,3,12},{14,0,15,13}};
unsigned char C_previous[4] = {0};
unsigned char key = 0, key_previous = 0;
unsigned char debouncer = 0, keyReady = 0;
int16_t number = 0;

unsigned char delay_cnt = 0; 
unsigned char flag_blinking = 0;

void LEDInit(void)
{
    DDRB = 0xFF;
    PORTB = 0x00;
}

void BlinkingFunc(void)
{ 
    if(flag_blinking == 1)
    {   
        if(delay_cnt == 200) //200*5ms = 1000ms   
        {     
            delay_cnt = 0;
            PORTB = ~PORTB;   
            if(PORTB == 0)  
            {
                number--;  
                SevenSegmentWrite(number);
                if(number == 0)
                    flag_blinking = 0; 
            }  
                    
        }
    }
}

void KeypadInit(void)
{
    DDRA = 0x0F;
    PORTA = 0xFF;
}

unsigned char GetEdge(void)
{
    unsigned char flag_edge = 0;
    
    R1 = 0; R2 = 0; R3 = 0; R4 = 0;
    delay_ms(1);  //Because half of the port is input and half of the port is output. 
    if((C1 == 0 && C_previous[0]==1) ||
       (C2 == 0 && C_previous[1]==1) ||
       (C3 == 0 && C_previous[2]==1) ||
       (C4 == 0 && C_previous[3]==1))  
     {
       flag_edge = 1;
     }
   
    C_previous[0] = C1;
    C_previous[1] = C2;  
    C_previous[2] = C3;  
    C_previous[3] = C4;
    
    return flag_edge;
}

unsigned char KeypadRead(void)
{
    unsigned char x = 16;
    
    R1 = 0; R2 = 1; R3 = 1; R4 = 1;
    delay_ms(1);  //Because half of the port is input and half of the port is output.
    if (C1 == 0){x = KeypadMatrix[0][0];}
    if (C2 == 0){x = KeypadMatrix[0][1];}
    if (C3 == 0){x = KeypadMatrix[0][2];}
    if (C4 == 0){x = KeypadMatrix[0][3];}
    
    R1 = 1; R2 = 0; R3 = 1; R4 = 1;
    delay_ms(1);  //Because half of the port is input and half of the port is output.
    if (C1 == 0){x = KeypadMatrix[1][0];}
    if (C2 == 0){x = KeypadMatrix[1][1];}
    if (C3 == 0){x = KeypadMatrix[1][2];}
    if (C4 == 0){x = KeypadMatrix[1][3];}
    
    R1 = 1; R2 = 1; R3 = 0; R4 = 1;
    delay_ms(1);  //Because half of the port is input and half of the port is output.
    if (C1 == 0){x = KeypadMatrix[2][0];}
    if (C2 == 0){x = KeypadMatrix[2][1];}
    if (C3 == 0){x = KeypadMatrix[2][2];}
    if (C4 == 0){x = KeypadMatrix[2][3];}
    
    R1 = 1; R2 = 1; R3 = 1; R4 = 0;
    delay_ms(1);  //Because half of the port is input and half of the port is output.
    if (C1 == 0){x = KeypadMatrix[3][0];}
    if (C2 == 0){x = KeypadMatrix[3][1];}
    if (C3 == 0){x = KeypadMatrix[3][2];}
    if (C4 == 0){x = KeypadMatrix[3][3];}

    return x; 
}

unsigned char KeypadFunc(void)
{  
    unsigned char flag_out = 0;
    
    key = KeypadRead();
    if(key != key_previous) //To avoid bouncing the key
    {   
        key_previous = key;
        debouncer = 0;
        keyReady = 0;   
    } 
    else
    {  
        if(key != 16)
        {    
            debouncer++;
            if(debouncer == 10) //10*5ms = 50ms
            {
                debouncer = 0;
                keyReady = 1; 
                flag_out = 1;
            } 
        }
        else
        {
            key_previous = key;
            debouncer = 0;
            keyReady = 0;
        }
    }
    
    if(keyReady == 1)
    {
        keyReady = 0;          
        if(key < 10)  
        {
            if(number <= 999)   
            {
                number = (number * 10) + key; 
                SevenSegmentWrite(number);  
            }
        }
        else if(key == KeypadMatrix[3][0]) //14
        {       
            if(number > 0)    
            {
                number = number / 10; 
                SevenSegmentWrite(number);  
            }
        }
        else if(key == KeypadMatrix[3][2]) //15
        {  
            if(number > 0)
                flag_blinking = 1;
        }  
    } 
    
    return flag_out;
}

void SevenSegmentInit(void)
{
    DDRC = 0xFF;
    PORTC = 0xFF;

    DDRD = 0xFF;
    PORTD = 0x00;    
}

void SevenSegmentWrite(uint16_t number)
{
    unsigned char n = 0; 
        
    for (n=0; n<4; n++)
    {
        digits[n] = number%10;
        number = number/10;    
    }
}

void SevenSegmentUpdate(void)
{
    PORTD = (1 << digitIdx); 
    PORTC = SevenSegmentCA[digits[digitIdx]]; 
    digitIdx++;
    if (digitIdx >= 4)
        digitIdx = 0;
}

void TimerHandler(void)
{
    //delay_ms(2);  
    delay_cnt++;
}



