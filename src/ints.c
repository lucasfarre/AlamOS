#include "../include/ints.h"

extern buffer stdinBuffer;
extern int locura;
int i = 0;

void int_08(void) {
        if(locura)
            setScreenTheme(i++);
        int rowBackup, columnBackup;
        time_t t;
        char timeString[9];
        time(&t);
        getCursorPosition(&rowBackup, &columnBackup);
        setCursorPosition(0,71);
        printf("%s", asctime(timeString,&t));
        setCursorPosition(rowBackup, columnBackup);
}

void int_09(int scanCode) {
    int c = scanCodeToAscii(scanCode);
    if(c != NOP) {
        enqueueBuffer(c, &stdinBuffer);
    }
}

void int_1A(void) {
    int hour,min,sec;
    clearInterrupts();
    outportb(0x70, 4);
    hour = inportb(0x71);
    outportb(0x70, 2);
    min = inportb(0x71);
    outportb(0x70, 0);
    sec = inportb(0x71);
    setInterrupts();
    printf("%d%d:%d%d:%d%d",hour, min, sec);
}
