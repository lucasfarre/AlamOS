#include "../include/shell.h"

extern int crazyMode;
extern buffer testBuffer;
extern buffer stdoutBuffer;
extern buffer stdinBuffer;

program echo = 
    {"echo", echoFunction, "     Imprime una linea de texto."};
program man = 
    {"man", manFunction, "      Muestra ayuda de los programas."};
program timeProgram = 
    {"time", timeFunction, "     Muestra la hora actual."};
program temp = 
    {"temp", tempFunction, "     Muestra la temperatura del CPU."};
program crazy = 
    {"crazy", crazyFunction, "    Cambia de tema cada 55 ms."};
program buftest = 
    {"buftest", buftestFunction, "  Testea bufferToScreen."};
program clear = 
    {"clear", clearFunction, "    Limpia la pantalla."};
program devby = 
    {"devby", devbyFunction, "    Muestra info de los developers."};
program lspciProgram = 
    {"lspci", lspciFunction, "    Muestra info del hardware."};
program raisetemp = 
    {"raisetemp", raisetempFunction, "Incrementa la temperatura."};
program systest =
    {"systest", systestFunction, "  Testea el sistema."};
    
program * programs[MAX_PROGRAMS] = {&echo, &man, &timeProgram, &lspciProgram,
                                    &temp, &crazy, &buftest, &clear, &devby,
                                    &raisetemp, &systest};

int echoFunction(char * s) {
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
    printf("No existe entrada de manual para %s.\n", s);
    return 0;
}

int timeFunction(char * s) {
    char timeString[9];
    time_t t;
    time(&t);
    printf("Son las %s.\n", asctime(timeString, &t));
    return 0;
}

int tempFunction(char * s) {
    printf("La temperatura del TJ Max es de %d *C.\n", tj_max());
    printf("La temperatura del Digital Readout es de %d *C.\n", temp_asm());
    printf("La temperatura del CPU es de %d *C.\n", tj_max() - temp_asm());
    return 0;
}

int crazyFunction(char * s) {
    int c;
    crazyMode = 1;
    printf("%s", "Presione Enter para salir del modo crazy.\n");
    while((c = getchar()) != '\n');
    crazyMode = 0;
    setScreenTheme(DEFAULT_THEME);
    setRowTheme(0, BLACK_THEME);
    return 0;
}

int buftestFunction(char * s) {
    writeBuffer(&testBuffer, s, strlen(s));
    bufferToScreen(&testBuffer);
    return 0;
}

int clearFunction(char * s) {
    defaultScreen();
    return 0;
}

int devbyFunction(char * s) {
    printf("\nAlamOS fue desarrollado por:\n\n");
    printf("\t\t* Franco Meola\n");
    printf("\t\t* Lucas Farre\n\n");
    printf("Con la colaboracion de:\n\n");
    printf("\t\t* OSDev Wiki\n");
    printf("\t\t* K & R: The C Programming Language\n");
    printf("\t\t* Intel Architectures Software Developer's Manual\n");
    printf("\t\t* The GNU Project\n\n");
    printf("AlamOS. Copyright 2013. All Rights Reserved.\n\n");
    return 0;
}

int lspciFunction(char * s) {
    lspci();
    return 0;
}

int raisetempFunction(char * s) {
    long double x = 1.41;
    long double y = 3.14;
    long double z = 9.99;
    printf("Presione enter para salir: ");
    while(getchar() != '\n') {
       x = (int)(x * y * z) >> 16;
       y = (int)(((int)x / (int)y / (int)z) ^ 0xFF) << 8;
       z = (int)(((int)x ^ (int)y) * ((int)y ^ (int)z)) >> 16;
       x = x - y + z;
    }
    return 0;
}

int systestFunction(char * s) {
    char name[MAX_INPUT_LENGHT];
    int i;
    printf("Bienvenido al programa de testeo de AlamOS\n");
    printf("Ingrese su nombre y presione enter: ");
    scanf("%s", name);
    printf("\nLo estabamos esperando Sr. %s\n", name);
    printf("Ingrese un numero entero: ");
    scanf("%d", &i);
    printf("El numero ingresado es: %d\n", i);
    printf("El numero %d es %x en base hexadecimal.\n", i, i);
    printf("El numero %d es %b en base binaria.\n", i, i);
    printf("El numero %d es %o en base octal.\n", i, i);
    printf("Gracias por utilizar systest.");
    return 0;
}

int shell(void) {
    int i = 0, j, c, count = 0, row, column;
    char cmd[MAX_COMMAND_LENGHT] = {0};
    char name[MAX_NAME_LENGHT] = {0};
    char args[MAX_ARGS_LENGHT] = {0};
    setFirstScrollableRow(2);
    getCursorPosition(&row, &column);
    if(column != 0)
        putchar('\n');
    printPrompt();
    if((c = getchar()) == '\n') {
        putchar('\n');
        return 0;
    }
    if(c != '\b') {
        count++;
        cmd[i++] = c;
        putchar(c);
    }
    while((c = getchar()) != '\n' && i < MAX_COMMAND_LENGHT) {
        if(c == '\b') {
            count--;
            if(i >= 1)
                i--;
        }
        else {
            count++;
            cmd[i++] = c;
        }
        if(count <= -1)
            count = 0;
        else
            putchar(c);
    }
    cmd[i] = 0;
    if(i >= MAX_COMMAND_LENGHT) {
        printf("%s","\nUps!: Superaste el limite de caracteres del comando.\n");
        return 0;
    }
    putchar('\n');
    for(i = 0; cmd[i] != ' ' && cmd[i] != 0 && i < MAX_NAME_LENGHT; i++)
        name[i] = cmd[i];
    name[i] = 0;
    if(i >= MAX_NAME_LENGHT) {
        printf("%s","\nUps!: Superaste el limite de caracteres del comando.\n");
        return 0;
    }
    if(cmd[i++] == ' ') {
        for(j = 0; cmd[i] != 0 && i < MAX_ARGS_LENGHT; i++, j++)
            args[j] = cmd[i];
        args[j] = 0;
        if(i >= MAX_ARGS_LENGHT) {
            printf("%s","\nUps!: Superaste el limite de caracteres ");
            printf("%s","de los argumentos.\n");
            return 0;
        }
    }
    else
        args[0] = 0;
    for(i = 0; i < MAX_PROGRAMS && programs[i] != NULL; i++)
        if(strcmp((programs[i])->name, name) == 0)
            return programs[i]->function(args);
    printf("%s: no se encontro la orden.\n", name);
    return 0;
}

void printPrompt(void) {
    printf("AlamOS:$> ");
}
