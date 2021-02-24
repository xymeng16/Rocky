#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "types.h"

typedef enum real_color
{
    rc_black = 0,
    rc_blue = 1,
    rc_green = 2,
    rc_cyan = 3,
    rc_red = 4,
    rc_magenta = 5,
    rc_brown = 6,
    rc_light_grey = 7,
    rc_dark_grey = 8,
    rc_light_blue = 9,
    rc_light_green = 10,
    rc_light_cyan = 11,
    rc_light_red = 12,
    rc_light_magenta = 13,
    rc_light_brown  = 14,   // yellow
    rc_white = 15
} real_color_t;

// clean the screen
void cls();

// output a char with color to the console
void cputc_c(char c, real_color_t bgc, real_color_t fgc);

// output a string terminated by '\0' to the console, black bgc and white fgc in default
void cputs(char *s);

// output a string terminated by '\0' with color to the console
void cputs_c(char *s, real_color_t bgc, real_color_t fgc);

// output a hexadecimal int value to the console, with color
void cputhex_c(uint32_t n, real_color_t bgc, real_color_t fgc);

// output a decimal int value to the console, with color
void cputdec_c(uint32_t n, real_color_t bgc, real_color_t fgc);

#endif // !INCLUDE_SCREEN_H_