#include "../include/buffers.h"

byte stdinBufferVector[STDIN_BUFFER_DIM] = {EOF};
byte stdoutBufferVector[STDOUT_BUFFER_DIM] = {EOF};
byte stderrBufferVector[STDERR_BUFFER_DIM] = {EOF};

buffer stdinBuffer = {stdinBufferVector, STDIN_BUFFER_DIM, 0};
buffer stdoutBuffer = {stdoutBufferVector, STDOUT_BUFFER_DIM, 0};
buffer stderrBuffer = {stderrBufferVector, STDERR_BUFFER_DIM, 0};

buffer * buffers[MAX_BUFFERS] = {&stdinBuffer, &stdoutBuffer, &stderrBuffer};

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
    memcpy(buf->vec, ct, n);
}
