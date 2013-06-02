#include "../defs.h"

#ifndef _video_
#define _video_

#define VIDEO_PORT 0xB8000
#define MIN_VIDEO_INDEX 0
#define MAX_VIDEO_INDEX (MAX_ROW * MAX_COLUMN * 2)

#define DIM_COLUMNS 80
#define DIM_COLUMNS_REAL DIM_COLUMNS * 2

#define DIM_ROWS 25
#define DIM_ROWS_REAL DIM_ROWS * 2

#define MIN_ROW 0
#define MAX_ROW 24
#define MIN_COLUMN 0
#define MAX_COLUMN 79

#define DEFAULT_THEME BLUE_THEME
#define BLANK_CHAR ' '
#define WHITE_THEME 0x07 // Letras blancas, fondo negro
#define GREEN_THEME 0x02 // Letras verdes, fondo negro
#define BLUE_THEME 0x1F  // Letras blancas, fondo azul

int printCharVector(int, byte);
int printCharMatrix(int, int, byte);
int printCharAdvancedVector(int, byte, byte);
int printCharAdvancedMatrix(int, int, byte, byte);
//int printStringAdvanced(int, char *, byte);
//int printString(int, char *);
void clearScreen(void);
void clearScreenAdvanced(byte);
int realVideoPosition(int);
void setScreenTheme(byte);

#endif
