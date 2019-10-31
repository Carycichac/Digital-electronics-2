/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-10-11
 * Last update: 2019-10-16
 * Platform:    ATmega328P, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description: Decimal counter with data display on 7-segment display.
 * TODO: Create and test functions to operate a 7-segment display using
 *       shift registers.
 * NOTE: Store segment.c and segment.h files in library/src and 
 *       library/inc folders.
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include "gpio.h"
#include "timer.h"
#include "segment.h"
#include <avr/interrupt.h>

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define LED_D1          PB5
#define BTN_S1          PC1 // PCINT 9
#define BTN_S2          PC2 // PCINT 10
#define BTN_S3          PC3 // PCINT 11

/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Shows decimal values ​​on 7-segment display.
 *  Input:  None
 *  Return: None
 */
int main(void)
{
    /* D1 led */
    // TODO: Configure D1 led at Multi-Function Shield
    DDRB |=_BV(LED_D1);
    PORTB &=~_BV(LED_D1);

    /* Pin Change Interrupts 11:9 */
    // TODO: Configure Pin Change Interrupts 11, 10, and 9
    PCICR |=  _BV(PCIE1);
    PCMSK1 |=_BV(BTN_S1);
    PCMSK1 |=_BV(BTN_S2);
    PCMSK1 |=_BV(BTN_S3);

    /* 7-segment display interface */
    // TODO: Configure 7-segment display pins
    DDRB |= _BV(SEGMENT_DATA);
    DDRD |= _BV(SEGMENT_CLK);
    DDRD |= _BV(SEGMENT_LATCH);
    
    //TIMER_0
    TIM_config_prescaler(TIM0, TIM_PRESC_256);
    TIM_config_interrupt(TIM0, TIM_OVERFLOW_ENABLE);

    /* Enable interrupts by setting the global interrupt mask */
    sei();

    /* Infinite loop */
    for (;;) {
        // TODO: Use function to display digit 1 at position 0
        SEG_putc(1, 0);
    }

    return (0);
}

/**
 *  Brief: Pin Change Interrupt 11:9 routine. Toggle a LED.
 */
ISR(PCINT1_vect)
{
    // TODO: Toggle a led
     PORTB ^= _BV(LED_D1);
}

ISR(TIMER0_OVF_vect)
{
    static uint8_t segment = 0;
    segment++;
    segment %= 4;

    static uint8_t j = 0; //jednotky
    static uint8_t d = 0; //desitky
    static uint8_t s = 0; //stovky
    static uint8_t t = 0; //tisice
    
    switch(segment)
    {
        case 0:
            SEG_putc(j, segment);
            break;
        case 1:
            SEG_putc(d, segment);
            break;
        case 2:
            SEG_putc(s, segment);
            break;
        case 3:
            SEG_putc(t, segment);
            break;
        default:
            SEG_putc(0, segment);
    }

    j++;

    if (j == 9) {
        j = 0;
        d++;
    }
    if (d == 9 && j == 9) {
        j = 0;
        d = 0;
        s++;
    }
    if (s == 9 && d == 9 && j == 9) {
        j = 0;
        d = 0;
        s = 0;
        t++;
    }
}