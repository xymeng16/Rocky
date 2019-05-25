/*---------------------------
Some screen operating functions in C.
When working in text-mode, the video memory is mapped 
to "CGA/EGA+ Chroma text video buffer"(0xB8000H-0xBFFFFH).
Char encoding ref: http://wiki.0xffffff.org/posts/hurlex-4.html
---------------------------*/
#include "screen.h"
#include "port_io.h"

// port 0x3D4 is the index of the VGA register
#define REG_VGA_INDEX 0x3D4
// port 0x3D5 is the value of the register to be set
#define REG_VGA_DATA 0x3D5

// the attribute byte of the screen
#define ATTR_BYTE 0x0F
// the blank char of the screen
#define BLANK 0xF20

// the coordinate of the cursor
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

// the VGA memory address
static const uint16_t video_mem_addr = (uint16_t *)0xB8000;

// move the cursor to the given location
static void move_cursor()
{
    // screen width is 80
    uint16_t cursor_loc = cursor_y * 80 + cursor_x;


    port_byte_out(REG_VGA_INDEX, 14); // the higher part of the cursor location
    port_byte_out(REG_VGA_DATA, cursor_loc >> 8); // the higher 8-bit
    port_byte_out(REG_VGA_INDEX, 15); // the lower part of the cursor location
    port_byte_out(REG_VGA_DATA, cursor_loc);
}

// clean the screen
void cls()
{
    int i = 0;
    for (i = 0; i < 80 * 25; i++)
    {
        video_mem_addr[i] = BLANK;
    }
    cursor_x = 0; cursor_y = 0;
    move_cursor();
}