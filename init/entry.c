#include "types.h"
#include "screen.h"

int kern_entry()
{
    // uint8_t *input = (uint8_t *)0xB8000; // Video buffer addr
    // uint8_t color = (0 << 4) | (15 & 0x0F);
    // cls();
    // // *input++ = 'T'; *input++ = color;
    // // *input++ = 'e'; *input++ = color;
    // // *input++ = 'l'; *input++ = color;
    // // *input++ = 'l'; *input++ = color;
    // // *input++ = 'o'; *input++ = color;
    // // *input++ = ','; *input++ = color;
    // // *input++ = ' '; *input++ = color;
    // // *input++ = 'O'; *input++ = color;
    // // *input++ = 'S'; *input++ = color;
    // // *input++ = ' '; *input++ = color;
    // // *input++ = 'K'; *input++ = color;
    // // *input++ = 'e'; *input++ = color;
    // // *input++ = 'r'; *input++ = color;
    // // *input++ = 'n'; *input++ = color;
    // // *input++ = 'e'; *input++ = color;
    // // *input++ = 'l'; *input++ = color;
    // // *input++ = '!'; *input++ = color;
    // cputc_c('A', rc_black, rc_white);
    cls();
    cputs("Hello, test world.\n");
    cputhex_c(0x1b2b3b4b, rc_black, rc_green);
    cputc_c(' ', rc_black, rc_white);
    cputdec_c(12345678, rc_black, rc_green);

    return 0;
}