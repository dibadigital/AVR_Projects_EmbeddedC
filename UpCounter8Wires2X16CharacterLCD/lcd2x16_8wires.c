#include "lcd2x16_8wires.h"

void send_command(unsigned char command)
{
    delay_ms(2);
    CONTROL_PORT &= ~RS; //RS = 0
    CONTROL_PORT &= ~RW; //RW = 0
    CONTROL_PORT &= ~E;  //E = 0
    DATA_PORT = command;  
    CONTROL_PORT |= E;   //E = 1
    CONTROL_PORT &= ~E;  //E = 0
}

void lcd_init(void)
{
    delay_ms(2);
    DATA_DDR = 0xFF;
    CONTROL_DDR = 0xFF;
    send_command(0x38); //cofiguration 8 wires 
    send_command(0x06); //shift cursor to right
    send_command(0x0C); //turn on display and turn off cursor
}

void lcd_clear(void)
{
    delay_ms(2);
    send_command(0x01); //clear lcd
    send_command(0x02); //return curser
}

void lcd_gotoxy(unsigned char x, unsigned char y)
{
    delay_ms(2);
    switch(y)
    {
        case 0:
            send_command(0x80+x); //line 1, position x
            break;
            
        case 1:
            send_command(0xC0+x); //line 2, position x
            break;
    }
}

void lcd_putchar(char ch)
{
    delay_ms(2);
    CONTROL_PORT |= RS;  //RS = 1
    CONTROL_PORT &= ~RW; //RW = 0
    CONTROL_PORT &= ~E;  //E = 0
    DATA_PORT = ch;   
    CONTROL_PORT |= E;   //E = 1
    CONTROL_PORT &= ~E;  //E = 0
}

void lcd_puts(char *str)
{
    delay_ms(2);
    while(*str != 0)
    {
        lcd_putchar(*str);
        str++;
    }
}