/*
 * ---------------------------------------------------------------------
 * Author:      Martin Vasicka, Matus Sobona, Vojtech Zboril
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2019-11-27
 * Last update: 2019-11-27
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description:
 */

/**
 * References:
 * https://techdocs.altium.com/display/FPGA/PS2+Keyboard+Scan+Codes
 * https://en.wikipedia.org/wiki/PS%2F2_port
 * https://ktln2.org/2016/08/04/ps2-protocol/
 * https://allpinouts.org/pinouts/connectors/input_device/mouse-keyboard-ps-2/
 */


/* Includes ----------------------------------------------------------*/
#include <stdlib.h>             // itoa() function
#include <stdio.h> 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include "timer.h"
#include "lcd.h"
#include "uart.h"
//#include "PS2.h"
#include "twi.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define DATA          PD2
#define CLOCK         PD4
#define UART_BAUD_RATE 9600

/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/
/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Coder/decoder for serial communication protocol PS/2
 *  Input:  None
 *  Return: None
 */

int i = 11;
uint8_t tmp[11];

int main(void)
{
    DDRD &= ~_BV(DATA);                   
    PORTD |= _BV(DATA);
    PORTD |= _BV(CLOCK);
  
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    EICRA = 1<<ISC01;
    EIMSK |= _BV(INT0);

    sei();

    for (;;) {
    }

    return (0);
}

ISR(INT0_vect)
{
    if((i < 9) && (i > 2)) {  
        //tmp[i] = DATA;   
        if (DATA == 1)
            uart_puts("1");
        else if (DATA==0)
            uart_puts("0");
        else
            uart_puts("2");
   }  
    i--;
    if (i <= 2) i = 11;
}
