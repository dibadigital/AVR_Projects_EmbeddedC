#ifndef _DancingLight_H
#define _DancingLight_H

#include <mega16a.h>
#include <delay.h>

#define OUTPUT    0xFF
#define INPUT     0x00

#define SET_ALL   0xFF
#define RESET_ALL 0x00

#define GPIO_WRITE_PIN(port, val) port = val

typedef struct{
    unsigned char PA_DIR;
    unsigned char PB_DIR;
    unsigned char PC_DIR;
    unsigned char PD_DIR;
    
    unsigned char PA_PORT;
    unsigned char PB_PORT;
    unsigned char PC_PORT;
    unsigned char PD_PORT;
}port;

void GPIO_INIT(port *p);

#endif
