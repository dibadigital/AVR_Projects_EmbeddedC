#include "AdjustableBlinking.h"

const unsigned char SevenSegmentCA[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
unsigned char digits[4] = {0};
unsigned char digitIdx = 0;
unsigned char previous_state_clk = 1, previous_state_sw = 1;
int16_t key_cnt = 0;  
unsigned char delay_cnt = 0; 
unsigned char flag_blinking = 0;

void RotaryEncoderVolInit(void)
{
    DDRA = 0x00;
    PORTA = 0x00;  
    previous_state_clk = ((PINA >> 0) & 0x01);
}

void RotaryEncoderVolRead(void)
{
    if(((PINA >> 0) & 0x01) != previous_state_clk) //positive & negative edges of clk
    {
        previous_state_clk = ((PINA >> 0) & 0x01);
        if(((PINA >> 1) & 0x01) == ((PINA >> 0) & 0x01)) 
        {
            if(key_cnt > 0)
                key_cnt--;
        }
        else
        {
            if(key_cnt < 9999)
                key_cnt++;  
        }
    } 
    
    if(((PINA >> 2) & 0x01) == 0x01)  
    {
        previous_state_sw = 1;
    }       
    if(previous_state_sw == 1 && ((PINA >> 2) & 0x01) == 0x00)  
    {  
        delay_ms(200);
        previous_state_sw = 0;
        if(key_cnt > 0)
            flag_blinking = 1;  
    }
}

void BlinkingFunc(void)
{ 
    if(flag_blinking == 1)
    {   
        if(delay_cnt == 100) //200ms   
        {     
            delay_cnt = 0;
            PORTB = ~PORTB;   
            if(PORTB == 0)  
            {
                key_cnt--; 
                if(key_cnt == 0)
                    flag_blinking = 0; 
            }  
                    
        }
    }
}

void LEDInit(void)
{
    DDRB = 0xFF;
    PORTB = 0x00;
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
    if(digitIdx > 3)
        digitIdx = 0;
}

void TimerHandler(void)
{
    delay_ms(2);          
    delay_cnt++;
}
