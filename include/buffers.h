
#ifndef _buffers_
#define _buffers_

#include "./lib/string.h"

#define EOF -1

#define MAX_BUFFERS 10
#define STDIN_BUFFER_DIM 80 * 25 * 2
#define STDOUT_BUFFER_DIM 80 * 25 * 2
#define STDERR_BUFFER_DIM 80 * 25 * 2

typedef unsigned char byte;
typedef unsigned int size_t;
typedef short int ssize_t;

typedef struct {
    byte * vec;
    int dim;
    int last;
} buffer;

int enqueueBuffer(byte, buffer *);
byte dequeueBuffer(buffer *);

void readBuffer(void *, const buffer *, size_t);
void writeBuffer(buffer *, const void *, size_t);

#endif
