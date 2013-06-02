#include "./lib/stdio.h"
#include "./drivers/video.h"
#include "./drivers/keyboard.h"
#include "./drivers/time.h"
#include "defs.h"
#include "kasm.h"

#ifndef _ints_
#define _ints_

/* Interrupción del timer tick */
void int_08(void);

/* Interrupción de teclado */
void int_09(int);

void int_1A(void);

#endif
