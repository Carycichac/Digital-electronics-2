#ifndef PS2_H_INCLUDED
#define PS2_H_INCLUDED

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>

/* Define ------------------------------------------------------------*/
#define PS2_DATA    PB5
#define PS2_CLK     PB4

void PS2_SYM(uint8_t symbol);

#endif