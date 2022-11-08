/*
 * io.c
 * Version 1.00 (C99)  
 * 
 * Copyright 2015 Steven James (www.perfectconsulting.co.uk)
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 */

#include "io.h"

#ifdef __unix__
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

/*************************************************************************
 * NOTE: Replace these functions for custom I/O e.g. UART                *
 *************************************************************************/

int getch(void) {
    struct termios original, tile;
    int ch;
    
    /* NOTE(MJ): Get original terminal I/O settings */
    tcgetattr(STDIN_FILENO, &original); 
    tile = original; 
    tile.c_lflag &= ~(ICANON | ECHO); 
    tile.c_cc[VTIME] = 0;
    tile.c_cc[VMIN] = 0;
    /* NOTE(MJ); Set new teminal I/O settings */
    tcsetattr(STDIN_FILENO, TCSANOW, &tile); 
    
    ch = getc(stdin);
 
    /* NOTE(MJ): Set original terminal I/O settings */   
    tcsetattr(STDIN_FILENO, TCSANOW, &original);
    
    return ch;
}
#endif

/* TODO(MJ): This hasn't been tested yet... */
int keypressed(void) {
    char ch = getch();

    if (ch != EOF) {
        ungetch(ch);
        return 1;
    }

    return 0;
}
