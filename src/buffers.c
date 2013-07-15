#include "../include/buffers.h"

byte stdinBufferVector[STDIN_BUFFER_DIM] = {EOF}; /* Teclado */
byte stdoutBufferVector[STDOUT_BUFFER_DIM] = {EOF}; /* Para testeo */
byte stderrBufferVector[STDERR_BUFFER_DIM] = {EOF}; /* Para uso futuro */
byte testBufferVector[TEST_BUFFER_DIM] = {EOF}; /* Para testeo */

buffer stdinBuffer = {stdinBufferVector, STDIN_BUFFER_DIM, 0};
buffer stdoutBuffer = {stdoutBufferVector, STDOUT_BUFFER_DIM, 0};
buffer stderrBuffer = {stderrBufferVector, STDERR_BUFFER_DIM, 0};
buffer testBuffer = {testBufferVector, TEST_BUFFER_DIM, 0};

buffer * buffers[MAX_BUFFERS] = {&stdinBuffer, &stdoutBuffer, 
                                 &stderrBuffer, &testBuffer};

int enqueueBuffer(byte c, buffer * buf) {
    if(buf->last < buf->dim) {
        buf->vec[buf->last++] = c;
        return 1;
    }
    return 0;
}

byte dequeueBuffer(buffer * buf) {
    int i;
    if(buf->last > 0) {
        byte ret = buf->vec[0];
        for(i = 0; i < buf->dim - 1; i++)
            buf->vec[i] = buf->vec[i + 1];
        buf->last--;
        return ret;
    }
    return 0;
}

void readBuffer(void * ct, const buffer * buf, size_t n) {
    memcpy(ct, buf->vec, n);
}

void writeBuffer(buffer * buf, const void * ct, size_t n) { 
    if(buf->last + n < buf->dim) {
        memcpy(buf->vec + buf->last, ct, n);
        buf->last += n;
    }
    else {
        memcpy(buf->vec, ct, n);
        buf->last = n;
    }
}
