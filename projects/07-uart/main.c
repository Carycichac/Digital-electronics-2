/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-10-23
 * Last update: 2019-11-01
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description:
 *    Analog-to-digital conversion with displaying result on LCD and 
 *    transmitting via UART.
 * 
 * Note:
 *    Peter Fleury's UART library.
 */

/* Includes ----------------------------------------------------------*/
#include <stdlib.h>             // itoa() function
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "lcd.h"
#include "uart.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define UART_BAUD_RATE 9600

/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Read ADC result and transmit via UART.
 *  Input:  None
 *  Return: None
 */
int main(void)
{
    // LCD display
    lcd_init(LCD_DISP_ON);

    // UART: asynchronous, 8-bit data, no parity, 1-bit stop
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Display string without auto linefeed
    lcd_puts("LCD testing");
    // Put string to ringbuffer for transmitting via UART.
    uart_puts("UART testing\r\n");
    lcd_clrscr ();
    /* ADC
     * TODO: Configure ADC reference, clock source, enable ADC module, 
     *       and enable conversion complete interrupt */
    ADMUX |= _BV(REFS0);
    ADCSRA |= _BV(ADEN);
    ADCSRA |= _BV(ADIE);
    ADCSRA |= _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2);



    /* Timer1
     * TODO: Configure Timer1 clock source and enable overflow 
     *       interrupt */
    TIM_config_prescaler(TIM1, TIM_PRESC_64);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

    // Infinite loop
    for (;;) {
    }

    // Will never reach this
    return (0);
}

/**
 *  Brief: Timer1 overflow interrupt routine. Start ADC conversion.
 */
ISR(TIMER1_OVF_vect)
{
    // TODO: Start ADC conversion
    ADCSRA |= _BV(ADSC);


}

/**
 *  Brief: ADC complete interrupt routine. Update LCD and UART 
 *         transmiter.
 */
ISR(ADC_vect)
{
    uint16_t value = 0;
    char uart_string[4];

	// Read 10-bit ACD value
    value = ADC;

    // TODO: Update LCD and UART transmiter
    itoa(value, uart_string, 10);
    lcd_puts(uart_string);
    lcd_putc(' ');
    if (value < 1){
        uart_puts("\033[0;94m");     
        uart_puts("RIGHT ");
    }
    else if (value > 1 && value < 101){
        uart_puts("\033[0;95m");
        uart_puts("UP ");
    }
    else if (value > 101 && value < 260){
        uart_puts("\033[0;96m");     
        uart_puts("DOWN ");
    }
    else if (value > 260 && value < 500){
        uart_puts("\033[0;31m");
        uart_puts("LEFT ");
    }
    else if (value > 500 && value < 700){
        uart_puts("\033[0;93m");  
        uart_puts("SELECT ");
    }
    else{
        uart_puts("");
    }
    //uart_puts(uart_string);
    //uart_putc(' ');
}