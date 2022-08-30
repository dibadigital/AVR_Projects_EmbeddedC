#include <mega16a.h>
#include <delay.h>

// Alphanumeric LCD functions
#include <alcd.h>

void main(void)
{
    unsigned char SevenSegmentCA[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
    
    enum menu_type{
        text1,
        text2,
        text3,
        text4,
        text5,
        text6,
        text1_menu,
        text2_menu,
        text3_menu,
        text4_menu,
        text5_menu,
        text6_menu
    }state;
     
    state = text1;
    
    DDRA = 0xFF;   //7SEG DIR
    PORTA = 0xFF;  //7SEG PORT
    
    DDRB &= 0xFC;  //Button DIR
    PORTB |= 0x03; //Button PORT
    
    DDRC = 0xFF;  //LCD DIR
    PORTC = 0x00; //LCD PORT
    
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
     
    PORTA = SevenSegmentCA[0];
    
    while (1)
    {       
        switch(state)
        {
            case text1: 
                lcd_gotoxy(0,0);
                lcd_putsf("Text.1 <=");
                lcd_gotoxy(0,1);
                lcd_putsf("Text.2");
                
                if(PINB.0 == 0)
                {
                    delay_ms(150);
                    while(PINB.0 == 0);
                    lcd_clear();
                    state = text2;
                }
      
                if(PINB.1 == 0)
                {
                    delay_ms(150);
                    while(PINB.1 == 0);
                    lcd_clear();
                    state = text1_menu;
                }
            break;
            
            case text2:
                lcd_gotoxy(0,0);
                lcd_putsf("Text.1");
                lcd_gotoxy(0,1);
                lcd_putsf("Text.2 <="); 
                
                if(PINB.0 == 0)
                {
                    delay_ms(150);
                    while(PINB.0 == 0);
                    lcd_clear();
                    state = text3;
                }
                
                if(PINB.1 == 0)
                {
                    delay_ms(150);
                    while(PINB.1 == 0);
                    lcd_clear();
                    state = text2_menu;
                }
            break;
            
            case text3:
                lcd_gotoxy(0,0);
                lcd_putsf("Text.3 <=");
                lcd_gotoxy(0,1);
                lcd_putsf("Text.4");  
                
                if(PINB.0 == 0)
                {
                    delay_ms(150);
                    while(PINB.0 == 0);
                    lcd_clear();
                    state = text4;
                }
                
                if(PINB.1 == 0)
                {
                    delay_ms(150);
                    while(PINB.1 == 0);
                    lcd_clear();
                    state = text3_menu;
                }
            break;
            
            case text4:
                lcd_gotoxy(0,0);
                lcd_putsf("Text.3");
                lcd_gotoxy(0,1);
                lcd_putsf("Text.4 <="); 
                
                if(PINB.0 == 0)
                {
                    delay_ms(150);
                    while(PINB.0 == 0);
                    lcd_clear();
                    state = text5;
                }
                
                if(PINB.1 == 0)
                {
                    delay_ms(150);
                    while(PINB.1 == 0);
                    lcd_clear();
                    state = text4_menu;
                }            
            break;
            
            case text5:
                lcd_gotoxy(0,0);
                lcd_putsf("Text.5 <=");
                lcd_gotoxy(0,1);
                lcd_putsf("Text.6");   
                
                if(PINB.0 == 0)
                {
                    delay_ms(150);
                    while(PINB.0 == 0);
                    lcd_clear();
                    state = text6;
                }
               
                if(PINB.1 == 0)
                {
                    delay_ms(150);
                    while(PINB.1 == 0);
                    lcd_clear();
                    state = text5_menu;
                }
            break;
            
            case text6:
                lcd_gotoxy(0,0);
                lcd_putsf("Text.5");
                lcd_gotoxy(0,1);
                lcd_putsf("Text.6 <=");
                 
                if(PINB.0 == 0)
                {
                    delay_ms(150);
                    while(PINB.0 == 0);
                    lcd_clear();
                    state = text1;
                }
                
                if(PINB.1 == 0)
                {
                    delay_ms(150);
                    while(PINB.1 == 0);
                    lcd_clear();
                    state = text6_menu;
                } 
            break;
            
            case text1_menu:
                lcd_gotoxy(0,0);
                lcd_putsf("-----Text.1-----");
                PORTA = SevenSegmentCA[1];  
                
                if(PINB.1 == 0)
                {
                    delay_ms(150);
                    while(PINB.1 == 0);
                    lcd_clear();
                    PORTA = SevenSegmentCA[0]; 
                    state = text1;
                }
            break;
            
            case text2_menu:
                lcd_gotoxy(0,0);
                lcd_putsf("-----Text.2-----");
                PORTA = SevenSegmentCA[2];
                
                if(PINB.1 == 0)
                {
                    delay_ms(150);
                    while(PINB.1 == 0);
                    lcd_clear();
                    PORTA = SevenSegmentCA[0]; 
                    state = text2;
                }
            break;
            
            case text3_menu:
                lcd_gotoxy(0,0);
                lcd_putsf("-----Text.3-----");
                PORTA = SevenSegmentCA[3];    
                
                if(PINB.1 == 0)
                {
                    delay_ms(150);
                    while(PINB.1 == 0);
                    lcd_clear();
                    PORTA = SevenSegmentCA[0]; 
                    state = text3;
                }
            break;
            
            case text4_menu:
                lcd_gotoxy(0,0);
                lcd_putsf("-----Text.4-----");
                PORTA = SevenSegmentCA[4];      
                
                if(PINB.1 == 0)
                {
                    delay_ms(150);
                    while(PINB.1 == 0);
                    lcd_clear();
                    PORTA = SevenSegmentCA[0]; 
                    state = text4;
                }
            break;
            
            case text5_menu:
                lcd_gotoxy(0,0);
                lcd_putsf("-----Text.5-----");
                PORTA = SevenSegmentCA[5];    
                
                if(PINB.1 == 0)
                {
                    delay_ms(150);
                    while(PINB.1 == 0);
                    lcd_clear();
                    PORTA = SevenSegmentCA[0]; 
                    state = text5;
                }
            break;
            
            case text6_menu:
                lcd_gotoxy(0,0);
                lcd_putsf("-----Text.6-----");
                PORTA = SevenSegmentCA[6];    
                
                if(PINB.1 == 0)
                {
                    delay_ms(150);
                    while(PINB.1 == 0);
                    lcd_clear();
                    PORTA = SevenSegmentCA[0]; 
                    state = text6;
                }
            break;
            
        }
    }
}
