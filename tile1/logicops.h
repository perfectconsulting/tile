/*
 *	Module : Logicops.h
 *	Author : Steven James
 *	Date : 25th January 1990
 *
 *	This module implements the seven main logic operations required by the
 *	forth engine, namely AND OR XOR NOT = > < .
 *
 *	Functions
 *	and_op() or_op() xor_op() not_op() equal_op()
 *	greater_op() less_op()
 */

#define AND_OP	400
#define OR_OP	401
#define XOR_OP	402
#define NOT_OP	403
#define EQUAL_OP	404
#define GREATER_OP	405
#define LESS_OP	406

/*
 *	Procedure to logical AND the top two 16 bit values on the paramter stack
 *	together to produce a 16 bit result.
 */
void and_op()
{
#ifdef DEBUG
  printf("and opcode\n");
#endif
  push_ps ( pop_ps() & pop_ps() ) ;
}

/*
 *	Procedure to logical OR the top two 16 bit values on the parameter stack
 *	together to produce a 16 bit result.
 */
void or_op()
{
#ifdef DEBUG
  printf("or opcode\n");
#endif
  push_ps ( pop_ps () | pop_ps () ) ;
}
 
/*
 *	Procedure to logical XOR the top two 16 bit values on the parameter stack
 *	together to produce a 16 bit result.
 */
void xor_op()
{
#ifdef DEBUG
  printf("xor opcode\n") ;
#endif
  push_ps( pop_ps() ^ pop_ps() ) ;
}
 
/*
 *	Procedure to logical NOT the top 16 bit value on the parameter stack
 *	to produce a 16 bit result.
 */
void not_op()
{
#ifdef DEBUG
  printf("not opcode\n") ;
#endif
  push_ps ( ~ pop_ps () ) ;
}
/*
 *	Procedure to test for equality between the top two 16 bit values on the
 *	parameter stack, and return a truth value to reflect the result.
 */
void equal_op()
{
#ifdef DEBUG
  printf("equal opcode\n") ;
#endif
  if( pop_ps() == pop_ps() )
    push_ps( FTRUE ) ;
  else
    push_ps ( FFALSE ) ;
}
 
/*
 *	Procedure to test two 16 bit quantities on the parameter stack, and
 *	return a 16 bit result of true ( -1 ) if the top stack element is
 *	greater than the second, otherwise return false ( 0 ).
 */
void greater_op()
{
  short top , bottom ;
#ifdef DEBUG
  printf("> opcode\n") ;
#endif
  top = pop_ps() ;
  bottom = pop_ps() ;
  if( bottom > top )
    push_ps ( FTRUE ) ;
  else
    push_ps( FFALSE ) ;
}
 
/*
 *	Procedure to test two 16 bit quantities on the parameter stack, and
 *	return a 16 bit result of true ( -1 ) if the top stack element is
 *	less than the second, otherwise return false ( 0 ) .
 */
void less_op()
{
  short top , bottom ;
#ifdef DEBUG
  printf("< opcode\n" ) ;
#endif
  top = pop_ps() ;
  bottom = pop_ps() ;
  if ( bottom < top )
    push_ps ( FTRUE ) ;
  else
    push_ps ( FFALSE ) ;
}
