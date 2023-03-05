
#include <mega16a.h>
#include <delay.h>
#include <stdio.h>
#include <stdint.h>

// Alphanumeric LCD functions
#include <alcd.h>

#define CH_NUM 2

#define ADC_VREF 5.0
#define ADC_RESULOTION 1024 //2^10 = 1024

#define AVG_NUM 5

enum channel_adc
{
    adc0,
    adc1 
}ch_adc;

char lcd_str[20] = {0};

uint8_t flag_adc = 0;

uint16_t adc_val = 0;
uint16_t adc[CH_NUM][AVG_NUM] = {0};
uint8_t idx_adc0 = 0, idx_adc1 = 0;
uint16_t average_adc[CH_NUM] = {0};
      
float input_voltage[CH_NUM] = {0}; 
float temprature = 0, voltage_pot = 0;

void adc_init(uint8_t channel);

void adc_channel_select(uint8_t channel);

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
            
                switch(ch_adc)
                {
                    case adc0: 
                        adc[ch_adc][idx_adc0] = adc_val;   
                        idx_adc0++;
                        if(idx_adc0 == AVG_NUM) 
                        {
                            average_adc[ch_adc] = Calculate_AVG(adc[ch_adc], AVG_NUM); 
                                                    
                            input_voltage[ch_adc] = (ADC_VREF/ADC_RESULOTION)*average_adc[ch_adc]; //V  
                
                            // LM35: each centigrade = 10 mV = 0.01 V
                            temprature = input_voltage[ch_adc] * 100;   // temprature = input_voltage / 0.01 V     
                        
                            sprintf(lcd_str, "temp = %4.2f", temprature);
                            lcd_gotoxy(0, 0);
                            lcd_puts(lcd_str); 
                            
                            idx_adc0 = AVG_NUM - 1;
                            DELETE_ONE_OLD_VALUE(adc[ch_adc], AVG_NUM); 
                        }
                    break;  
                    
                    case adc1:  
                        adc[ch_adc][idx_adc1] = adc_val;   
                        idx_adc1++;
                        if(idx_adc1 == AVG_NUM) 
                        {
                            average_adc[ch_adc] = Calculate_AVG(adc[ch_adc], AVG_NUM); 
                                                    
                            input_voltage[ch_adc] = (ADC_VREF/ADC_RESULOTION)*average_adc[ch_adc]; //V  
                                
                            voltage_pot = input_voltage[ch_adc];
                        
                            sprintf(lcd_str, "V = %4.2f", voltage_pot);
                            lcd_gotoxy(0, 1);
                            lcd_puts(lcd_str);  
                            
                            idx_adc1 = AVG_NUM - 1;
                            DELETE_ONE_OLD_VALUE(adc[ch_adc], AVG_NUM);
                        }  
                    break;
                }      
                 
        }
          
        delay_ms(1);
        cnt++;
        if(cnt == 500)
        {      
            cnt = 0;       
            switch(ch_adc)
            {
                case adc0:
                    ch_adc = adc1; 
                break;     
                
                case adc1:
                    ch_adc = adc0; 
                break;
            }   
            adc_channel_select(ch_adc);                                   
            ADCSRA |= (1 << 4);  //clear flag interrupt ADC
            ADCSRA |= (1 << 6);  // start conversion ADC
        } 
    }
}

void adc_init(uint8_t channel)
{
    ADMUX = (ADMUX & 0xE0) | channel;  // adc channel
    ADMUX |= ((0 << 7) | (1 << 6));    // Vref is AVCC  
    
    ADCSRA |= 0x06; // adc prescaler is 64: f_clk_ADC = 8 Mhz/64 = 125 Khz < 200 Khz
    ADCSRA |= (1 << 3); // adc interrupt is enabled
    ADCSRA |= (1 << 7); // adc is enabled
}

void adc_channel_select(uint8_t channel)
{
    ADMUX = (ADMUX & 0xE0) | channel;
    delay_us(50);       
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
