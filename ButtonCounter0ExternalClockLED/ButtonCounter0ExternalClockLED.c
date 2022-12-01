#include <mega16a.h>
#include <delay.h>

void main(void)
{   
    DDRA = 0xFF;
    PORTA = 0x00;
    
    DDRB = 0x00;
    PORTB = 0x01;
    
    // Counter0, External Clock T0, Falling Edge    
    // Normal Mode
    // Normal port operation, oc0 disconnected
    TCCR0 = 0x06;
    
    while(1)
    {  
        PORTA = TCNT0;
    }
}
