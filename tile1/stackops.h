/*
 *	Module : Stackops.h
 *	Author : Steven James
 *	Date : 20th January 1990
 *
 *	This module implements the seven main stack operations required by
 *	the forth engine, namely DROP DUP SWAP OVER ROT EMPTY for the parameter
 *	stack, and >R R> R J for the return stack.
 *
 *	Functions : -
 *	drop_op() dup_op() swap_op() over_op() rot_op()
 *	pushr_op() popr_op() r_op() j_op()
 *	empty_op()
 */

#define DROP_OP	100
#define DUP_OP	101
#define SWAP_OP	102
#define OVER_OP	103
#define ROT_OP	104
#define PUSHR_OP	105
#define POPR_OP	106
#define R_OP	107
#define J_OP	108
#define EMPTY_OP	109

/*
 *	Procedure to disguard the top item on the parameter stack.
 */
void drop_op()
{
#ifdef DEBUG
  printf("drop opcode\n") ;
#endif
  pop_ps () ;
}

/*
 *	Procedure to duplicate the top item on the parameter stack.
 */
void dup_op()
{
  unsigned short top ;
#ifdef DEBUG
  printf("dup opcode\n") ;
#endif
  top = pop_ps () ;
  push_ps ( top ) ;
  push_ps ( top ) ;
}

/*
 *	Procedure to swap the top two items on the parameter satck.
 */
void swap_op()
{
  unsigned short top , bottom ;
#ifdef DEBUG
  printf("swap opcode\n") ;
#endif
  top = pop_ps() ;
  bottom = pop_ps() ;
  push_ps( top ) ;
  push_ps( bottom ) ;
}

/*
 *	Procedure to copy the second item on the parameter stack to the top.
 */
void over_op()
{
  unsigned short top , bottom ;
#ifdef DEBUG
  printf("over opcode\n") ;
#endif
  top = pop_ps() ;
  bottom = pop_ps() ;
  push_ps( bottom ) ;
  push_ps( top ) ;
  push_ps( bottom ) ;
}

/*
 *	Procedure to move the third item on the parameter satck to the top.
 */
void rot_op()
{
  unsigned short top , middle , bottom ;
#ifdef DEBUG
  printf("rot opcode\n") ;
#endif
  top = pop_ps() ;
  middle = pop_ps () ;
  bottom = pop_ps() ;
  push_ps( middle ) ;
  push_ps( top )	;
  push_ps( bottom ) ;
}

/*
 *	Procedure to push the top item fron the parameter to the return stack.
 */
void pushr_op()
{
#ifdef DEBUG
  printf(">R opcode\n") ;
#endif
  push_rs ( pop_ps () ) ;
}

/*
 *	Procedure to push the top item from the return to the parameter stack.
 */
void popr_op()
{
#ifdef DEBUG
  printf("R> opcode\n") ;
#endif
  push_ps( pop_rs() ) ;
}

/*
 *	Procedure to push the top element on the return stack onto the top
 *	of the parameter stack as a 16 bit quantity, without disturbing the
 *	top of the return stack.
 */
void r_op()
{
  unsigned short r ;
#ifdef DEBUG
  printf("R opcode\n") ;
#endif
  r = pop_rs() ;
  push_rs( r ) ;
  push_ps( r ) ;
}

/*
 *	Procedure to push the third element on the return stack onto the top
 *	of the parameter stack as a 16 bit quantity, without disturbing the
 *	third element on the return stack.
 */
void j_op()
{
  unsigned short third ;
#ifdef DEBUG
  printf("J opcode\n") ;
#endif
  push_ps( pop_rs() ) ;
  push_ps( pop_rs() ) ;
  third = pop_rs() ;
  push_rs( third ) ;
  push_rs( pop_ps() ) ;
  push_rs( pop_ps() ) ;
  push_ps( third ) ;
}
 
/*
 *	Procedure to check if the parameter stack is empty, and return
 *	a 16 bit value to reflect the result.
 */
void empty_op()
{
#ifdef DEBUG
  printf("empty opcode\n") ;
#endif
  if ( empty_ps() )
    push_ps ( FTRUE ) ;
  else
    push_ps( FFALSE ) ;
}
