#include <mega16a.h>
#include <delay.h>
#include <stdio.h>
#include <stdint.h>

// Alphanumeric LCD functions
#include <alcd.h>

#define MIN_OCR 18000
#define MAX_OCR 19000

void TCNT1_Access_Write(unsigned int input_data);
void ICR1_Access_Write(unsigned int input_data);
void OCR1A_Access_Write(unsigned int input_data);
void OCR1B_Access_Write(unsigned int input_data);

void main(void)
{    
    uint16_t i = MAX_OCR;
    char lcd_str[20] = {0}; 
    
    DDRA = 0x00;
    PORTA = 0xFF; 
    
    DDRC = 0xFF;  //LCD DIR
    PORTC = 0x00; //LCD PORT
    
    DDRD = 0xFF;
    PORTD = 0x00;
    
    // Timer1, FastPWM Mode, TOP = ICR1
    // Freq_osc = 8 MHz, Prescaler = 8, Bottom = 0
    // OCR1A =~ 18000 to 19000 (Duty Cycle =~ 10% to 5%)  
    // OCR1B =~ 18000 to 19000 (Duty Cycle =~ 10% to 5%)
    // T_ovf  = 20 ms, Freq_ovf = 1 kHz
    // T_oc1A = 20 ms, Freq_oc1A = 50 Hz
    // T_oc1B = 20 ms, Freq_oc1B = 50 Hz
    TCCR1A = 0x02;                  // FastPWM Mode    
    TCCR1A |= (1 << 4) | (1 << 5);  // Set oc1B on compare match (Set output to high level) (inverting mode)  
    TCCR1A |= (1 << 6) | (1 << 7);  // Set oc1A on compare match (Set output to high level) (inverting mode)
    
    TCCR1B = 0x02;                  // Prescaler = 8 
    TCCR1B |= (1 << 3) | (1 << 4);  // FastPWM Mode
            
    TCNT1_Access_Write(0);        // TCNT1 = 0 : TCNT1H = 0x0, TCNT1L = 0x0   
    ICR1_Access_Write(19999);     // ICR1 = 19999 : ICR1H = 0x4E, ICR1L = 0x1F     // TOP = ICR1
    OCR1A_Access_Write(i);        // OCR1A = 19000 : OCR1AH = 0x4A, OCR1AL = 0x38  // compare match and generate oc1A
    OCR1B_Access_Write(i);        // OCR1B = 19000 : OCR1BH = 0x4A, OCR1BL = 0x38  // compare match and generate oc1B
         
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
    
    while(1)
    {  
        if (PINA.1 == 0)
        {          
            if (i < MAX_OCR)
            {
                i++; 
                OCR1A_Access_Write(i);
                OCR1B_Access_Write(i);
            }
        } 
        
        if (PINA.0 == 0)
        {          
            if (i > MIN_OCR)
            {
                i--;    
                OCR1A_Access_Write(i);
                OCR1B_Access_Write(i);
            }
        }   
        
        delay_ms(1);       
        sprintf(lcd_str, "OCR1 = %5u", i);
        lcd_gotoxy(0, 0);
        lcd_puts(lcd_str);
        
        sprintf(lcd_str, "Duty = %05.2f", 100.0*(19999-i+1)/(19999-0+1));
        lcd_gotoxy(0, 1);
        lcd_puts(lcd_str);  
    }
}

void TCNT1_Access_Write(unsigned int input_data)
{
    unsigned char interrupt_status = 0;
    interrupt_status = SREG;
    #asm("cli")
//    TCNT1 = input_data;  
    TCNT1H = (unsigned char)(input_data >> 8);
    TCNT1L = (unsigned char)input_data;
    SREG  = interrupt_status;        
}

void ICR1_Access_Write(unsigned int input_data)
{
unsigned char interrupt_status = 0;
    interrupt_status = SREG;
    #asm("cli")
//    ICR1 = input_data;
    ICR1H = (unsigned char)(input_data >> 8);
    ICR1L = (unsigned char)input_data;
    SREG  = interrupt_status;        
}

void OCR1A_Access_Write(unsigned int input_data)
{
    unsigned char interrupt_status = 0;
    interrupt_status = SREG;
    #asm("cli")
//    OCR1A = input_data;
    OCR1AH = (unsigned char)(input_data >> 8);
    OCR1AL = (unsigned char)input_data;
    SREG  = interrupt_status;        
}

void OCR1B_Access_Write(unsigned int input_data)
{
    unsigned char interrupt_status = 0;
    interrupt_status = SREG;
    #asm("cli")
//    OCR1B = input_data;
    OCR1BH = (unsigned char)(input_data >> 8);
    OCR1BL = (unsigned char)input_data;
    SREG  = interrupt_status;        
}

