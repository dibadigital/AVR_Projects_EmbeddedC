#include <mega16.h>
#include <delay.h>

//void main(void) //The Rotary Encoder Volume used creates an edge with each step change.
//{
//    unsigned char previous_state_clk = 1;
//    
//    DDRA = 0x00;
//    PORTA = 0x00;
//    
//    DDRB = 0xFF;
//    PORTB = 0x00;
//    
//    while(1)
//    {
//        if(previous_state_clk == 0 && ((PINA >> 0) & 0x01) == 1) //positive edges of clk
//        {
//            previous_state_clk = 1;
//            if(((PINA >> 1) & 0x01) == 0) 
//                PORTB++;
//            else
//                PORTB--;
//        }      
//        else if(previous_state_clk == 1 && ((PINA >> 0) & 0x01) == 0) //negative edges of clk
//        {
//            previous_state_clk = 0;
//            if(((PINA >> 1) & 0x01) == 1)
//                PORTB++;
//            else
//                PORTB--;
//        } 
//        
//    }
//}

void main(void) //The Rotary Encoder Volume used creates an edge with each step change.
{
    unsigned char previous_state_clk = 1;
    
    DDRA = 0x00;
    PORTA = 0x00;
    
    DDRB = 0xFF;
    PORTB = 0x00;
    
    previous_state_clk = ((PINA >> 0) & 0x01);
    
    while(1)
    {
        if(((PINA >> 0) & 0x01) != previous_state_clk) //positive & negative edges of clk
        {
            previous_state_clk = ((PINA >> 0) & 0x01);
            if(((PINA >> 1) & 0x01) == ((PINA >> 0) & 0x01))
                PORTB--;
            else
                PORTB++;
        } 
        
    }
}