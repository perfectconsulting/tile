/*
 *	Module : dataops.h
 *	Author : Steven James
 *	Date : 26th January 1990
 *
 *	This module implements the two data constructs required by the forth
 *	engine, namely LIT and CONST.
 *
 *	Functions
 *	lit	op() const op()
 */

#define LIT_OP	500
#define CONST_OP	501

/*
 *	Procedure to push the literal pointed to by the instruction register
 *	onto the parameter stack, and increment the instruction register.
 */
void lit_op()
{
#ifdef DEBUG
  printf("lit opcode\n") ;
#endif
  push_ps( get_word( i ) ) ;
  i += 2	;
}

/*
 *	Procedure to push the constant pointed to be the word address register
 *	onto the parameter stack.
 */
void const_op()
{
#ifdef DEBUG
  printf("const opcode\n") ;
#endif
  push_ps ( get_word( wa ) ) ;
}
