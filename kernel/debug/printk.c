/*
    Some code are copied from linux kernel v2.0.40
*/
#include "screen.h"
#include "string.h"
#include "vargs.h"
#include "debug.h"

// the printk function is based on vsprintf function
static int vsprintf(char *buf, const char *format, va_list args);

void printk(const char *format, ...)
{
    static char buf[1024]; // set to static to avoid frequently creating local var
    va_list args;
    int i;

    va_start(args, format);
    i = vsprintf(buf, format, args);
    va_end(args);

    buf[i] = '\0';

    cputs(buf);
}

void printk_c(real_color_t bgc, real_color_t fgc, const char *format, ...)
{
    static char buf[1024]; // set to static to avoid frequently creating local var
    va_list args;
    int i;

    va_start(args, format);
    i = vsprintf(buf, format, args);
    va_end(args);

    buf[i] = '\0';

    cputs_c(buf, bgc, fgc);
}

#define is_digit(c)	((c) >= '0' && (c) <= '9')

static int skip_atoi(const char **s)
{
    int i = 0;

    while (is_digit(**s))
    {
        i = i * 10 + *((*s)++) - '0';
    }
    
    return i;
}

#define ZEROPAD		1	// pad with zero
#define SIGN	 	2   	// unsigned/signed long
#define PLUS    	4	// show plus
#define SPACE	  	8   	// space if plus
#define LEFT	 	16  	// left justified
#define SPECIAL		32  	// 0x
#define SMALL	  	64  	// use 'abcdef' instead of 'ABCDEF'

/*
__asm__("divl %2\n"
       : "=d" (remainder), "=a" (quotient)
       : "g" (modulus), "d" (high), "a" (low));
*/
#define do_div(n,base) ({ \
		int __res; \
		__asm__("divl %4":"=a" (n),"=d" (__res):"0" (n),"1" (0),"r" (base)); \
		__res; })