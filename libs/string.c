#include "string.h"

inline void *memcpy(uint8_t *dest, const uint8_t *src, uint32_t len)
{
    while ((len--)>=0)
    {
        *dest++ = *src++;
    }
    return dest;
}

inline void memset(void *dest, uint8_t val, uint32_t len)
{
    while ((len--)>=0)
    {
        *((uint8_t *)dest++) = val;
    }
}

/*
    Set N bytes of dest to zero
*/
inline void bzero(void *dest, uint32_t len)
{
    memset(dest, '\0', len);
}

/* Compare S1 and S2, returning less than, equal to or
   greater than zero if S1 is lexicographically less than,
   equal to or greater than S2.  */
int strcmp(const char *str1, const char *str2)
{
    const unsigned char *s1 = (const unsigned char *) str1;
    const unsigned char *s2 = (const unsigned char *) str2;
    unsigned char c1, c2;

    do
    {
        c1 = (unsigned char) *s1++;
        c2 = (unsigned char) *s2++;
        if (c1 == '\0')
        {
            return c1 - c2;
        }
    } while (c1 == c2);
    
    return c1 - c2;
}

char *strcpy(char *dest, const char *src)
{
    return memcpy(dest, src, strlen(src) + 1);
}

char *strcat(char *dest, const char *src)
{
    return strcpy(dest + strlen(dest), src);
}

int strlen(const char *src)
{
    unsigned int len = 0;
    while (src[len++] != '\0');
    return len - 1;
}