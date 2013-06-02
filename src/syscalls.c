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
        ;//writeBuffer(files[fd]->buf, buf, count);
    return count;
}

ssize_t read(int fd, void * buf, size_t count) {
    int i;
    if(fd == STDIN) {
        while(stdinBuffer.last == 0);
        for(i = 0; i < count; i++)
            *(byte *)buf = dequeueBuffer(&stdinBuffer); /*files[fd]->buf por que no andas?*/
    }
    else
        ;//readBuffer(buf, files[fd]->buf, count);
    return count;
}
