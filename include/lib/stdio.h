
#ifndef _stdio_
#define _stdio_

#include "../syscalls.h"
#include "../buffers.h"
#include "stdarg.h"
#include "stdlib.h"
#include "ctype.h"

#define EOF -1
#define NULL 0
#define MAX_FILES 10

#define MAX_STRING_LENGTH 80

typedef unsigned char byte;

typedef struct {
    int fd;
    buffer * buf;
} FILE;

/* Standard Input Output Library */

/* Input */
int fgetc(FILE * stream);
char * fgets(char * s, int n, FILE * stream);
int getc(FILE * stream);
int getchar(void);
char * gets(char * s);
void scanf(char *fmt, ...);
void fscanf(FILE * stream, char *fmt, ...);
void vfscanf(FILE * stream, char *fmt, va_list ap);

/* Output */
int fputc(int c, FILE * stream);
int fputs(const char * s, FILE * stream);
int putc(int c, FILE * stream);
int putchar(int c);
int puts(const char * s);
void printf(char *fmt, ...);
void fprintf(FILE * stream, char *fmt, ...);
void vfprintf(FILE * stream, char *fmt, va_list ap);

#endif
