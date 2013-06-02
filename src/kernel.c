#include "../include/kernel.h"

DESCR_INT idt[0xA];		/* IDT de 10 entradas */
IDTR idtr;				/* IDTR */

int tickpos = 0;
extern FILE * * files;
extern buffer stdinBuffer;
extern FILE stdoutFile;
extern FILE stdinFile;
extern void set_cursor(byte row, byte column);
extern dword temp_asm(void);

/*
** kmain()
** Punto de entrada de código C.
*/

int locura = 1;

int kmain() {
    
/* Borra la pantalla. */
    clearScreen();

/* Carga de IDT con la Rutina de Atención de IRQ0 */
    setup_IDT_entry (&idt[0x08], 0x08, (dword)&_int_08_hand, ACS_INT, 0);
    setup_IDT_entry (&idt[0x09], 0x08, (dword)&_int_09_hand, ACS_INT, 0);
    //setup_IDT_entry (&idt[0x1A], 0x08, (dword)&_int_1A_hand, ACS_INT, 0);

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
    
    
    
    //word current = inportb(0x71);
    //current |= (0x1 << 2);
    //outportb(0x71, current);
    //
    //
    //time_t t;
    //time(&t);
    //char s[10];
    //puts(asctime(s, &t));
    //putchar('\n');
    //
    //
    //byte * tempRegister = (byte *)0x19C;
    //word temp = inportb((word)(tempRegister + 2));;
    //int digitalReadout = (temp & 0x007F);
    //printf("%d",digitalReadout);
    //
    //char s[10];
    //int a;
    //int c1,c2,c3;
    //printf("Hex: %x\n",255);
    //printf("Bin: %b\n",0xFFFF);
    //printf("Dec: %d\n",255);
    //printf("Dec: %d\n",-15);
    //printf("Char: %c\n", 'T');
    //printf("Octal: %o\n", 255);
    //printf("String: %s\n",s);
    //printf("%d %o %b %x %s",255,0777,255,255,"hola");
    //puts(s);
    //while ( (c = getchar()) != '\n' );
   
    //c1 = getchar();
    //c2 = getchar();
    //c3 = getchar();
    //putchar(c1);
    //putchar(c2);
    //putchar(c3);
    //printf("Ingrese un numero: ");
    //while ( (c = getchar()) != '\n' );
    
    
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
    locura = 0;
    setScreenTheme(DEFAULT_THEME);
    clearScreenHeader(" AlamOS", BLACK_THEME);
    setCursorPosition(2,0);
   
    while(1) {
        int row, column;
        getCursorPosition(&row, &column);
        if(row >= 22) {
            clearScreenHeader(" AlamOS", BLACK_THEME);
            setCursorPosition(2,0);
        }
        shell();
    }
}
