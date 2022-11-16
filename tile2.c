/*
 * tile2.c
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

#include "io.h"
#include "tile2.h"
#include "op_codes.h"
#include "virtual-machine.h"
#include "helper_macros.h"

#define INITIAL_TIB				0x20
#define INITIAL_DP				0x500

#define _DUP					compile_byte(VM_OPCODE_DUP);
#define _SWAP					compile_byte(VM_OPCODE_SWAP);
#define _ROT					compile_byte(VM_OPCODE_ROT);
#define _DROP					compile_byte(VM_OPCODE_DROP);
#define _OVER					compile_byte(VM_OPCODE_OVER);
#define _RESET					compile_byte(VM_OPCODE_RESET);
#define _TOR					compile_byte(VM_OPCODE_TOR);
#define _RFROM					compile_byte(VM_OPCODE_RFROM);
#define _RAT					compile_byte(VM_OPCODE_RAT);
#define _RET					compile_byte(VM_OPCODE_RET);
#define _CALL(n)				compile_call(n);
#define _SCALL(n)				compile_scall(n);
#define _ADD					compile_byte(VM_OPCODE_ADD);
#define _SUB					compile_byte(VM_OPCODE_SUB);
#define _MUL					compile_byte(VM_OPCODE_MUL);
#define _DIV					compile_byte(VM_OPCODE_DIV);
#define _MOD					compile_byte(VM_OPCODE_MOD);
#define _LIT(n)					compile_lit(n);
#define _AND					compile_byte(VM_OPCODE_AND);
#define _OR						compile_byte(VM_OPCODE_OR);
#define _XOR					compile_byte(VM_OPCODE_XOR);
#define _NOT					compile_byte(VM_OPCODE_NOT);
#define _EQUAL					compile_byte(VM_OPCODE_EQUAL);
#define _LESS					compile_byte(VM_OPCODE_LESS);
#define _GREATER				compile_byte(VM_OPCODE_GREATER);
#define _FETCH					compile_byte(VM_OPCODE_FETCH);
#define _CFETCH					compile_byte(VM_OPCODE_CFETCH);
#define _STORE					compile_byte(VM_OPCODE_STORE);
#define _CSTORE					compile_byte(VM_OPCODE_CSTORE);
#define _KEY					compile_byte(VM_OPCODE_KEY);
#define _DEBUG_INFO				compile_byte(VM_OPCODE_DEBUG);
#define _HAULT					compile_byte(VM_OPCODE_HAULT);

word dp;
word last;
word smart_label[8];

void compile_byte(byte b)
{
	ADDR_BYTE(dp) = b;
	dp++;
}

void compile_word(word w)
{
	ADDR_WORD(dp) = w;
	dp +=2;
}

void compile_lit(word w)
{
	compile_byte(VM_OPCODE_LIT);
	compile_word(w);
}

void compile_call(word w)
{
	compile_byte(VM_OPCODE_CALL);
	compile_word(w);
}

void compile_scall(word w)
{
	compile_word(w | 0x8000);
}

void compile_0branch(word w)
{
	compile_byte(VM_OPCODE_0BRANCH);
	compile_word(w);
}

void compile_branch(word w)
{
	compile_byte(VM_OPCODE_BRANCH);
	compile_word(w);
}

void compile_jump(word w)
{
	compile_byte(VM_OPCODE_JUMP);
	compile_word(w);
}

void smart_clear()
{	int i;
	for(i = 0; i < 8; i++)
		smart_label[i] = 0;
}

void smart_0branch(int n)
{	
	if(smart_label[n])
	{
		compile_byte(VM_OPCODE_0BRANCH);
		compile_word(-(dp+2 - smart_label[n]));
	}
	else
	{
		compile_byte(VM_OPCODE_0BRANCH);
		smart_label[n] = dp;
		compile_word(0);
	}
}

void smart_branch(int n)
{	
	if(smart_label[n])
	{
		compile_byte(VM_OPCODE_BRANCH);
		compile_word(-(dp+2 - smart_label[n]));
	}
	else
	{
		compile_byte(VM_OPCODE_BRANCH);
		smart_label[n] = dp;
		compile_word(0);
	}
}

void smart_mark(int n)
{
	smart_label[n] = dp;
}

void smart_resolve(int n)
{
	ADDR_WORD(smart_label[n]) = (dp - (smart_label[n] + 2));
}

void compile_header(char *s)
{
	int i;
	int n;

	word here;

	here = dp;
	n = strlen(s);

	compile_byte(n | 0x80);
	for(i = 0; i < n; i++)
		if(i + 1 < n)
			compile_byte(s[i]);
		else
			compile_byte(s[i] | 0x80);

	compile_word(last);
	last = here;

	smart_clear();
}

void build_dictionary()
{
	word label_plus_origin;
	word label_dp;
	word label_tib;
	word label_in;
	word label_state;
	word label_base;
	word label_current;
	word label_context;
	word label_width;
	word label_plus_store;
	word label_minus_store;
	word label_zero_equal;
	word label_here;
	word label_comma;
	word label_ccomma;
	word label_max;
	word label_min;
	word label_inline;
	word label_tibfrom;
	word label_tibplus;
	word label_bword;
	word label_word;
	word label_bfind;
	word label_nfa2lfa;
	word label_lfa2nfa;
	word label_lfa2cfa;
	word label_cfa2lfa;

	word label_qcr;
	word label_oneplus;
	word label_oneminus;
	word label_test;
	word label_scratch;

	dp = 0x0;
	last = 0x0;

	// Cold start vector
	compile_byte(VM_OPCODE_JUMP);
	compile_word(0x100);

	dp = 0x04;

	compile_word(INITIAL_DP);				// DP
	compile_word(0);						// STATE
	compile_word(INITIAL_TIB);				// TIB
	compile_word(0);						// IN
	compile_word(10);						// BASE
	compile_word(0);						// CURRENT
	compile_word(0);						// CONTEXT
	compile_word(0);						// WIDTH
	compile_word(0);
	compile_word(0);
	compile_word(0);
	compile_word(0);

	dp = 0x80;

	compile_header("dup");
	_DUP
	_RET

	compile_header("swap");
	_SWAP
	_RET

	compile_header("over");
	_OVER
	_RET

	compile_header("rot");
	_ROT
	_RET

	compile_header("drop");
	_DROP
	_RET

	compile_header("reset");
	_RESET
	_RET

	compile_header(">r");
	_TOR
	_RET

	compile_header("r>");
	_RFROM
	_RET

	compile_header("r@");
	_RAT
	_RET

	compile_header("+");
	_ADD
	_RET

	compile_header("-");
	_SUB
	_RET

	compile_header("1+");
label_oneplus = dp;
	_LIT(0x01)
	_ADD
	_RET

	compile_header("1-");
label_oneminus = dp;
	_LIT(0x01)
	_SUB
	_RET

	compile_header("u*");
	_MUL
	_RET

	compile_header("u/");
	_DIV
	_RET

	compile_header("mod");
	_MOD
	_RET

	compile_header("and");
	_AND
	_RET

	compile_header("or");
	_OR
	_RET

	compile_header("xor");
	_XOR
	_RET

	compile_header("not");
	_NOT
	_RET

	compile_header("=");
	_EQUAL
	_RET

	compile_header(">");
	_GREATER
	_RET

	compile_header("<");
	_LESS
	_RET

	compile_header("@");
	_FETCH
	_RET

	compile_header("c@");
	_CFETCH
	_RET

	compile_header("!");
	_STORE
	_RET

	compile_header("c!");
	_CSTORE
	_RET

	compile_header("(emit)");
	compile_byte(VM_OPCODE_EMIT);
	_RET

	compile_header("(key)");
	compile_byte(VM_OPCODE_KEY);
	_RET

	compile_header("(?key)");
	compile_byte(VM_OPCODE_QKEY);
	_RET

	compile_header("+ORIGIN");
label_plus_origin = dp;
	_LIT(0x04);
	_ADD
	_RET

	compile_header("DP");
label_dp = dp;
	_LIT(0x0)
	_CALL (label_plus_origin)
	_RET

	compile_header("STATE");
label_state = dp;
	compile_lit(0x2);
	compile_call(label_plus_origin);
	compile_byte(VM_OPCODE_RET);

	compile_header("TIB");
label_tib = dp;
	_LIT(0x4);
	_CALL(label_plus_origin);
	_RET

	compile_header("IN");
label_in = dp;
	_LIT(0x6);
	_CALL(label_plus_origin);
	_RET

	compile_header("BASE");
label_base = dp;
	_LIT(0x8);
	_CALL(label_plus_origin);
	_RET

	compile_header("CURRENT");
label_current = dp;
	_LIT(0x0a);
	_CALL(label_plus_origin);
	_RET

	compile_header("CONTEXT");
label_context = dp;
	_LIT(0x0c);
	_CALL(label_plus_origin);
	_RET

	compile_header("+!");
label_plus_store = dp;
	_DUP
	_FETCH
	_ROT
	_ADD
	_SWAP
	_STORE
	_RET

	compile_header("-!");
label_minus_store = dp;
	_DUP
	_FETCH
	_ROT
	_SUB
	_SWAP
	_STORE
	_RET

	compile_header("0=");
label_zero_equal = dp;
	_LIT(0x0)
	_EQUAL
	_RET

	compile_header("here");
label_here = dp;
	_CALL(label_dp);
	_FETCH
	_RET

	compile_header(",");
label_comma = dp;
	_CALL(label_here);
	_STORE
	_LIT(0x02);
	_CALL(label_dp);
	_CALL(label_plus_store);
	_RET

	compile_header("c,");
label_ccomma = dp;
	_CALL(label_here);
	_CSTORE
	_LIT(0x01);
	_CALL(label_dp);
	_CALL(label_plus_store);
	_RET

	compile_header("max");
label_max = dp;
	_OVER
	_OVER
	_GREATER
	smart_0branch(1);
	_SWAP
	smart_resolve(1);
	_DROP
	_RET

	compile_header("min");
label_min = dp;
	_OVER
	_OVER
	_LESS
	smart_0branch(1);
	_SWAP
	smart_resolve(1);
	_DROP
	_RET

	compile_header("?cr");
label_qcr = dp;
	_LIT(0x0d)
	_EQUAL
	_RET

	compile_header("inline");
label_inline = dp;
	_CALL(label_tib)
	_FETCH
	smart_mark(2);
	_KEY
	_DUP
	compile_call(label_qcr);
	smart_0branch(1);
	_DROP
	_LIT(0x0)
	_SWAP
	_CSTORE
	_LIT(0x0)
	_CALL(label_in)
	_STORE
	_RET
	smart_resolve(1);
	_OVER
	_CSTORE
	_LIT(0x01)
	_ADD
	smart_branch(2);

	compile_header("tib>");
label_tibfrom = dp;
	_CALL(label_tib)
	_FETCH
	_CALL(label_in)
	_FETCH
	_ADD
	_RET

	compile_header("tib+");
label_tibplus = dp;
	_LIT(0x1)
	_CALL(label_in)
	_CALL(label_plus_store)
	_RET

	compile_header("(word)");
label_bword = dp;
	smart_mark(3);
	_CALL(label_tibfrom)
	_CFETCH
	_DUP
	smart_0branch(1);
	_OVER
	_EQUAL
	smart_0branch(2);
	_CALL(label_tibplus)
	smart_branch(3);

	smart_resolve(1);
	smart_resolve(2);
	_DROP
	_RET
	
	compile_header("word");
label_word = dp;
	_DUP					// ( bl -- bl bl )
	_TOR
	_CALL(label_bword)		// ( bl -- )
	//_DEBUG_INFO
	_CALL(label_here)       // ( -- h )
	_DUP					// ( -- h h )
	_LIT(0x0)				// ( h h -- 0 h h )
	_OVER					// ( 0 h h -- h 0 h h )
	_CSTORE					// ( h 0 h h  -- h h )	
	smart_mark(3);
	_CALL(label_oneplus)	// ( h h -- h' h )
	_CALL(label_tibfrom)	// ( h' h -- t h' h )
	_CFETCH					// ( t h' h  -- t@ h' h )
	_DUP					// ( t@ h' h -- t@ t@ h' h )
	smart_0branch(1);
	_DUP					// ( t@ h' h -- t@ t@ h' h )
	_RAT					// ( t@ t@ h' h -- bl t@ t@ h' h )
	_EQUAL					// ( bl t@ t@ h' h -- f t@ h' h )	
	_NOT					
	smart_0branch(2);
	_OVER					// (t@ h' h -- h' t@ h' h )
	_CSTORE					// ( h' t@ h' h -- h' h )
	_CALL(label_tibplus)
	smart_branch(3);

	smart_resolve(1);
	smart_resolve(2);
	//_DEBUG_INFO
	_DROP					// ( t@ h' h -- h' h)
	_OVER					// ( h' h -- h h' h) 
	_CALL(label_oneplus)
	_SUB					// ( h h' h -- n h )
	_SWAP					// ( n h -- h n )
	_CSTORE
	_RFROM;
	_DROP
	_RET

	compile_header("lfa>cfa");
label_lfa2cfa = dp;
	_LIT(2)
	_ADD
	_RET

	compile_header("cfa>lfa");
label_lfa2cfa = dp;
	_LIT(2)
	_SUB
	_RET

	compile_header("lfa>nfa");
label_lfa2nfa = dp;
	_CALL(label_oneminus)
	smart_mark(1);
	_CALL(label_oneminus)
	_DUP
	_CFETCH
	_LIT(0x80)
	_AND
	_LIT(0x80)
	_EQUAL
	smart_0branch(1);
	_RET

	compile_header("nfa>lfa");
label_nfa2lfa = dp;
	smart_mark(1);
	_CALL(label_oneplus)
	_DUP
	_CFETCH
	_LIT(0x80)
	_AND
	_LIT(0x80)
	_EQUAL
	smart_0branch(1);
	_CALL(label_oneplus)
	_RET

	smart_clear();
label_scratch = dp;
	_OVER		// ( nfa a -- nfa a nfa )
	_OVER		// ( nfa a -- nfa a nfa a )
	_CFETCH		// ( nfa a nfa a - nfa@ a nfa a )
	_LIT(0x7f)
	_AND
	_SWAP		// ( nfa@ a nfa a -- a nfa@ nfa a )
	_CFETCH		// ( a nfa@ nfa a -- a@ nfa@ nfa a )
	_EQUAL		// ( a@ nfa@ nfa a -- f nfa a)
	smart_0branch(1);
	smart_mark(2);	
	_CALL(label_oneplus);	// ( nfa a -- nfa' a )
	_SWAP		// ( nfa' a -- a nfa' )				
	_CALL(label_oneplus); // ( a nfa' -- a' nfa')
	_SWAP		// ( a' nfa' -- nfa' a' )				
	_OVER		// ( nfa' a' -- a' nfa' a' ) 
	_CFETCH		// ( a' nfa' a' -- a'@ nfa' a' )
	_DUP		// ( a'@ nfa' a' -- a'@ a'@ nfa' a' )
	smart_0branch(3);
	_OVER		// ( a'@ nfa' a'  -- nfa' a'@ nfa' a' )
	_CFETCH		// ( nfa' a'@ nfa' a' -- nfa'@ a'@ nfa' a' )
	_LIT(0x7f)
	_AND		
	_EQUAL		// ( nfa'@ a'@ nfa' a' -- f nfa' a')
	_NOT
	smart_0branch(2);
	smart_resolve(1);
	_DROP
	_DROP
	_LIT(0x0)
	_RET
	smart_resolve(3);
	_DROP
	_SWAP
	_DROP
	_SWAP
	_DROP
	_LIT(2)
	_ADD
	_LIT(0xffff)
	_RET

	compile_header("(find)");
label_bfind = dp;
	smart_mark(2);
	_OVER
	_OVER
	_CALL(label_scratch)
	smart_0branch(1);
	_LIT(0xffff)
	_RET
	smart_resolve(1);
	
	_CALL(label_nfa2lfa)
	_FETCH
	_DUP
	_CALL(label_zero_equal)
	smart_0branch(2);
	_DROP
	_DROP
	_LIT(0x0)
	_RET
	
label_test = dp;

	compile_call(label_inline);
	compile_lit(32);
	compile_call(label_word);
	compile_call(label_here);
	_LIT(last)
	_CALL(label_bfind)
	_DEBUG_INFO
	_HAULT


//compile_call(label_here);
	compile_lit(2);
	compile_call(label_comma);	
	compile_lit(1);
	compile_call(label_comma);
	compile_call(label_here);

	//compile_byte(VM_OPCODE_QKEY);
	compile_byte(VM_OPCODE_HAULT);

	vm_ip = label_test;
	vm_execute();

}

int main(int argc, char *argv[])
{
//	byte *dp;

	vm_init();
	build_dictionary();	

/*
	dp = vm_base;

	*dp++ = VM_OPCODE_KEYQ;
	*dp++ = VM_OPCODE_0BRANCH;
	*(word*)dp = -4;
	dp +=2;
	*dp++ = VM_OPCODE_KEY;
	*dp++ = VM_OPCODE_EMIT;
	*dp++ = VM_OPCODE_HAULT;
*/
	

	return 0;
}
