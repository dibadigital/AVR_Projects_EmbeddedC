#ifndef _lock_H
#define _lock_H

#include <mega16a.h> 
#include <delay.h>
#include <stdio.h>
#include <stdint.h>

#include <alcd.h>

#define R1 PORTA.0
#define R2 PORTA.1
#define R3 PORTA.2
#define R4 PORTA.3

#define C1 PINA.4
#define C2 PINA.5
#define C3 PINA.6
#define C4 PINA.7

#define MAX_OF_Elements_PassWord  5
#define MAX_OF_Elements_BUZZER   10

#define MSG_ENTER_PASS     0
#define MSG_OK_PASS        1
#define MSG_WRONG_PASS     2
#define MSG_PREVIOUS_PASS  3
#define MSG_NEW_PASS       4
#define MSG_CHANGE_OK      5

typedef enum{
    MENU_ENTER_PASS,
    MENU_OK_PASS,
    MENU_WRONG_PASS,
    MENU_PREVIOUS_PASS, 
    MENU_NEW_PASS,
    MENU_CHANGE_OK,
    MENU_INPUT
}menu_type;

extern menu_type lock_state;

extern char messages[7][17];
extern unsigned char passIndex;
extern unsigned char password_entered[MAX_OF_Elements_PassWord];
extern eeprom unsigned char password_registered[MAX_OF_Elements_PassWord];

extern unsigned char flag_keypad;
extern const unsigned char KeypadMatrix[4][4];
extern unsigned char C_previous[4];
extern unsigned char key, key_previous;
extern unsigned char debouncer, keyReady; 
extern unsigned char flag_mode_enter, flag_msg_write;
extern unsigned char cnt_wait, cnt_msg;

extern unsigned char t_buzzer_total[MAX_OF_Elements_BUZZER];
extern unsigned char t_buzzer_duration[MAX_OF_Elements_BUZZER];
extern unsigned char flag_buzzer;
extern unsigned char cnt_buzzer, buzzer_index, num_of_buzzer_element;
extern unsigned char relay_state;

void KeypadInit(void);
void BuzzerInit(void);
void RelayInit(void);

void lock_process(void);
unsigned char GetEdge(void);
unsigned char KeypadRead(void);
unsigned char KeypadFunc(void);
void key_process(void);

unsigned char password_write(void);
void password_write_reg(void);
unsigned char password_verification(void);
unsigned char password_clear(void);
void password_clear_all(unsigned char flag_enter_reg);
void message_write(unsigned char msgIndex_input);
void star(void);
void space(void);

void NumBuzzer_write(unsigned char num);
void sound1(void);
void sound2(void);
void sound3(void);
void sound4(void);
void sound5(void);
void buzzer_start(void);
void buzzer_stop(void);
void Buzzer_Relay_write(unsigned char pin_num, unsigned char pin_state);
void buzzer_process(void);
void relay_process(void);

#endif 