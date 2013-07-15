#include "./lib/stdio.h"
#include "./drivers/video.h"
#include "./drivers/keyboard.h"
#include "./lib/time.h"
#include "defs.h"
#include "kasm.h"

#ifndef _ints_
#define _ints_

extern dword temp_asm(void);
extern dword tj_max(void);

/* Interrupcion del Timer Tick */
void int_08(void);

/* Interrupcion de Teclado */
void int_09(int);

#endif
