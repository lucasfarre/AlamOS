#ifndef _syscalls_
#define _syscalls_

#include "defs.h"
#include "./lib/stdio.h"
#include "buffers.h"
#include "./drivers/video.h"
#include "./drivers/keyboard.h"

#define STDIN 0
#define STDOUT 1
#define STDERR 2

typedef unsigned char byte;
typedef unsigned int size_t;
typedef short int ssize_t;

ssize_t write(int fd, const void * buf, size_t count);
ssize_t read(int fd, void * buf, size_t count);

extern ssize_t write_int80h(int fd, const void * buf, size_t count);
extern ssize_t read_int80h(int fd, void * buf, size_t count);

#endif
