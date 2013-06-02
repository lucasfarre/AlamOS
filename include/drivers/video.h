#ifndef _video_
#define _video_

#include "../defs.h"
#include "../lib/stdio.h"

#define ERROR -1

#define VIDEO_PORT 0xB8000

#define DIM_VECTOR DIM_ROWS * DIM_COLUMNS
#define DIM_REAL_VECTOR (DIM_VECTOR * 2)

#define DIM_ROWS 25
#define DIM_COLUMNS 80

#define BLANK_CHAR ' '

#define DEFAULT_THEME BLUE_THEME
#define BLACK_THEME 0x0F // Letras blancas, fondo negro
#define GREEN_THEME 0x02 // Letras verdes, fondo negro
#define BLUE_THEME 0x1F  // Letras blancas, fondo azul

#define TAB_SPACES 4

typedef unsigned char byte;

typedef struct {
    int row;
    int column;
} position ;

extern void set_cursor(byte row, byte column);
//void printCharForced(position p, byte ascii);
//void setAttibuteForced(position p, byte attribute);
//int positionToIndex(position p);
void setAttribute(byte attribute);
void setChar(byte ascii);
void getCursorPosition(int * row, int * column);
int isValidPosition(int row, int column);
void clearScreen(void);
void clearScreenAdvanced(byte attribute);
void clearScreenHeader(char * header, byte attribute);
void setScreenTheme(byte);
int printChar(byte c);
int setCursorPosition(int row, int column);
int incCursor(int);
int decCursor(int);
int newLine(void);
void cursorVisibility(int boolean);
#endif
