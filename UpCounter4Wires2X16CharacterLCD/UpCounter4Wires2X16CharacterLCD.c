#include <mega16a.h>
#include <delay.h>
#include <stdio.h>

#include "lcd2x16_4wires.h"

void main(void)
{
    unsigned char i = 0;
    char str[20];
    
    lcd_init();
    lcd_clear();
    lcd_gotoxy(0,0);
    lcd_puts("   dibadigital   ");  
    delay_ms(1000);
    lcd_clear();
    
    while(1)
    {
         sprintf(str,"Value = %02d",i);
         lcd_gotoxy(0,0);
         lcd_puts(str);
         delay_ms(1000);
         i++;
         if(i > 99) 
         {
            i = 0;
            lcd_clear();
         }
    }
}
