/*
 * io.h
 * Version 1.00 (C99)  
 * 
 * Copyright 2015 Steven James (www.perfectconsulting.co.uk)
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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