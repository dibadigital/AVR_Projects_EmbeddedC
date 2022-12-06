#include <mega16a.h>
#include <delay.h>

void main(void)
{   
    DDRA = 0xFF;
    PORTA = 0x00;
    
    DDRB = 0x00;
    PORTB = 0x01;  
    
    DDRD = 0xFF;
    PORTD = 0x00;
    
    // Counter0, External Clock T0, Falling Edge    
    // Normal Mode
    // Normal port operation, oc0 disconnected
    TCCR0 = 0x06;
      
    TCNT0 = 246;
    while(1)
    {  
        PORTA = TCNT0;
        
        if((TIFR & (1 << 0)) == 0x01)
        {
            PORTD.0 = !PORTD.0; //Toggle PD0 
            TCNT0 = 246;
            TIFR = (1 << 0); //Alternatively, TOV0 is cleared by writing a logic one to the flag.
        }
    }
}
