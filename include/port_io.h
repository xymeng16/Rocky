#ifndef INCLUDE_PORT_IO_H_
#define INCLUDE_PORT_IO_H_

#include "types.h"

// write 1 byte to the given port
void port_byte_out(uint16_t port, uint8_t value);

// read 1 byte from the given port
uint8_t port_byte_in(uint16_t port);

// read 1 word from the given port
uint16_t port_word_in(uint16_t port);

#endif // !INCLUDE_PORT_IO_H_