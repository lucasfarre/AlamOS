/* .h */

int fprintf(FILE * stream, const char * format, ...);
int printf(const char * format, ...);
int fscanf(FILE * stream, const char * format, ...);
int scanf(const char * format, ...);

/* .c */

int printf(const char * format, ...) {
    return fprintf(stdout,format,...);
}

int scanf(const char * format, ... ) {
    return fscanf(stdin,format,...);
}

/* fputc escribe el caracter c (convertido a unsigned char) en stream.  *
** Retorna el caracter escrito o EOF en caso de error                   */

/* fprintf toma una salida y la convierte y escribe hacia el stream bajo el *
** control de format.                                                       *
** Retorna el número de caracteres escritos o un valor negativo si ocurrió  *
** algún un error                                                           */

int fprintf(FILE * stream, const char * format, ...) {
    int cant;
    int * input = format;
    cant = 0;
    while ( *input++ ) {
        if ( fputc(*input,stream) != EOF ) {
            cant++;
        }
        else
            return -1; /* Error */
    }
    return cant;
}

/* fgetc retorna el siguiente caracter de stream como unsigned char      *
** (convertido a un int), o EOF si encontró el fin de archivo o un error */

/* fscanf lee del stream bajo el control de format, y asigna los valores   *
** convertidos a través de argumentos subsecuentes, cada uno de los cuales *
** debe ser un puntero.                                                    *
** Retorna EOF si se encuentra fin de archivo o un error antes de la       *
** conversión; de otra forma regresa el número de artículos de entrada     *
** convertidos y asignados                                                 */

int fscanf(FILE * stream, const char * format, ...) {
    int cant, c;
    int * input = stream;
    cant = 0;
    while ( *input++ ) {
        if ( (c = fgetc(*input)) != EOF ) {
            if ( fputc(c,stream) != EOF )
                cant++;
            else
                return EOF; /* Error */
        }
        else
            return EOF; /* Error */
    }
    return cant;
}
