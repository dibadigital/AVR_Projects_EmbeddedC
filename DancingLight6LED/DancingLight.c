#include "DancingLight.h"

void GPIO_INIT(port *p)
{
    DDRA = p -> PA_DIR;
    DDRB = p -> PB_DIR;
    DDRC = p -> PC_DIR;
    DDRD = p -> PD_DIR; 
    
    PORTA = p -> PA_PORT;
    PORTB = p -> PB_PORT;
    PORTC = p -> PC_PORT;
    PORTD = p -> PD_PORT;
}