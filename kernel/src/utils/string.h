#ifndef STRING_H
#define STRING_H
#define uint8_t unsigned short
#define uint16_t unsigned int
#define uint32_t unsigned long
char* strcat(char *dest, const char *src);
char* strcat(char *dest, const char src);
int strlen(const char * s);
char *strncpy(char *destString, const char *sourceString,int maxLength);
int strcmp(const char *dst, char *src);
int strcpy(char *dst,const char *src);
int strncmp( const char* s1, const char* s2, int c );
#endif
