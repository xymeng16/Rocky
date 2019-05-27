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

// the attribute byte of the screen ((0 << 4) | (15 & 0x0F)):((back_color << 4) | (fore_color & 0x0F))
#define ATTR_BYTE 0x0F
// the blank char of the screen ((ATTR_BYTE << 8) | 0x20)
#define BLANK 0xF20

// the coordinate of the cursor
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

// the VGA memory address
static uint16_t *video_mem_addr = (uint16_t *)0xB8000;

// move the cursor to the cursor_loc
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

// move the data of the last 24 lines 1 line forward and clear the last line 
static void scroll()
{
    // scroll when y reaches 25
    if (cursor_y >= 25)
    {
        int i;
        for (i = 0; i < 24 * 80; i++)
        {
            video_mem_addr[i] = video_mem_addr[i+80];
        }

        for(i = 24 * 80; i < 25 * 80; i++)
        {
            video_mem_addr[i] = BLANK;
        }

        // set current y
        cursor_y = 24;
    }
}


// output a char with color to the console
void cputc_c(char c, real_color_t bgc, real_color_t fgc)
{
    // screen width is 80
    uint16_t cursor_loc = cursor_y * 80 + cursor_x;
    uint8_t attr_byte = ((uint8_t)bgc << 4) | ((uint8_t)fgc & 0x0F);

    // handle the backspace(0x08), tab(0x09), '\r', '\n' and space
    switch (c)
    {
        case 0x08: // backspace
            cursor_x = (cursor_x-- == 0) ? 0 : cursor_x;
            break;
        
        case 0x09: // tab, to a position that is divisible by 8 (0xF8 = ~(8-1) = 11111 000)
            cursor_x = (cursor_x + 8) & 0xF8;
            break;

        case '\r': // '\t'
            cursor_x = 0;
            break;

        case '\n':
            cursor_x = 0;
            cursor_y++;
            break;

        default:
            if(c >= ' ')
            {
                video_mem_addr[cursor_x + cursor_y * 80] = c | attr_byte;
                cursor_x++;
            }
            break;
    }

    scroll();
    move_cursor();

}

// output a string terminated by '\0' to the console, black bgc and white fgc in default
void cputs(char *s)
{

}

// output a string terminated by '\0' with color to the console
void cputs_c(char *s, real_color_t bgc, real_color_t fgc)
{

}

// output a hexadecimal int value to the console, with color
void cputhex_c(uint32_t n, real_color_t bgc, real_color_t fgc)
{

}

// output a decimal int value to the console, with color
void cputdec_c(uint32_t n, real_color_t bgc, real_color_t fgc)
{

}