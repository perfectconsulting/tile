/*
 * op_codes.h
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

 
#ifndef OP_CODES_H
#define OP_CODES_H

#define VM_OPCODE_NOOP		0x00
#define VM_OPCODE_HAULT		VM_OPCODE_NOOP + 1
#define VM_OPCODE_DEBUG		VM_OPCODE_NOOP + 2
// NOOP
// NOOP
// NOOP
// NOOP
// NOOP
// NOOP
// NOOP
// NOOP

#define VM_OPCODE_DUP		0x0a
#define VM_OPCODE_SWAP		VM_OPCODE_DUP + 1
#define VM_OPCODE_OVER		VM_OPCODE_DUP + 2
#define VM_OPCODE_ROT		VM_OPCODE_DUP + 3
#define VM_OPCODE_DROP		VM_OPCODE_DUP + 4
#define VM_OPCODE_RESET		VM_OPCODE_DUP + 5
#define VM_OPCODE_TOR		VM_OPCODE_DUP + 6
#define VM_OPCODE_RFROM		VM_OPCODE_DUP + 7
#define VM_OPCODE_RAT		VM_OPCODE_DUP + 8
// NOOP


#define VM_OPCODE_LIT		0x14
#define VM_OPCODE_ADD		VM_OPCODE_LIT + 1
#define VM_OPCODE_SUB		VM_OPCODE_LIT + 2
#define VM_OPCODE_MUL		VM_OPCODE_LIT + 3
#define VM_OPCODE_DIV		VM_OPCODE_LIT + 4
#define VM_OPCODE_MOD		VM_OPCODE_LIT + 5

// NOOP
// NOOP
// NOOP
// NOOP

#define VM_OPCODE_AND		0x1e
#define VM_OPCODE_OR		VM_OPCODE_AND + 1
#define VM_OPCODE_XOR		VM_OPCODE_AND + 2
#define VM_OPCODE_NOT		VM_OPCODE_AND + 3
#define VM_OPCODE_EQUAL		VM_OPCODE_AND + 4
#define VM_OPCODE_LESS		VM_OPCODE_AND + 5
#define VM_OPCODE_GREATER	VM_OPCODE_AND + 6
// NOOP
// NOOP

#define VM_OPCODE_FETCH		0x26
#define VM_OPCODE_CFETCH	VM_OPCODE_FETCH + 1
#define VM_OPCODE_STORE		VM_OPCODE_FETCH + 2
#define VM_OPCODE_CSTORE	VM_OPCODE_FETCH + 3

// NOOP
// NOOP
// NOOP
// NOOP

#define VM_OPCODE_BRANCH	0x2e
#define VM_OPCODE_0BRANCH	VM_OPCODE_BRANCH + 1
#define VM_OPCODE_JUMP		VM_OPCODE_BRANCH + 2
#define VM_OPCODE_CALL		VM_OPCODE_BRANCH + 3
#define VM_OPCODE_RET		VM_OPCODE_BRANCH + 4

// NOOP
// NOOP
// NOOP
// NOOP

#define VM_OPCODE_EMIT		0x37
#define VM_OPCODE_KEY		VM_OPCODE_EMIT + 1
#define VM_OPCODE_QKEY		VM_OPCODE_EMIT + 2

#endif /* OP_CODES_H */


