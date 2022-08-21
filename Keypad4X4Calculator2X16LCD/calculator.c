#include "calculator.h"

const unsigned char KeypadMatrix[4][4] = {{7,8,9,10},{4,5,6,11},{1,2,3,12},{14,0,15,13}};
unsigned char C_previous[4] = {0};
unsigned char key = 0, key_previous = 0;
unsigned char debouncer = 0, keyReady = 0;

uint32_t number = 0, result = 0, val2 = 0, lcd_var = 0;
unsigned char op = 0;
unsigned char flag_val2 = 0, flag_equal = 0;

void KeypadInit(void)
{
    DDRA = 0x0F;
    PORTA = 0xFF;
}

unsigned char GetEdge(void)
{
    unsigned char flag_edge = 0;
    
    R1 = 0; R2 = 0; R3 = 0; R4 = 0;
    delay_ms(1);  //Because half of the port is input and half of the port is output. 
    if((C1 == 0 && C_previous[0]==1) ||
       (C2 == 0 && C_previous[1]==1) ||
       (C3 == 0 && C_previous[2]==1) ||
       (C4 == 0 && C_previous[3]==1))  
     {
       flag_edge = 1;
     }
   
    C_previous[0] = C1;
    C_previous[1] = C2;  
    C_previous[2] = C3;  
    C_previous[3] = C4;
    
    return flag_edge;
}

unsigned char KeypadRead(void)
{
    unsigned char x = 16;
    
    R1 = 0; R2 = 1; R3 = 1; R4 = 1;
    delay_ms(1);  //Because half of the port is input and half of the port is output.
    if (C1 == 0){x = KeypadMatrix[0][0];}
    if (C2 == 0){x = KeypadMatrix[0][1];}
    if (C3 == 0){x = KeypadMatrix[0][2];}
    if (C4 == 0){x = KeypadMatrix[0][3];}
    
    R1 = 1; R2 = 0; R3 = 1; R4 = 1;
    delay_ms(1);  //Because half of the port is input and half of the port is output.
    if (C1 == 0){x = KeypadMatrix[1][0];}
    if (C2 == 0){x = KeypadMatrix[1][1];}
    if (C3 == 0){x = KeypadMatrix[1][2];}
    if (C4 == 0){x = KeypadMatrix[1][3];}
    
    R1 = 1; R2 = 1; R3 = 0; R4 = 1;
    delay_ms(1);  //Because half of the port is input and half of the port is output.
    if (C1 == 0){x = KeypadMatrix[2][0];}
    if (C2 == 0){x = KeypadMatrix[2][1];}
    if (C3 == 0){x = KeypadMatrix[2][2];}
    if (C4 == 0){x = KeypadMatrix[2][3];}
    
    R1 = 1; R2 = 1; R3 = 1; R4 = 0;
    delay_ms(1);  //Because half of the port is input and half of the port is output.
    if (C1 == 0){x = KeypadMatrix[3][0];}
    if (C2 == 0){x = KeypadMatrix[3][1];}
    if (C3 == 0){x = KeypadMatrix[3][2];}
    if (C4 == 0){x = KeypadMatrix[3][3];}

    return x; 
}

unsigned char KeypadFunc(void)
{  
    unsigned char flag_out = 0;
    
    key = KeypadRead();
    if(key != key_previous) //To avoid bouncing the key
    {   
        key_previous = key;
        debouncer = 0;
        keyReady = 0;   
    } 
    else
    {  
        if(key != 16)
        {    
            debouncer++;
            if(debouncer == 10) //10*5ms = 50ms
            {
                debouncer = 0;
                keyReady = 1; 
                flag_out = 1;
            } 
        }
        else
        {
            key_previous = key;
            debouncer = 0;
            keyReady = 0;
        }
    }
    
    if(keyReady == 1)
    {
        keyReady = 0;
        calculator_process();
        lcd_process();  
    } 
    
    return flag_out;
}

void calculator_process(void)
{
    if (key < 10) //numbers buttons: 0 1 2 3 4 5 6 7 8 9    
    {
        digit_process();
    }
    else if ((10 <= key) && (key <= 13)) //operators buttons: + - * / 
    {
        flag_equal = 0;  
        operator_process();
    }
    else if (key == 14) //clear button 
    {
        clear_process();
    }
    else if (key == 15) //equal button 
    {          
        flag_equal = 1;
        equal_process();  
    }
}
void digit_process(void)
{
    if(flag_equal == 1)
        clear_process();
    
    number = (number * 10) + key;    
    if (op == 0) //before entering the operator
    {
        result = number; 
        val2 = number;   
    }
    else //after entering the operator
    {
        val2 = number; 
        flag_val2 = 1;    
    }
    lcd_var = number;
}
void operator_process (void)
{
    if(flag_val2 == 1) 
    {           
        flag_val2 = 0;
        equal_process();
        val2 = result;
    } 
    
    number = 0;      
    
    switch (key) //operators buttons: + - * /
    {
        case 13:  //Sum : +
            op = 1;
        break;
            
        case 12:  //Subtraction : -
            op = 2;
        break;
            
        case 11:  //Multiplication : *
            op = 3;
        break;
            
        case 10:  //Division : /
            op = 4;
        break;         
    }
}

void clear_process (void)
{
    flag_equal = 0;
    flag_val2 = 0;
    number = 0;  
    result = 0;
    op = 0;
    val2 = 0;
    lcd_var = 0;
}

void equal_process (void)
{
    flag_val2 = 0;
    
    switch (op) //operators buttons: + - * /
    {   
        case 1:  //Sum : +
            result = result + val2;
        break;
            
        case 2:  //Subtraction : - 
            if((int32_t)result - (int32_t)val2 >= 0)
                result = result - val2;
        break;
            
        case 3:  //Multiplication : *
            result = result * val2;
        break;
            
        case 4: //Division : / 
            if(val2 != 0)
                result = result / val2;
            else
                lcd_error();
        break;         
    }     
    lcd_var = result; 
}

void lcd_process(void)
{
    char lcd_array[20] = {0};
    lcd_gotoxy(0, 1);
    sprintf(lcd_array,"%16lu", lcd_var);
    lcd_puts(lcd_array);
}

void lcd_error(void)
{
    lcd_clear();
    lcd_gotoxy(5, 0);
    lcd_puts("Error 0");
    flag_equal = 0;
    clear_process();
    delay_ms(1000);
    lcd_clear();
}