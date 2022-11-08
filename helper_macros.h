/*
 * helper_macros.h
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

 
#ifndef HELPER_MACROS_H
#define HELPER_MACROS_H

#define ADDR_DWORD(a)			(*(dword*)(vm_base + (a)))
#define ADDR_WORD(a)			(*(word*)(vm_base + (a)))
#define ADDR_BYTE(a)			(*(byte*)(vm_base + (a)))

#define STACK_FREE				(ADDR_WORD(vm_sp))
#define STACK_TOP				(ADDR_WORD(vm_sp+2))
#define STACK_MIDDLE			(ADDR_WORD(vm_sp+4))
#define STACK_BOTTOM			(ADDR_WORD(vm_sp+6))

#endif /* HELPER_MACROS_H */