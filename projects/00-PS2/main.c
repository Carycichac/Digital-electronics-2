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
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "lcd.h"
#include "uart.h"
//#include "PS2.h"
#include "twi.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define DATA          PB5
#define CLOCK         PB4
#define UART_BAUD_RATE 9600

/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/
/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Coder/decoder for serial communication protocol PS/2
 *  Input:  None
 *  Return: None
 */
int main(void)
{
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    twi_init();

    sei();

    TIM_config_prescaler(TIM1, TIM_PRESC_8);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

    for (;;) {
    }

    return (0);
}

ISR(TIMER1_OVF_vect)
{
    
    uint8_t symbol = 0;

    twi_start(0x00);
    symbol = twi_read_ack();
    twi_stop();
    //PS2_SYM(symbol);
    if (symbol == 0x3a) {
        uart_putc('m');
    }
}
