#include "gpio.h"
#include "PS2.h"

void PS2_SYM(uint8_t symbol)
{
    if (symbol == 0x3a) {
        uart_puts('m');
    }
}