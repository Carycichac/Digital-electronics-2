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
#include <avr/io.h>
#include <util/delay.h>
#include <gpio.h>

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define LED_PIN_0     PB0
#define LED_PIN_5     PB5
#define BLINK_DELAY   250

/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
  * Brief:  Main program. Blink a LED with delay function.
  * Input:  None
  * Return: None
  */
int main(void)
{
    GPIO_config_output(&DDRB, LED_PIN_0);
    GPIO_config_output(&DDRB, LED_PIN_5);
    GPIO_write(&PORTB, LED_PIN_0, 1);
    GPIO_write(&PORTB, LED_PIN_5, 1);
    

    /* Infinite loop */
      for (;;)
      {
        if (bit_is_clear(PIND, 2)) {
          /* Invert LED and delay */
          GPIO_toggle(&PORTB, LED_PIN_0);
          GPIO_toggle(&PORTB, LED_PIN_5);
          _delay_ms(BLINK_DELAY);     /* Wait for several milisecs */
        }
      }
    return (0);
}
