#include <mega16.h>
#include <delay.h>

//void main(void)
//{
//    unsigned char data[50] = "Time = 10, Temp = 21, Speed = 56";
//    unsigned char i = 0, number = 0, a = 0, b = 0;
//    
//    DDRC = 0xFF;
//    PORTC = 0x00;
//    
//    while(1)
//    { 
//        for(i=0;i<50;i++)
//            if((data[i]=='S')&&(data[i+1]=='p')&&(data[i+2]=='e')&&(data[i+3]=='e')&&(data[i+4]=='d'))
//                break;
//             
//        number = (data[i+8]-48)*10+(data[i+9]-48);
//        a = number/10;
//        b = number%10;
//        PORTC = (a << 4) | b;        
//    }
//}

void main(void)
{
    unsigned char data[50] = "Time = 10, Temp = 21, Speed = 56";
    unsigned char i = 0;
    
    DDRC = 0xFF;
    PORTC = 0x00;
    
    while(1)
    { 
        for(i=0;i<50;i++)
            if((data[i]=='S')&&(data[i+1]=='p')&&(data[i+2]=='e')&&(data[i+3]=='e')&&(data[i+4]=='d'))
                break;
        
        // +48 = 32 + 16 = 00110000            
        PORTC = ((data[i+8]&0x0F) << 4) | (data[i+9]&0x0F); 
    }
}