#include "string.h"
#include <stddef.h>
#define uint8_t unsigned short
#define uint16_t unsigned int
#define uint32_t unsigned long

char* strcat(char *dest, const char *src)
{
    char *rdest = dest;

    while (*dest)
      dest++;
    while (*dest++ = *src++)
      ;
    return rdest;
}

char* strcat(char *dest, const char src)
{
    char *rdest = dest;

    while (*dest)
      dest++;
    while (*dest++ = src)
      ;
    return rdest;
}


int strlen(const char * s) {
    int len = 0;
    while(*s++)
        len++;
    return len;
}

char *strncpy(char *destString, const char *sourceString,int maxLength)
{
    unsigned count;

    if ((destString == (char *) NULL) || (sourceString == (char *) NULL))
    {
        return (destString = NULL);
    }

    if (maxLength > 255)
        maxLength = 255;

    for (count = 0; (int)count < (int)maxLength; count ++)
    {
        destString[count] = sourceString[count];

        if (sourceString[count] == '\0')
            break;
    }

    if (count >= 255)
    {
        return (destString = NULL);
    }

    return (destString);
}

int strcmp(const char *dst, char *src)
{
    int i = 0;

    if (strlen(dst) != strlen(src))
        return 1;

    return strncmp(dst, src, strlen(dst));
}

char * strstr(const char *in, const char *str) {
    char c;
    uint32_t len;

    c = *str++;
    if (!c)
        return (char *) in;

    len = strlen(str);
    do {
        char sc;

        do {
            sc = *in++;
            if (!sc)
                return (char *) 0;
        } while (sc != c);
    } while (strncmp(in, str, len) != 0);

    return (char *) (in - 1);
}

int strcpy(char *dst,const char *src)
{
    int i = 0;
    while ((*dst++ = *src++) != 0)
        i++;
    return i;
}

int strncmp( const char* s1, const char* s2, int c) {
    int result = 0;

    while ( c ) {
        result = *s1 - *s2++;

        if ( ( result != 0 ) || ( *s1++ == 0 ) ) {
            break;
        }

        c--;
    }

    return result;
}