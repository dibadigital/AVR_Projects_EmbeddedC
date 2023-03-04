
#include <mega16a.h>
#include <delay.h>
#include <stdio.h>
#include <stdint.h>

// Alphanumeric LCD functions
#include <alcd.h>

#define ADC_VREF 2.56
#define ADC_RESULOTION 1024 //2^10 = 1024

#define AVG_NUM 5

char lcd_str[20] = {0};

uint8_t flag_adc = 0;

uint16_t adc_val = 0;
uint16_t adc[AVG_NUM] = {0};
uint8_t idx = 0;
uint16_t average_adc = 0;
      
float input_voltage = 0; 
float temprature = 0;

void adc_init(uint8_t channel);

uint16_t Calculate_AVG(uint16_t* arr, uint8_t num);
void DELETE_ONE_OLD_VALUE(uint16_t* arr, uint8_t num);

interrupt [ADC_INT] void isr_adc(void)
{
    uint8_t adc_L = 0, adc_H = 0; 
    unsigned char interrupt_status = 0;
            
    interrupt_status = SREG;
    #asm("cli")
    //adc_result = ADCW;
    adc_L = ADCL;
    adc_H = ADCH; 
    adc_val = (adc_H << 8) | adc_L; 
    SREG = interrupt_status;    //#asm("sei") 
    flag_adc = 1;
}

void main(void)
{   
    uint16_t cnt = 0;
     
    DDRC = 0xFF;  //LCD DIR
    PORTC = 0x00; //LCD PORT
     
    adc_init(0);  // adc channel is 0 (ADC0)
    
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
        
    #asm("sei")
     
    ADCSRA |= (1 << 6);  // start conversion ADC
            
    while (1)
    {      
        if(flag_adc == 1)
        {
            flag_adc = 0;      
            adc[idx] = adc_val;
            idx++;
            if(idx == AVG_NUM) 
            {
                average_adc = Calculate_AVG(adc, AVG_NUM); 
                                                    
                input_voltage = (ADC_VREF/ADC_RESULOTION)*average_adc; //V
                // LM35: each centigrade = 10 mV = 0.01 V
                temprature = input_voltage * 100;   // temprature = input_voltage / 0.01 V 
            
                sprintf(lcd_str, "temp = %4.2f", temprature);
                lcd_gotoxy(0, 0);
                lcd_puts(lcd_str);
                    
                idx = AVG_NUM - 1;
                DELETE_ONE_OLD_VALUE(adc, AVG_NUM); 
            }
        }
          
        delay_ms(1);
        cnt++;
        if(cnt == 500)
        {      
            cnt = 0;                                          
            ADCSRA |= (1 << 4);  //clear flag interrupt ADC
            ADCSRA |= (1 << 6);  // start conversion ADC
        } 
    }
}

void adc_init(uint8_t channel)
{
    ADMUX = (ADMUX & 0xE0) | channel;  // adc channel
    ADMUX |= ((1 << 7) | (1 << 6));    // Vref is 2.56V internal Vref  
    
    ADCSRA |= 0x06; // adc prescaler is 64: f_clk_ADC = 8 Mhz/64 = 125 Khz < 200 Khz
    ADCSRA |= (1 << 3); // adc interrupt is enabled
    ADCSRA |= (1 << 7); // adc is enabled
}

uint16_t Calculate_AVG(uint16_t* arr, uint8_t num)
{
    uint8_t i;
    uint32_t sum = 0;
    for(i = 0; i < num; i++)
    {
        sum += arr[i];
    }   
    return (uint16_t)(sum/num);
}

void DELETE_ONE_OLD_VALUE(uint16_t* arr, uint8_t num)
{
     uint8_t i;
     for(i = 1; i < num; i++)
    {
        arr[i-1] = arr[i];
    } 
}
