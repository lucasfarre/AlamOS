#ifndef _shell_
#define _shell_

#include "../include/lib/stdio.h"
#include "../include/lib/string.h"
#include "../include/drivers/time.h"

#define MAX_PROGRAMS 10
#define MAX_NAME_LENGHT 10
#define MAX_ARGS_LENGHT 80
#define DIM_HELP_CONTENT 4
#define NULL 0

extern dword temp_asm(void);
extern dword tj_max(void);


/* lista las ayudas de los comandos que cuentan con una */
int manFunction(char * s);
void printPromt(void);
int echoFunction(char * s);
int timeFunction(char * s);
int tempFunction(char * s); 
int shell(void);

// no puedo hacer un arreglo de punteros a funcion ni un arreglo de estructuras
// de programas donde cada una tenga su puntero a funcion porque varian los
// tipos de parametros y el tipo de salida

typedef struct {
    char * name;
    int (* function)(char * args);
    char * man;
} program;

// hago un arreglo de estructuras help

typedef struct {
    char * name;
    char * help;
} help_list;


#endif
