#include "defs.h"

#ifndef _kc_
#define _kc_

/* Muestra la imagen de inicio */
void showSplashScreen();

/* Tiempo de espera */
void wait(int time);

/* Limpia la pantalla */
/* void k_clear_screen(); */

/* Inicializa la entrada del IDT */
void setup_IDT_entry (DESCR_INT *item, byte selector, dword offset, byte access,
			 byte cero);

#endif