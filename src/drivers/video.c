#include "../../include/drivers/video.h"

char * video = (char *) VIDEO_PORT;
byte theme = DEFAULT_THEME;
position cursor = {0,0};
int visibleCursor = 1;

static int positionToIndex(position pos) {
    return pos.row * DIM_COLUMNS + pos.column;
}

static void setPositionChar(position pos, byte ascii) {
    int realIndex = positionToIndex(pos) * 2;
    video[realIndex] = ascii;
}

static void setPositionAttribute(position pos, byte attribute) {
    int realIndex = positionToIndex(pos) * 2;
    video[realIndex + 1] = attribute;
}

void setChar(byte ascii) {
    setPositionChar(cursor, ascii);
}

void setAttribute(byte attribute) {
    setPositionAttribute(cursor, attribute);
}

void getCursorPosition(int * row, int * column) {
    *row = cursor.row;
    *column = cursor.column;
}

int isValidPosition(int row, int column) {
    return row >= 0 && row < DIM_ROWS &&
           column >= 0 && column < DIM_COLUMNS;
}

int setCursorPosition(int row, int column) {
    if(isValidPosition(row, column)) {
        cursor.row = row;
        cursor.column = column;
        if(visibleCursor == 1)
            set_cursor(cursor.row, cursor.column);
        return 1;
    }
    return 0;
}

void clearScreen(void) {
	clearScreenAdvanced(theme);
}

void clearScreenAdvanced(byte attribute) {
	int i = 0;
    while(i < DIM_REAL_VECTOR) {
		video[i++] = BLANK_CHAR;
		video[i++] = attribute;
	}
}

void clearScreenHeader(char * header, byte attribute) {
    int i = 0, j;
    while(i < DIM_COLUMNS * 2) {
		video[i++] = BLANK_CHAR;
		video[i++] = attribute;
	}
    while(i < DIM_REAL_VECTOR) {
		video[i++] = BLANK_CHAR;
		video[i++] = theme;
	}
    for(i = 0, j = 0; header[i] != 0; i++, j+=2)
        video[j] = header[i];
}

void setScreenTheme(byte attribute) {
    theme = attribute;
    int i = 0;
	while(i++ < DIM_REAL_VECTOR) {
		video[i++] = theme;
	}
}

int printChar(byte c) {
    switch (c) {
        case '\n': return newLine();
        case '\t': return incCursor(TAB_SPACES);
        case '\b': {
            if(decCursor(1)) {
                setPositionChar(cursor, ' ');
                return 1;
            }
            return ERROR;
        }
        default: {
            setPositionChar(cursor, c);
            if(!incCursor(1))
                return ERROR;
            return 1;
        }
    }
}

int incCursor(int n) {
    int ret = 0;
    if(cursor.column + n < DIM_COLUMNS)
        ret = setCursorPosition(cursor.row, cursor.column + n);
    else
        ret = setCursorPosition(cursor.row + 1, 
                                cursor.column + n - DIM_COLUMNS);
    return ret;
}

int decCursor(int n) {
    int ret = 0;
    if(cursor.column - n < 0)
        ret = setCursorPosition(cursor.row - 1, 
                                cursor.column + DIM_COLUMNS - n);
    else
        ret = setCursorPosition(cursor.row, cursor.column - n);
    return ret;
}

int newLine(void) {
    return setCursorPosition(cursor.row + 1, 0);
}

void cursorVisibility(int boolean) {
    visibleCursor = boolean;
}

//void showCursor(int) {
//}

/*Falta Scrollear cuando llego al final!!!*/


/*
void scrollScreen(int rows, int direction) {
    if(direction == UP || direction == DOWN && rows > 0 && rows <= DIM_BUFFER)
*/
