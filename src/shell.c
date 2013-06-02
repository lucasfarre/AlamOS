#include "../include/shell.h"

program echo = {"echo", echoFunction, "Imprime una linea de texto."};
program man = {"man", manFunction, "Muestra ayuda de los programas."};
program timeProgram = {"time", timeFunction, "Muestra la hora actual."};
program temp = {"temp", tempFunction, "Muestra la temperatura del CPU."};
program * programs[MAX_PROGRAMS] = {&echo, &man, &timeProgram, &temp, NULL};


int echoFunction(char * s) {
    if(*s == 0) {
        printf("%s\n", "Se esperaba algun parametro.");
        return 0;
    }
    printf("%s\n",s);
    return 0;
}

int manFunction(char * s) {
    int i;
    if(*s == 0) {
        for(i = 0; i < MAX_PROGRAMS && programs[i] != NULL; i++) {
            printf("%s\t%s\n", (programs[i])->name, (programs[i])->man);
        }
        return 0;
    }
    for(i = 0; i < MAX_PROGRAMS && programs[i] != NULL; i++) {
        if(strcmp((programs[i])->name, s) == 0) {
            printf("%s: %s\n", (programs[i])->name, (programs[i])->man);
            return 0;
        }
    }
    printf("No hay ayuda para este comando\n");
    return 0;
}

int timeFunction(char * s) {
    char timeString[9];
    time_t t;
    time(&t);
    printf("Son las %s\n", asctime(timeString, &t));
    return 0;
}

int tempFunction(char * s) {
    printf("La temperatura del TJ Max es de %d *C\n", tj_max());
    printf("La temperatura del Digital Readout es de %d *C\n", temp_asm());
    printf("La temperatura del CPU es de %d *C\n", tj_max() - temp_asm());
    return 0;
}

int shell(void) {
    int i = 0, c;
    char name[MAX_NAME_LENGHT] = {0};
    char args[MAX_ARGS_LENGHT] = {0};
    printPromt();
    if((c = getchar()) == '\n') {
        putchar(c);
        return 0;
    }
    putchar(c);
    name[i++] = c; 
    while((c = getchar()) != ' ' && c != '\n') {
        putchar(c);
        name[i++] = c;
    }
    putchar(c);
    name[i] = 0;
    i = 0;
    if(c == ' ') {
        while((c = getchar()) != '\n') {
            putchar(c);
            args[i++] = c;
        }
        putchar(c);
    }
    args[i] = 0;
    for(i = 0; i < MAX_PROGRAMS && programs[i] != NULL; i++) {
        if(strcmp((programs[i])->name, name) == 0)
            return programs[i]->function(args);
    }
    printf("%s: no se encontro la orden.\n", name);
    return 0;
}

void printPromt(void) {
    printf("AlamOS:$> ");
}
