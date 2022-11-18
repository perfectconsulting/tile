/*
 *	Module : defineops.h
 *	Author : Steven James
 *	Date : 19th February 1990
 *
 *	This module implements the five defining constructs required by the
 *	forth engine, namley <BUILDS DOES> CREATE : ; .
 *
 *	Functions
 *	builds_op() does_op() create_op() define_op() end_op()
 */

#define BUILDS_OP	900
#define DOES_OP	901
#define CREATE_OP	902
#define DEFINE_OP	903
#define END_OP	904

/*
 *	Procedure to push the the current content of the word address register
 *	onto the top of th parameter stack as a 16 bit quantity.
 */
void builds_op()
{
#ifdef DEBUG
  printf("builds opcode\n") ;
#endif
  push_ps ( wa ) ;
}

/*
 *	Procedure to push the contents of the instruction register onto the top
 *	of the return stack, set in instruction register to the 16 bit quantity
 *	pointed to by the contents of the word address register and push the
 *	nincremented contents of the word address register onto the parameter
 *	stack as a 16 bit quantity.
 */
void does_op()
{
#ifdef DEBUG
  printf("does opcode\n") ;
#endif
  push_rs( i ) ;
  i = get_word( wa ) ;
  push_ps( wa + 2 ) ;
}

/*
 *	Procedure to construct a header ( ie. the name and link fields ) for the
 *	the next space delimited string in the text input buffer, and report any
 *	attempts to redefine an existing word.
 */
void mkheader()
{
  push_ps( get_word( get_word( CURRENT ) ) ) ;
  push_ps( SPACE ) ;
  word_op() ;
  push_ps( get_word( DP ) ) ;
  push_ps( get_word( get_word( CONTEXT ) ) ) ;
  find_op() ;
  if ( pop_ps () == FTRUE )
    {
      printf("'%s' has been redefined.\n" , dp_string() ) ;
      drop_op() ;
    }
  drop_op() ;
  put_word( get_word( CURRENT ) , get_word( DP ) ) ;
  put_word( DP , get_word( DP ) + get_word( WIDTH ) + 1 ) ;
  put_word( get_word( DP ) , pop_ps() ) ;
  put_word( DP , get_word( DP ) + 2 ) ;
}

/*
 *	Procedure to construct a word header from the space delimited string in
 *	the text input buffer, with the code field address pointing to the
 *	body of the word.
 */
void create_op()
{
#ifdef DEBUG
  printf("create opcode\n") ;
#endif
  mkheader() ;
  put_word( get_word( DP ) , get_word( DP ) + 2 ) ;
  put_word( DP , get_word( DP ) + 2 ) ;
}

/*
 *	Procedure to construct a colon definition from the space delimited string
 *	in the text input buffer.
 */
void define_op()
{
#ifdef DEBUG
  printf("define opcode\n") ;
#endif
  put_word( CONTEXT , get_word( CURRENT ) ) ;
  mkheader() ;
  put_word( get_word( DP ) , colon_cfa ) ;
  put_word( DP , get_word( DP ) + 2 ) ;
  put_word( STATE , FTRUE ) ;
}

/*
 *	Procedure to compile a semi colon and terminate compilation of a colon
 *	definition by resetting the STATE user variable.
 */
void end_op()
{
#ifdef DEBUG
  printf("end opcode\n") ;
#endif
  push_ps( semi_cfa ) ;
  put_word( get_word( DP ) , pop_ps() ) ;
  put_word( DP , get_word( DP ) + 2 ) ;
  put_word( STATE , FFALSE ) ;
}
