#include <mega16a.h>

// Alphanumeric LCD functions
#include <alcd.h>

#include "lock.h"

void main(void)
{
    DDRC = 0xFF;  //LCD DIR
    PORTC = 0x00; //LCD PORT
     
    KeypadInit();
    BuzzerInit(); 
    RelayInit();
    
    // Alphanumeric LCD initialization
    // Connections are specified in the
    // Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
    // RS - PORTC Bit 0
    // RD - PORTC Bit 1
    // EN - PORTC Bit 2
    // D4 - PORTC Bit 4
    // D5 - PORTC Bit 5
    // D6 - PORTC Bit 6
    // D7 - PORTC Bit 7
    // Characters/line: 16
    lcd_init(16);
           
    lcd_clear();
    lcd_gotoxy(0,0);
    lcd_puts("  dibadigital  ");
            
    Buzzer_Relay_write(0, 1);  //SET Buzzer
    delay_ms(200);
    Buzzer_Relay_write(0, 0);  //RESET Buzzer
    delay_ms(200);
    
    while (1)
    {
        lock_process(); 
        buzzer_process();   
        delay_ms(10);
    }
}
