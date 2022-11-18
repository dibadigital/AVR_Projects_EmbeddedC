#include <mega16a.h>
#include <delay.h>

unsigned char i = 0;  //0 to 255

// External Interrupt 0 service routine
interrupt [EXT_INT0] void isr_ext_int0(void) //EXT_INT0 : PD2
{
    i++;                  
    PORTB = i;
}

void main(void)
{
    DDRB = 0xFF;
    PORTB = 0x00;
    
    DDRD &= ~(1 << 2);
    PORTD |= (1 << 2);
        
    // External Interrupt : INT0, Mode: Rising Edge
    MCUCR = 0x03;    
    GICR = 0x40;

    // Global enable interrupts
    #asm("sei")

    while(1)
    {
            
    }
}
