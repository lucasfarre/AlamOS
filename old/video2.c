#include "../../include/drivers/video.h"
#include "../../include/defs.h"

char * * video = (char * *) VIDEO_PORT;
byte theme = DEFAULT_THEME;

//int printCharAdvanced(int index, byte ascii, byte attribute) {
    //if(index >= MIN_VIDEO_INDEX / 2 && 
       //position <= MAX_VIDEO_INDEX / 2) {
        //video[index * 2] = ascii;
        //video[index * 2 + 1] = attribute;
        //return 1;
    //}
    //return 0;
//}

int printCharAdvancedVector(int index, byte ascii, byte attribute) {
    int row;
    int column;
    row = index / DIM_COLUMNS;
    if(index < DIM_COLUMNS)
        column = index;
    else
        column = index % DIM_COLUMNS - 1;
    return printCharAdvancedMatrix(row, column, ascii, attribute);
}

//int printCharAdvanced2(int row, int column, byte ascii, byte attribute) {
    //if(row >= MIN_ROW && row <= MAX_ROW && 
       //column >= MIN_COLUMN && column <= MAX_COLUMN) {
        //video[((row - 1) * MAX_COLUMN + column - 1) * 2] = ascii;
        //video[((row - 1) * MAX_COLUMN + column - 1) * 2 + 1] = attribute;
        //return 1;
    //}
    //return 0;
//}

int printCharAdvancedMatrix(int row, int column, byte ascii, byte attribute) {
    if(row >= MIN_ROW && row <= MAX_ROW && 
       column >= MIN_COLUMN && column <= MAX_COLUMN) {
        row *= 2;             // Convierte las filas y columnas en filas reales
        column *= 2;
        video[row][column] = ascii;
        video[row][column + 1] = attribute;
        return 1;
    }
    return 0;
}

int printCharVector(int index, byte ascii) {
    return printCharAdvancedVector(index, ascii, theme);
}

int printCharMatrix(int row, int column, byte ascii) {
    return printCharAdvancedMatrix(row, column, ascii, theme);
}

//int printStringAdvanced(int index, char * s, byte attribute) {
    //int count = 0;
    //while(*s != 0)
        //count += printCharAdvanced(index++, *(s++), attribute);
    //return count;
//}
//
//int printString(int index, char * s) {
    //return printStringAdvanced(index, s, theme);
//}

void clearScreenAdvanced(byte attribute) {
    int i, j;
    for(i = MIN_ROW; i < DIM_ROWS_REAL; i++) {
        for(j = MIN_COLUMN; j < DIM_COLUMNS_REAL; j += 2) {
            video[i][j] = BLANK_CHAR;
            video[i][j + 1] = attribute;
        }
    }
}

void clearScreen(void) {
	clearScreenAdvanced(theme);
}

void setScreenTheme(byte attribute) {
    theme = attribute;
    int i, j;
    for(i = MIN_ROW; i < DIM_ROWS_REAL; i++) {
        for(j = MIN_COLUMN; j++ < DIM_COLUMNS_REAL;)
            video[i][j++] = attribute;
    }
}
