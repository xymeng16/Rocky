#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "screen.h"
#include "vargs.h"

// print kernel message
void printk(const char *format, ...);

void printk_c(real_color_t back, real_color_t fore, const char *format, ...);
#endif