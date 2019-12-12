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
#include <math.h>
#include "timer.h"
#include "lcd.h"
#include "uart.h"
//#include "PS2.h"
#include "twi.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define DATA          PC4
#define CLOCK         PC5
#define UART_BAUD_RATE 9600

/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/
/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Coder/decoder for serial communication protocol PS/2
 *  Input:  None
 *  Return: None
 */
int i = 0;
uint8_t clk_act = 2;


int main(void)
{
    DDRC |= _BV(DATA);
    DDRC |= _BV(CLOCK);                       
    PORTC &= ~_BV(DATA);
    PORTC &= ~_BV(CLOCK);
  
    //uint8_t clk_act = CLOCK;       


    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    twi_init();

    TIM_config_prescaler(TIM0, TIM_PRESC_1);
    TIM_config_interrupt(TIM0, TIM_OVERFLOW_ENABLE);

       sei();

    for (;;) {
    }

    return (0);
}

ISR(TIMER0_OVF_vect)
{
    uint8_t clk_bef = clk_act;
    uint8_t tmp[11];
    uint8_t sym = 0;
    char txt[4];

    if (i > 11) i = 0;

    clk_act = CLOCK;

    if (clk_bef == 1 && clk_act == 0 && i < 11) 
    {
        tmp[i] = DATA;
        i++;
    }

    if (i == 11)
    {
        i = 0;
        for (int j = 7; j >= 0; j--)
        {
            sym += tmp[j] * pow(2, j);
        }
        itoa(sym, txt, 16);
        uart_puts(txt);
    }

    /*
    uint8_t symbol = 0;

    twi_start(0x00);
    symbol = twi_read_ack();
    twi_stop();
    //PS2_SYM(symbol);
    if (symbol == 0x3a) {
        uart_putc('m');
    }*/

}
