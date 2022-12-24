/*
 *	Module : Mathsops.h
 *	Author : Steven James
 *	Date : 24th January 1990
 *
 *	This module implements the seven main arithmetic operations required by
 *	the forth engine, namely + - * / U* U/ MINUS.
 *
 *	Functions :-
 *	add op () daddop_ () umul_op () udiv_op () minus_op () dminus_op (
 */

#define ADD_OP	300
#define DADD_OP	301
#define UMUL_OP	302
#define UDIV_OP	303
#define MINUS_OP	304
#define DMINUS_OP	305

/*
 *	Procedure to add the top two 16 bit quantities on the parameter stack
 *	together producing a 16 bit result.
 */
void add_op()
{
  unsigned short top , bottom ;
#ifdef DEBUG
  printf("add opcode\n");
#endif
  top = pop_ps() ;
  bottom = pop_ps() ;
  push_ps ( bottom + top ) ;
}

/*
 *	Procedure to add the top two 32 bit quantities on the parameter stack
 *	together producing a 32 bit result with the most significant word
 *	first, and the least significat word second.
 */
void dadd_op()
{
  unsigned int lsword , msword , top , bottom ;
#ifdef DEBUG
  printf("dadd opcode\n" );
#endif
  msword = ( int ) pop_ps()	;
  lsword = ( int ) pop_ps()	;
  top = ( msword << 16 ) + lsword ;
  msword = ( int ) pop_ps ()	;
  lsword = ( int ) pop_ps()	;
  bottom = ( msword << 16 ) + lsword ;
  top += bottom ;
  push_ps( ( unsigned short ) ( top & 0xffff ) ) ;
  push_ps( ( unsigned short ) ( top >> 16 ) ) ;
}

/*
 *	Procedure to multiply the top two 32 bit quantities on the parameter
 *	stack together producing a 32 bit result with the most significant
 *	word first, and the least significat word second.
 */
void umul_op()
{
  unsigned short top , bottom ;
  unsigned long result ;
#ifdef DEBUG
  printf("umul opcode\n");
#endif
  top = pop_ps() ;
  bottom = pop_ps() ;
  result = top * bottom ;
  push_ps( ( unsigned short ) result & 0xffff ) ;
  push_ps( ( unsigned short ) ( result >> 16 ) & 0xffff ) ;
}

/*
 *	Procedure to divide the top 16 bit quantitie on the parameter stack by
 *	the bottom 32 bit quantity producing a 32 bit result with the most
 *	significant word first, and the least significat word second.
 */
void udiv_op()
{
  unsigned int top , msword , lsword , bottom ;
#ifdef DEBUG
  printf("udiv opcode\n") ;
#endif
  top = ( int ) pop_ps() ;
  if ( top == 0 )
    {
      printf("Arithmetic error - attempt to divide by zero.\n" ) ;
      forth_abort() ;
    }
  else
    {
      msword =	( int ) pop_ps() ;
      lsword =	( int ) pop_ps() ;
      bottom = ( msword << 16 ) + lsword ;
      push_ps(	( unsigned short ) ( bottom % top ) ) ;
      push_ps(	( unsigned short ) ( bottom / top ) ) ;
    }
}

/*
 *	Procedure to negate the top 16 bit quantity on the parameter stack
 *	producing a 16 bit result.
 */
void minus_op()
{
  unsigned short top ;
#ifdef DEBUG
  printf("minus opcode\n") ;
#endif
  top = abs ( ( int ) pop_ps() ) ;
  push_ps ( ( unsigned short ) -top ) ;
}

/*
 *	Procedure to negate the top 32 bit quantity on the parameter stack
 *	producing a 32 bit result with the most significant word first, and
 *	the least significat word second.
 */
void dminus_op ()
{
  unsigned short top , bottom ;
#ifdef DEBUG
  printf("dminus opcode\n" ) ;
#endif
  top = abs( ( int ) pop_ps() ) ;
  bottom = abs( ( int ) pop_ps() ) ;
  push_ps( -bottom ) ;
  if( bottom != 0 && top == 0 )
    push_ps( -1 ) ;
  else
    if ( top == 0xffff )
      push_ps( 0 ) ;
    else
      push_ps( -top ) ;
}
