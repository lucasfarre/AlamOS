#ifndef _time_h
#define _time_h

#include "../kasm.h"

typedef struct {
    int tm_sec;
    int tm_min;
    int tm_hour;
} time_t;

/* BackEnd: Guarda el tiempo en la estructura */
void time(time_t * tp);

/* FrontEnd: Convierte a una cadena de texto el tiempo */
char * asctime(char * str_time, const time_t * tp);

int BCDtoDecimal(int bcd);

#endif
