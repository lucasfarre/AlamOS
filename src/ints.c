#include "../include/ints.h"

extern buffer stdinBuffer;
extern int crazyMode;
int i = 0;

void int_08(void) { /* Interrupcion del Timer Tick */
    if(crazyMode)
        setScreenTheme(i++);
    int rowBackup, columnBackup;
    time_t t;
    char timeString[9];
    time(&t);
    getCursorPosition(&rowBackup, &columnBackup);
    setCursorPosition(0,64);
    printf("%d*C | %s", tj_max() - temp_asm(), asctime(timeString,&t));
    setCursorPosition(rowBackup, columnBackup);
}

void int_09(int scanCode) { /* Interrupcion del Teclado */
    int c = scanCodeToAscii(scanCode);
    if(c != NOP) {
        enqueueBuffer(c, &stdinBuffer);
    }
}

