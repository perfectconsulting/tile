/*
 * tile2.h
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

 
#ifndef TILE2_H
#define TILE2_H

#ifdef __unix__
#include <stdint.h>
typedef uint16_t word;
typedef int16_t sword;
typedef uint8_t byte;
typedef uint32_t dword;
typedef int32_t sdword;
#else
typedef unsigned short word;
typedef signed short sword;
typedef unsigned char byte;
typedef unsigned long dword;
typedef signed long sdword;
#endif


#define VM_MEMORY_SIZE			0xffff
#define VM_STACK_GAP			0x40

#define VM_STATE_EXECUTE		0
#define VM_STATE_HAULT			1

#define VM_STACK_PROTECTION

#endif /* TILE2_H */