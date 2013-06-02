#include "../include/lib/string.h"

void * memcpy(void * s, const void * ct, size_t n) {
    int i;
    for (i = 0; i < n; i++) {
        *(byte *)s = *(byte *)ct;
    }
    return s;
}

char * strcpy(char * s, const char * ct) {
    char * aux = s;
    while (*ct) {
        *aux++ = *ct++;
    }
    return s;
}

/* FUENTE: K & R Capitulo 3 */
/* reverse: reverse string s in place */
void reverse(char * s) {
    int c, i, j;
    for(i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

int strlen(char * s) {
    int i;
    for(i = 0; *s++; i++);
    return i;
}

/*K & R Capitulo 5*/
int strcmp(const char * cs, const char * ct) {
    for(; *cs == *ct; cs++, ct++)
        if(*cs == '\0')
            return 0;
    return *cs - *ct;
}
