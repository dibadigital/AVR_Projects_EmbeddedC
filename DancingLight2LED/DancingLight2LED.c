#include <mega16.h>
#include <delay.h>

void main(void)
{
    unsigned char x = 1, select = 0;
     
    DDRA = 0xFF;
    PORTA = 0x00;
    
    DDRB = 0xFF;
    PORTB = 0x00;
    
    DDRC = 0xFF;
    PORTC = 0x00;
    
    DDRD = 0xFF;
    PORTD = 0x00;
    
    while(1)
    {
       switch(select)
       {
            case 0:
                PORTA = x; 
                delay_ms(200);
                x = x << 1;
                if(x == 0)
                {
                    PORTA = 0;
                    select = 1;
                    x = 1;
                }
            break;
            
            case 1: 
                PORTB = x; 
                delay_ms(200);
                x = x << 1;
                if(x == 0)
                {
                    PORTB = 0;
                    select = 2;
                    x = 1;
                }
            break;
            
            case 2:    
                PORTC = x; 
                delay_ms(200);
                x = x << 1;
                if(x == 0)
                {
                    PORTC = 0;
                    select = 3;
                    x = 1;
                }
            break;
            
            case 3: 
                PORTD = x; 
                delay_ms(200);
                x = x << 1;
                if(x == 0)
                {
                    PORTD = 0;
                    select = 0;
                    x = 1;
                }
            break;
       }
    }
}