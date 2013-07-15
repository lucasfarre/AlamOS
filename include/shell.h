#ifndef _shell_
#define _shell_

#include "../include/lib/stdio.h"
#include "../include/lib/string.h"
#include "../include/lib/time.h"
#include "../include/buffers.h"
#include "../include/kernel.h"
#include "./drivers/lspci.h"

#define MAX_PROGRAMS 20
#define MAX_NAME_LENGHT 15
#define MAX_ARGS_LENGHT 30
#define MAX_COMMAND_LENGHT (MAX_NAME_LENGHT + MAX_ARGS_LENGHT)
#define MAX_INPUT_LENGHT 80 * 25 * 4
#define NULL 0

extern dword temp_asm(void);
extern dword tj_max(void);

int shell(void);
void printPrompt(void);
int manFunction(char * s);
int echoFunction(char * s);
int timeFunction(char * s);
int tempFunction(char * s); 
int crazyFunction(char * s);
int buftestFunction(char * s);
int clearFunction(char * s);
int devbyFunction(char * s);
int lspciFunction(char * s);
int raisetempFunction(char * s);
int systestFunction(char * s);

typedef struct {
    char * name;
    int (* function)(char * args);
    char * man;
} program;

#endif
