#include "../include/kernel.h"

DESCR_INT idt[0xA];		/* IDT de 10 entradas */
IDTR idtr;				/* IDTR */

extern FILE * * files;
extern buffer stdinBuffer;
extern FILE stdoutFile;
extern FILE stdinFile;
extern void set_cursor(byte row, byte column);
extern dword temp_asm(void);
byte inportb(word port);

/*
** kmain()
** Punto de entrada de código C.
*/

int crazyMode = 1;

int kmain() {
    
    /* Borra la pantalla. */
    clearScreen();

    /* Carga de IDT con las Rutinas de Atencion */
    setup_IDT_entry (&idt[0x08], 0x08, (dword)&_int_08_hand, ACS_INT, 0);
    setup_IDT_entry (&idt[0x09], 0x08, (dword)&_int_09_hand, ACS_INT, 0);
    setup_IDT_entry (&idt[0x80], 0x08, (dword)&_int_80_hand, ACS_INT, 0);

    /* Carga de IDTR */
	idtr.base = 0;
	idtr.base +=(dword) &idt;
	idtr.limit = sizeof(idt)-1;

	_lidt (&idtr);

	clearInterrupts();
    
    /* Configuro la mascara de los PIC */
   _mascaraPIC1(0xFC); // Habilito IRQ1 para teclado
   _mascaraPIC2(0xFF); // HAbilito IRQ8 para RTC
        
    setInterrupts();

    /* Imprimo Splashscreen */   
    
    setCursorPosition(7,13);
    printf("%s","  /$$$$$$ /$$                       /$$$$$$  /$$$$$$");
    setCursorPosition(8,13);
    printf("%s"," /$$__  $| $$                      /$$__  $$/$$__  $$");
    setCursorPosition(9,13);
    printf("%s","| $$  \\ $| $$ /$$$$$$ /$$$$$$/$$$$| $$  \\ $| $$  \\__/");
    setCursorPosition(10,13);
    printf("%s","| $$$$$$$| $$|____  $| $$_  $$_  $| $$  | $|  $$$$$$");
    setCursorPosition(11,13);
    printf("%s","| $$__  $| $$ /$$$$$$| $$ \\ $$ \\ $| $$  | $$\\____  $$");
    setCursorPosition(12,13);
    printf("%s","| $$  | $| $$/$$__  $| $$ | $$ | $| $$  | $$/$$  \\ $$");
    setCursorPosition(13,13);
    printf("%s","| $$  | $| $$/$$__  $| $$ | $$ | $| $$  | $$/$$  \\ $$");
    setCursorPosition(14,13);
    printf("%s","| $$  | $| $|  $$$$$$| $$ | $$ | $|  $$$$$$|  $$$$$$/");
    setCursorPosition(15,13);
    printf("%s","|__/  |__|__/\\_______|__/ |__/ |__/\\______/ \\______/");
    
    while(getchar() != '\n');
    crazyMode = 0;
    defaultScreen();
    while(1) {
        shell();
    }
}

void defaultScreen(void) {
    setScreenTheme(DEFAULT_THEME);
    clearScreen();
    setRowTheme(0, BLACK_THEME);
    setCursorPosition(0,0);
    printf(" AlamOS");
    setCursorPosition(1,0);
    printf("%s", "************************************");
    printf("%s", " Shell ");
    printf("%s", "*************************************");
    setCursorPosition(2,0);
}
