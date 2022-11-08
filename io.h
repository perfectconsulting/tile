/*
 * io.h
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

 
#ifndef IO_H
#define IO_H

/* TODO(MJ): Placing standard libraries here, for now */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* NOTE(MJ): Define macOS as a UNIX */
#if !defined(__unix__) && defined(__APPLE__) && defined(__MACH__)
#define __unix__
#endif

/* TODO(MJ): We should probably factor this out better... */
# if defined(CUSTOM_IO)
/* NOTE(MJ): Placeholder for custom IO functions e.g. UART */
#elif defined(__unix__)
#define ungetch(ch) ungetc(ch,stdin)

int getch(void);
int keypressed(void);
# else
#include <conio.h>

#define getch() _getch()
#define keypressed() _kbhit()
#endif

#ifdef DEBUG 
#define TRACE(fmt,...) \
  do { fprintf(stderr, "%s:%d:%s(): " fmt "\n", __FILE__, __LINE__, __func__, __VA_ARGS__); } while (0)
#else
/* Do nothing */
#define TRACE(fmt,...)
#endif

#endif /* IO_H */