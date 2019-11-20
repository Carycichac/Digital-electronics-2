;* ---------------------------------------------------------------------
;*
;* Assembly implementation of 4- and 8--bit LFSR-based (Linear Feedback
;* Shift Register) pseudo-random generators.
;* ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
;*
;* Copyright (c) 2017-2019 Tomas Fryza
;* Dept. of Radio Electronics, Brno University of Technology, Czechia
;* This work is licensed under the terms of the MIT license.
;*
;* https://www.xilinx.com/support/documentation/application_notes/xapp052.pdf
;* http://courses.cse.tamu.edu/walker/csce680/lfsr_table.pdf
;*
;* ---------------------------------------------------------------------

;* Includes ------------------------------------------------------------
; Set offset for control register addresses (NEEDED FOR I/O REGISTERS)
#define __SFR_OFFSET    0
#include <avr/io.h>

;* Define --------------------------------------------------------------
#define result  r16
#define temp    r17
#define input   r24

;* Functions -----------------------------------------------------------
;* LFSR-based 4-bit pseudo-random generator.
;* Input:  r24 - Current value of shift register
;* Return: r24 - New value of shift register
.global rand4_asm
rand4_asm:
    push result             ; Save "Result" on Stack
    push temp               ; Save "Temp" on Stack

    bst input, 3            ; Copy "Input" bit 3 to T Flag...
    bld result, 0           ; ...and then to "Result" bit 0
    bst input, 2            ; Copy "Input" bit 2 to T Flag
    bld temp, 0             ; ...and then to "Temp" bit 0
    eor result, temp        ; Xor "Input" bits 3 and 2

    lsl input               ; Shift all "Input" bits to left
    com result              ; Invert "Result"
    bst result, 0           ; Copy "Result" bit 0 to T Flag...
    bld input, 0            ; ...and then to "Input" bit 0
    andi input, 0x0f        ; Make sure 4 upper birs are cleared

    pop temp                ; Restore "Temp" from Stack
    pop result              ; Restore "Result" from Stack
    ret                     ; Return from subroutine


.global burst_asm
burst_asm:
    sbi $18, 0 ;
    cbi $18, 0 ;
    