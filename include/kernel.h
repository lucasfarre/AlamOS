#ifndef _kernel_
#define _kernel_

#include "kasm.h"
#include "defs.h"
#include "kc.h"
#include "./drivers/video.h"
#include "./lib/stdio.h"
#include "./lib/stdlib.h"
#include "./lib/time.h"
#include "shell.h"
#include "./drivers/lspci.h"

#define OS_PID	0

int (*player)(void);

typedef enum eINT_80 {WRITE=0, READ} tINT_80;
typedef enum eUSER {U_KERNEL=0, U_NORMAL} tUSERS;

void defaultScreen(void);

/* __write
*
* Recibe como parámetros:
* - File Descriptor
* - Buffer del source
* - Cantidad
*
**/
size_t __write(int fd, const void* buffer, size_t count);

/* __read
*
* Recibe como parámetros:
* - File Descriptor
* - Buffer a donde escribir
* - Cantidad
*
**/
size_t __read(int fd, void* buffer, size_t count);

#endif
