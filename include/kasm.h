#ifndef _kasm_
#define _kasm_

#include "defs.h"

unsigned int _read_msw();

void _lidt (IDTR *idtr);

/* Escribe máscara de PIC1 */
void _mascaraPIC1 (byte mascara);

/* Escribe máscara de PIC2 */
void _mascaraPIC2 (byte mascara);  

/* Deshabilita las interrupciones */
void clearInterrupts(void); 

/* Habilita las interrupciones */       
void setInterrupts(void);	 

/* Handler de la int del Timer Tick */
void _int_08_hand(void);  
    
/* Handler de la int del Teclado */
void _int_09_hand(unsigned char);  

void _int_1A_hand(void);        

/* Outport */
void outportb(word port, byte source);
/* Inport */
dword inportb(word port);

void _debug (void);

#endif
