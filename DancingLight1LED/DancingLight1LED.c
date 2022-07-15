#include <mega16.h>
#include <delay.h>

//void main(void)
//{
//    signed char a = 0;
//    unsigned char select = 0;
//
//    DDRB = 0xFF;
//    PORTB = 0x00;
//    
//    while(1)
//    {
//        PORTB = ((1 << a) << 4) | (1 << (3-a));
//        
//        if(select == 0)
//        {
//            a++;
//            if(a > 3)  
//            { 
//                a = 2;
//                select = !select;
//            } 
//        }
//        else
//        {
//            a--;
//            if(a < 0)
//            {
//               a = 1;
//               select = !select;
//            }
//        }
//        delay_ms(300);
//    }
//}

//void main(void)
//{
//    unsigned char x = 0x80, y = 0x01;
//    unsigned char select = 0; 
//    
//    DDRB = 0xFF;
//    PORTB = 0x00;
//    
//    while(1)
//    {
//         if(select == 0)
//         {
//            PORTB = x|y;
//            delay_ms(300);
//            x >>= 1;
//            y <<= 1;
//            if(x == 0x10)
//                select = 1;
//         }
//         else
//         {
//            PORTB = x|y;
//            delay_ms(300);
//            x <<= 1;
//            y >>= 1;
//            if(x == 0x80)
//                select = 0;
//         }
//    }
//}

void main(void)
{
    unsigned char select = 0, i = 0;
    unsigned char arr[4] = {0x81, 0x42, 0x24, 0x18};
    
    DDRB = 0xFF;
    PORTB = 0x00;
    
    while(1)
    {
        if(select == 0)
        {
            PORTB = arr[i];
            delay_ms(300);
            i++;
            if(i == 3)
                select = 1;
        }
        else
        {
            PORTB = arr[i];
            delay_ms(300);
            i--;
            if(i == 0)
                select = 0;
        }
    }
}