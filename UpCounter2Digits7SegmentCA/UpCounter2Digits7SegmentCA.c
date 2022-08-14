#include <mega16a.h>
#include <delay.h>

//void main(void)
//{
//    unsigned char SevenSegmentCA[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90}; 
//    unsigned char i = 0, j = 0;
//    
//    DDRC = 0xFF; 
//    PORTC = 0xFF;
//    
//    DDRD = 0xFF; 
//    PORTD = 0xFF;
//    
//    while(1)
//    {
//        PORTC = SevenSegmentCA[i];
//        PORTD = SevenSegmentCA[j];
//        j++;
//        if(j > 9)
//        {
//            j = 0;
//            i++;
//            if(i > 9)
//                i = 0;
//        }
//        delay_ms(1000); 
//    }
//}

void main(void)
{
    unsigned char SevenSegmentCA[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
    unsigned char i = 0;   
    
    DDRC = 0xFF;
    PORTC = 0xFF;
    
    DDRD = 0xFF;
    PORTD = 0xFF;
    
    while(1)
    {                        
       PORTC = SevenSegmentCA[i/10];
       PORTD = SevenSegmentCA[i%10];   
       i++;
       if(i > 99)
          i = 0;
       delay_ms(1000);
            
    }
}
