#include "lcd2x16_4wires.h"

void send_command(unsigned char command)
{
    delay_ms(2);
    DATA_CONTROL_PORT &= ~RS; //RS = 0
    DATA_CONTROL_PORT &= ~RW; //RW = 0
    DATA_CONTROL_PORT &= ~E;  //E = 0   
    DATA_CONTROL_PORT &= 0x0F;
    DATA_CONTROL_PORT |= (command & 0xF0);
    DATA_CONTROL_PORT |= E;   //E = 1
    DATA_CONTROL_PORT &= ~E;  //E = 0     
    
    delay_ms(2);
    DATA_CONTROL_PORT &= ~RS; //RS = 0
    DATA_CONTROL_PORT &= ~RW; //RW = 0
    DATA_CONTROL_PORT &= ~E;  //E = 0 
    DATA_CONTROL_PORT &= 0x0F;
    DATA_CONTROL_PORT |= ((command << 4) & 0xF0); 
    DATA_CONTROL_PORT |= E;   //E = 1 
    DATA_CONTROL_PORT &= ~E;  //E = 0
}

void lcd_init(void)
{
    delay_ms(2);
    DATA_CONTROL_DDR |= 0xF7; 
    send_command(0x02); //return cursor
    send_command(0x28); //cofiguration 4 wires 
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
    DATA_CONTROL_PORT |= RS;  //RS = 1
    DATA_CONTROL_PORT &= ~RW; //RW = 0
    DATA_CONTROL_PORT &= ~E;  //E = 0  
    DATA_CONTROL_PORT &= 0x0F; 
    DATA_CONTROL_PORT |= (ch & 0xF0);
    DATA_CONTROL_PORT |= E;   //E = 1  
    DATA_CONTROL_PORT &= ~E;  //E = 0       
    
    delay_ms(2);
    DATA_CONTROL_PORT |= RS;  //RS = 1
    DATA_CONTROL_PORT &= ~RW; //RW = 0
    DATA_CONTROL_PORT &= ~E;  //E = 0  
    DATA_CONTROL_PORT &= 0x0F;
    DATA_CONTROL_PORT |= ((ch << 4) & 0xF0);   
    DATA_CONTROL_PORT |= E;   //E = 1
    DATA_CONTROL_PORT &= ~E;  //E = 0 
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