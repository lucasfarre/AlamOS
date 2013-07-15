#include "../include/syscalls.h"

extern FILE * * files;
extern buffer stdinBuffer;
extern buffer stdoutBuffer;

ssize_t write(int fd, const void * buf, size_t count) {
    int i;
    if(fd == STDOUT) {
        for(i = 0; i < count; i++) {
            if(printChar(*(char *)buf))
                writeBuffer(&stdoutBuffer, buf, count);
            else
                return -1;
        }
    }
    else
        ; /* Para uso futuro */
    return count;
}

ssize_t read(int fd, void * buf, size_t count) {
    int i;
    if(fd == STDIN) {
        for(i = 0; i < count; i++) {
            while(stdinBuffer.last == 0);
            *(byte *)buf = dequeueBuffer(&stdinBuffer);
        }
    }
    else
        ; /* Para uso futuro */
    return count;
}
