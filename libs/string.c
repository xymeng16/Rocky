#include "string.h"

inline void memcpy(uint8_t *dest, const uint8_t *src, uint32_t len)
{
    while ((len--)>=0)
    {
        *dest++ = *src++;
    }
}

inline void memset(void *dest, uint8_t val, uint32_t len)
{
    while ((len--)>=0)
    {
        *((uint8_t *)dest++) = val;
    }
}

void bzero(void *dest, uint32_t len);

int strcmp(const char *str1, const char *str2);

char *strcpy(char *dest, const char *src);

char *strcat(char *dest, const char *src);

int strlen(const char *src);