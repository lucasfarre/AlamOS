#include "../../include/drivers/time.h"

/* Fuente consultada: http://wiki.osdev.org/RTC */
/* Turning on IRQ 8 */

void time(time_t * tp) {
    clearInterrupts();
    outportb(0x70, 4);
    tp->tm_hour = inportb(0x71);
    outportb(0x70, 2);
    tp->tm_min = inportb(0x71);
    outportb(0x70, 0);
    tp->tm_sec = inportb(0x71);
    setInterrupts();
    return;
}

char * asctime(char * str_time, const time_t * tp) {
    str_time[0] = ((tp->tm_hour & 0xF0) >> 4) + '0';
    str_time[1] = ((tp->tm_hour & 0x0F)) + '0';
    str_time[2] = ':';
    str_time[3] = ((tp->tm_min & 0xF0) >> 4) + '0';
    str_time[4] = ((tp->tm_min & 0x0F)) + '0';
    str_time[5] = ':';
    str_time[6] = ((tp->tm_sec & 0xF0) >> 4) + '0';
    str_time[7] = ((tp->tm_sec & 0x0F)) + '0';
    str_time[8] = 0;
    return str_time;
}
