#include <mega16a.h>
#include <delay.h>

unsigned char SevenSegmentCA[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
unsigned char flag = 0;
    
void display(unsigned char counter);

// External Interrupt 0 service routine
interrupt [EXT_INT0] void isr_ext_int0(void) //EXT_INT0 : PD2
{
    flag = !flag;
}

void main(void)
{
    unsigned char i = 0;
    
    DDRC = 0xFF;
    PORTC = 0xFF;
    
    DDRD |= 0x03;
    PORTD |= 0x00;
      
    DDRD &= ~(1 << 2);
    PORTD |= (1 << 2);
        
    // External Interrupt : INT0, Mode: Rising Edge
    MCUCR = 0x03;    
    GICR = 0x40;

    // Global enable interrupts
    #asm("sei")
      
    while(1)
    {
        if(flag == 1)
        {
            for(i=0; i<100; i+=2)
            {
                display(i);
            }
        }
        else
        {
            for(i=1; i<100; i+=2)
            {
                display(i);
            }
        }
       
    }
}

void display(unsigned char counter)
{
    unsigned char j = 0, n = 0;
    unsigned char digits[2] = {0};
    signed int delay_cnt = 50;
       
    j = counter;
    for (n=0; n<2; n++)
    {
        digits[n] = j%10;
        j = j/10; 
    }  
        
    while(delay_cnt > 0)
    {
        PORTD.0 = 1;                         
        PORTC = SevenSegmentCA[digits[0]]; 
        delay_ms(5);  
        PORTD.0 = 0;   
            
        PORTD.1 = 1;                         
        PORTC = SevenSegmentCA[digits[1]];  
        delay_ms(5); 
        PORTD.1 = 0;  
        
        delay_cnt--;
    }
}
