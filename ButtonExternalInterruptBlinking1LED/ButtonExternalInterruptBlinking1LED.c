#include <mega16a.h>
#include <delay.h>

// External Interrupt 0 service routine
interrupt [EXT_INT0] void isr_ext_int0(void) //EXT_INT0 : PD2
{                  
    PORTB = 0x00;
}


// External Interrupt 1 service routine
interrupt [EXT_INT1] void isr_ext_int1(void) //EXT_INT1 : PD3
{                
    PORTB = 0xFF;
}

void main(void)
{
    DDRB = 0xFF;
    PORTB = 0x00;
    
    DDRD &= ~(1 << 2);
    PORTD |= (1 << 2);    
    
    DDRD &= ~(1 << 3);
    PORTD |= (1 << 3);
        
    // External Interrupt : INT0, Mode: Rising Edge
    // External Interrupt : INT1,  Mode: Falling Edge
    MCUCR = 0x0B; // MCUCR |= 0x03;  MCUCR |= 0x08;   
    GICR = 0xC0;  //  GICR |= 0x40;   GICR |= 0x80;

    // Global enable interrupts
    #asm("sei")

   
    while(1)
    {
            
    }
}