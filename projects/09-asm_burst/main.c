/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-09-27
 * Last update: 2019-07-16
 * Platform:    ATmega328P, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description: Blink a LED with delay function.
 * TODO: Verify functionality of LED blinker.
 * NOTE: Macro _BV converts a bit number into a byte value (see AVR Libc
 * Reference Manual).
 */

/* Includes ----------------------------------------------------------*/
#include <stdlib.h>         // itoa() function
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "uart.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define LED_PIN_0     PB0
#define burst_5     PB5
#define BLINK_DELAY   250

/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
  * Brief:  Main program. Blink a LED with delay function.
  * Input:  None
  * Return: None
  */
extern void burst_asm(uint8_t number);
int main(void)
{
    GPIO_config_output(&DDRB, burst_5);
    GPIO_write(&PORTB, burst_5, 1);
    


    /* Infinite loop */
      for (;;)
      {
         
      }
    return (0);
}
