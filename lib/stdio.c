#include "../include/lib/stdio.h"

/* Standard Streams */

extern buffer stdinBuffer;
extern buffer stdoutBuffer;
extern buffer stderrBuffer;

FILE stdinFile = {0, &stdinBuffer};
FILE stdoutFile = {1, &stdoutBuffer};
FILE stderrFile = {2, &stderrBuffer};

FILE * files[MAX_FILES] = {&stdinFile, &stdoutFile, &stderrFile};


/* Standard Input Output Library */

/* Input */

void scanf(char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfscanf(&stdinFile, fmt, ap);
    va_end(ap);
}

void fscanf(FILE * stream, char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfscanf(stream, fmt, ap);
    va_end(ap);
}

void vfscanf(FILE * stream, char *fmt, va_list ap) {
    char *p;
    int *ival;
    for(p = fmt; *p; p++) {
        if (*p != '%') {
            if (getchar() != *p)
                return;
            continue;
        }
        switch(*++p) {
            case 'c': {
                ival = va_arg(ap, int *);
                *ival = getchar();
                break;
            }
            case 'd': {
                int c;
                char s[MAX_STRING_LENGTH];
                char * aux = s;
                ival = va_arg(ap, int *);
                while(isdigit(c = getchar()))
                    *aux++ = c;
                *aux = 0;
                *ival = atoi(s);
                break;
            }
            case 's': {
                fgets(va_arg(ap, char *), MAX_STRING_LENGTH, stream);
                break;
            }
            default: {
                if (getchar() != *p)
                    return;
                break;
            }
        }
    }
}

int fgetc(FILE * stream) {
    byte c;
    if(read(stream->fd, &c, 1) == 1)
        return c;
    return EOF;
}

char * fgets(char * s, int n, FILE * stream) {
    int i, c;
    for(i = 0; i < n; i++) {
        if((c = fgetc(stream)) == EOF)
            return NULL;
        else if(c == '\n')
            break;
        s[i] = c;
    }
    s[i] = 0;
    return s;
}

int getc(FILE * stream) {
    return fgetc(stream);
}

int getchar(void) {
    return getc(&stdinFile);
}

char * gets(char * s) {
    int i, c;
    for(i = 0; ; i++) {
        if((c = getchar()) == EOF)
            return NULL;
        else if(c == '\n')
            break;
        s[i] = c;
    }
    s[i] = 0;
    return s;
}

/* Output */

void printf(char *fmt, ...) {
    va_list ap; /* apunta a cada arg sin nombre en orden */
    va_start(ap, fmt); /* hace que ap apunte al primer arg sin nombre */
    vfprintf(&stdoutFile, fmt, ap);
    va_end(ap); /* limpia cuando todo está hecho */
}

void fprintf(FILE * stream, char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stream, fmt, ap);
    va_end(ap);
}

/* Idea: K & R Capitulo 7 */
/* minprintf: minimal printf with variable argument list */
void vfprintf(FILE * stream, char *fmt, va_list ap) {
    char *p;
    int ival = 0;
    char s[MAX_STRING_LENGTH];
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            fputc(*p, stream);
            continue;
        }
        switch (*++p) {
            case 'd':
            case 'i': {
                ival = va_arg(ap, int);
                fputs(itoa(s, ival, 10), stream);
                break;
            }
            case 'x': 
            case 'X': {
                ival = va_arg(ap, int);
                fputs(itoa(s, ival, 16), stream);
                break;
            }
            case 'o': {
                ival = va_arg(ap, int);
                fputs(itoa(s, ival, 8), stream);
                break;
            }
            case 'b': {
                ival = va_arg(ap, int);
                fputs(itoa(s, ival, 2), stream);
                break;
            }
            case 'c': {
                ival = va_arg(ap, int);
                fputc(ival, stream);
                break;
            }
            case 's': {
                fputs(va_arg(ap, char *), stream);
                break;
            }
            default: {
                fputc(*p, stream);
                break;
            }
        }
    }
}

int fputc(int c, FILE * stream) {
    if(write(stream->fd, &c, 1) == 1)
        return c;
    return EOF;
}

int fputs(const char * s, FILE * stream) {
    while(*s != 0)
        if(fputc(*s++, stream) == EOF)
            return EOF;
    return 1;
}

int putc(int c, FILE * stream) {
    return fputc(c, stream);
}

int putchar(int c) {
    return putc(c, &stdoutFile);
}

int puts(const char * s) {
    return fputs(s, &stdoutFile);
}


