/*---------------------------
Functions for port I/O in C.
GCC inline assembly
Ref: http://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html
---------------------------*/
#include "port_io.h"

// write 1 byte to the given port
inline void port_byte_out(uint16_t port, uint8_t value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

// read 1 byte from the given port
inline uint8_t port_byte_in(uint16_t port)
{
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret; 
}

// read 1 word from the given port
inline uint16_t port_word_in(uint16_t port)
{
    uint16_t ret;
    asm volatile("inw %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}
