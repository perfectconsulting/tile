/*
 * virtual-machine.c
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
#include "tile2.h"
#include "op_codes.h"
#include "helper_macros.h"

word vm_ip;
byte vm_state;
byte vm_op;

word vm_top;
word vm_bottom;

word vm_s0;
word vm_sp;
word vm_r0;
word vm_rp;
word vm_debug;

byte *vm_base;

void vm_debug_status(void);

void vm_op_noop(void){
}

void vm_op_hault(void){
	
     	vm_state = VM_STATE_HAULT;
}

void vm_op_debug(void){
	vm_debug = ! vm_debug;
}


void vm_op_dup(void){
	STACK_FREE = STACK_TOP;
	vm_sp-=2;
}

void vm_op_swap(void){
	STACK_TOP  ^= STACK_MIDDLE;
	STACK_MIDDLE ^= STACK_TOP;
	STACK_TOP  ^= STACK_MIDDLE;
}

void vm_op_over(void){
	STACK_FREE = STACK_MIDDLE;
	vm_sp-=2;
}

void vm_op_rot(void){
	STACK_FREE = STACK_BOTTOM;
	STACK_BOTTOM = STACK_MIDDLE;
	STACK_MIDDLE = STACK_TOP;
	STACK_TOP = ADDR_WORD(vm_sp);
}

void vm_op_drop(void){
	if(vm_sp < vm_s0)
		vm_sp+=2;
}

void vm_op_reset(void){
	vm_sp = vm_s0;
	vm_rp = vm_r0;
}

void vm_op_tor(void){
	ADDR_WORD(vm_rp) = STACK_TOP;
	vm_sp += 2;
	vm_rp -= 2;
}

void vm_op_rfrom(void){
	vm_rp += 2;
	STACK_FREE = ADDR_WORD(vm_rp);
	vm_sp -= 2;
}

void vm_op_rat(void){
	STACK_FREE = ADDR_WORD(vm_rp + 2);
	vm_sp -= 2;
}

void vm_op_lit(void){
	ADDR_WORD(vm_sp) = ADDR_WORD(vm_ip);
	vm_sp-=2;
	vm_ip+=2;
}

void vm_op_add(void){
	STACK_MIDDLE = STACK_MIDDLE + STACK_TOP;
	vm_sp+=2;
}

void vm_op_sub(void){
	STACK_MIDDLE = STACK_MIDDLE - STACK_TOP;
	vm_sp+=2;
}

void vm_op_mul(void){
	ADDR_DWORD(vm_sp) = STACK_MIDDLE * STACK_TOP;
	STACK_MIDDLE = (word)ADDR_DWORD(vm_sp) & 0xffff;
	STACK_TOP = (word)(ADDR_DWORD(vm_sp) >> 16) & 0xffff;
}

void vm_op_div(void){
	ADDR_DWORD(vm_sp) = (STACK_BOTTOM << 16) ^ (STACK_MIDDLE);
	STACK_MIDDLE = ADDR_DWORD(vm_sp) / (STACK_TOP);
	STACK_BOTTOM = ADDR_DWORD(vm_sp) % (STACK_TOP);
	vm_sp+=2;
}

void vm_op_mod(void){
	STACK_MIDDLE = STACK_MIDDLE % STACK_TOP;
	vm_sp+=2;
}

void vm_op_and(void){
	STACK_MIDDLE = STACK_MIDDLE & STACK_TOP;
	vm_sp+=2;
}

void vm_op_or(void){
	STACK_MIDDLE = STACK_MIDDLE | STACK_TOP;
	vm_sp+=2;
}

void vm_op_xor(void){
	STACK_MIDDLE = STACK_MIDDLE ^ STACK_TOP;
	vm_sp+=2;
}

void vm_op_not(void){
	STACK_TOP = ~(STACK_TOP);
}

void vm_op_equal(void){
	STACK_MIDDLE = (STACK_MIDDLE == STACK_TOP) ? 0xffff : 0;
	vm_sp+=2;
}

void vm_op_less(void){
	STACK_MIDDLE = (STACK_TOP < STACK_MIDDLE) ? 0xffff : 0;
	vm_sp+=2;
}

void vm_op_greater(void){
	STACK_MIDDLE = (STACK_TOP > STACK_MIDDLE) ? 0xffff : 0;
	vm_sp+=2;
}

void vm_op_fetch(void){
	STACK_TOP = ADDR_WORD(STACK_TOP); 
}

void vm_op_cfetch(void){
	STACK_TOP = ADDR_BYTE(STACK_TOP); 
}

void vm_op_store(void){
	ADDR_WORD(STACK_TOP) = STACK_MIDDLE;
	vm_sp+=4;
}

void vm_op_cstore(void){
	ADDR_BYTE(STACK_TOP) = STACK_MIDDLE;
	vm_sp+=4;
}

void vm_op_branch(void){
	vm_ip += ADDR_WORD(vm_ip) + 2;
}

void vm_op_0branch(void){
 	if(STACK_TOP == 0)
		vm_ip += ADDR_WORD(vm_ip);

	vm_sp += 2;
	vm_ip += 2;
}

void vm_op_jump(void){
	vm_ip = ADDR_WORD(vm_ip + 2);
}

void vm_op_call(void){
	ADDR_WORD(vm_rp) = vm_ip + 2;
	vm_rp -= 2;
	vm_ip = ADDR_WORD(vm_ip);
}

void vm_op_ret(void){
	vm_rp += 2;
	vm_ip = ADDR_WORD(vm_rp);
}

void vm_op_emit(void){
	putchar(STACK_TOP);
	vm_sp += 2;
}

void vm_op_key(void){
	ADDR_WORD(vm_sp) = _getch();
	putchar(ADDR_WORD(vm_sp));
	vm_sp -= 2;
}

void vm_op_qkey(void){
	ADDR_WORD(vm_sp) = _kbhit() ? 0xffff : 0;
	vm_sp -= 2;
}

void (*opcode[])() = { 
	vm_op_noop,		// 0x00
	vm_op_hault,
	vm_op_debug,
	vm_op_noop,
	vm_op_noop,
	vm_op_noop,
	vm_op_noop,
	vm_op_noop,
	vm_op_noop,
	vm_op_noop,
	vm_op_dup,		// 0x0a
	vm_op_swap,
	vm_op_over,
	vm_op_rot,
	vm_op_drop,
	vm_op_reset,
	vm_op_tor,
	vm_op_rfrom,
	vm_op_rat,
	vm_op_noop,
	vm_op_lit,		// 0x14
	vm_op_add,
	vm_op_sub,
	vm_op_mul,
	vm_op_div,
	vm_op_mod,
	vm_op_noop,
	vm_op_noop,
	vm_op_noop,
	vm_op_noop,
	vm_op_and,		// 0x1e
	vm_op_or,
	vm_op_xor,
	vm_op_not,
	vm_op_equal,
	vm_op_less,
	vm_op_greater,
	vm_op_noop,
	vm_op_fetch,	// 0x26
	vm_op_cfetch,
	vm_op_store,
	vm_op_cstore,
	vm_op_noop,
	vm_op_noop,
	vm_op_noop,
	vm_op_noop,
	vm_op_branch,	// 0x2e
	vm_op_0branch,
	vm_op_jump,
	vm_op_call,
	vm_op_ret,
	vm_op_noop,
	vm_op_noop,
	vm_op_noop,
	vm_op_noop,
	vm_op_emit,
	vm_op_key,
	vm_op_qkey
} ;

void vm_init(void)
{
	vm_base = (byte*)calloc(VM_MEMORY_SIZE, sizeof(byte));

	vm_top = VM_MEMORY_SIZE;
	vm_bottom = 0;

	vm_s0 = vm_top;
	vm_sp = vm_s0;

	vm_r0 = vm_s0 - VM_STACK_GAP;
	vm_rp = vm_r0;

	vm_state = VM_STATE_EXECUTE;
	vm_ip = vm_bottom;

	vm_debug = 0;
}

void vm_execute(void)
{
	char c;
	while(vm_state != VM_STATE_HAULT)
	{
		vm_op = ADDR_BYTE(vm_ip);

		if(vm_debug)
		{
			vm_debug_status();

			c = _getch();
			if(c == 'b')
				c = 'b';

		}

		if(vm_op & 0x80)
		{
			ADDR_WORD(vm_rp) = vm_ip + 2;
			vm_rp -= 2;
			vm_ip = ADDR_WORD(vm_ip) & 0x7fff;
		}
		else
		{	
			vm_ip++;

TRACE("%s=%d","vm_ip",vm_ip);

			(*opcode[vm_op])();
		}
	}
}

void vm_debug_status(void)
{
	word p;
	char s[128];
	char t[32];
	char *opName;

	*s=0;

	if(vm_sp == vm_s0){
		strcat(s,"empty");
	}
	else{
		p = vm_sp;

		while(p != vm_s0)
		{
			p += 2;
			sprintf(t,"0x%x ",ADDR_WORD(p));
			strcat(s,t);
		}
	}
	

	switch(vm_op)
	{
		case VM_OPCODE_NOOP:
			opName = "NOOP";
			break;

		case VM_OPCODE_DEBUG:
			opName = "DEBUG";
			break;

		case VM_OPCODE_HAULT:
			opName = "HAULT";
			break;

		case VM_OPCODE_DUP:
			opName = "DUP";
			break;

		case VM_OPCODE_SWAP:
			opName = "SWAP";
			break;

		case VM_OPCODE_OVER:
			opName = "OVER";
			break;

		case VM_OPCODE_ROT:
			opName = "ROT";
			break;

		case VM_OPCODE_DROP:
			opName = "DROP";
			break;

		case VM_OPCODE_RESET:
			opName = "RESET";
			break;

		case VM_OPCODE_TOR:
			opName = "TOR";
			break;

		case VM_OPCODE_RFROM:
			opName = "RFROM";
			break;

		case VM_OPCODE_RAT:
			opName = "RAT";
			break;

		case VM_OPCODE_LIT:
			opName = "LIT";
			break;

		case VM_OPCODE_ADD:
			opName = "ADD";
			break;

		case VM_OPCODE_SUB:
			opName = "SUB";
			break;

		case VM_OPCODE_MUL:
			opName = "MUL";
			break;

		case VM_OPCODE_DIV:
			opName = "DIV";
			break;

		case VM_OPCODE_MOD:
			opName = "MOD";
			break;

		case VM_OPCODE_AND:
			opName = "AND";
			break;

		case VM_OPCODE_OR:
			opName = "OR";
			break;

		case VM_OPCODE_XOR:
			opName = "XOR";
			break;

		case VM_OPCODE_NOT:
			opName = "NOT";
			break;

		case VM_OPCODE_EQUAL:
			opName = "EQUAL";
			break;

		case VM_OPCODE_FETCH:
			opName = "FETCH";
			break;

		case VM_OPCODE_LESS:
			opName = "LESS";
			break;

		case VM_OPCODE_GREATER:
			opName = "GREATER";
			break;

		case VM_OPCODE_CFETCH:
			opName = "CFETCH";
			break;

		case VM_OPCODE_STORE:
			opName = "STORE";
			break;

		case VM_OPCODE_CSTORE:
			opName = "CSTORE";
			break;

		case VM_OPCODE_BRANCH:
			opName = "BRANCH";
			break;

		case VM_OPCODE_0BRANCH:
			opName = "0BRANCH";
			break;

		case VM_OPCODE_JUMP:
			opName = "JUMP";
			break;

		case VM_OPCODE_CALL:
			opName = "CALL";
			break;

		case VM_OPCODE_RET:
			opName = "RET";
			break;

		case VM_OPCODE_EMIT:
			opName = "EMIT";
			break;
		case VM_OPCODE_KEY:
			opName = "KEY";
			break;

		case VM_OPCODE_QKEY:
			opName = "QKEY";
			break;

		default:
			opName = "?";
			break;

	}


	printf("vm_ip 0x%x ", vm_ip - 1);
	printf("vm_sp 0x%x ", vm_sp);
	printf("vm_rp 0x%x ", vm_rp);
	printf("vm_op 0x%x (%s) ", vm_op, opName);

	printf("stack [%s]\n", s);
}
