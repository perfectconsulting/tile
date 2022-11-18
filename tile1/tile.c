/*
 *-------------------------------------------------------------------
 *
 *      T . I . L . E
 ★
 *	Threaded Interpretive Language Enviroment
 *
 *
 *	1989/90 Senior Honours Major Project By Steven James
 *
 *	For The Computational Science Department
 *
 *	Of
 *
 *	St. Andrews University
 *
 *
 *-------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include "stddefs.h"
#include "forward.h"
#include "forthconst.h"
#include "user.h"
#include "trapops.h"
#include "memory.h"
#include "fstacks.h"
#include "fstring.h"
#include "innerops.h"
#include "stackops.h"
#include "memoryops.h"
#include "mathsops.h"
#include "logicops.h"
#include "dataops.h"
#include "branchops.h"
#include "ioops.h"
#include "dictops.h"
#include "defineops.h"
#include "inner.h"
#include "dictionary.h"

#define VERSION	1.15

/*
 *	Procedure to display the initial startup message.
 */
void legand()
{
  printf( "TILE - Threaded Interpretive Language Environment.\n" ) ;
  printf( "Version %1.2f (c) University of St. Andrews.\n",VERSION ) ;
}

/*
 *	Procedure to report a context error for the last dictionary search.
 */
void context_error()
{
  drop_op() ;
  printf("'%s' is not in the context vocabulary.\n" , dp_string() ) ;
  forth_abort() ;
}

/*
 *	Procedure to compile the 16 bit value on top of the parameter stack
 *	into the free dictionary as a literal.
 */
void compile_lit ()
{
  push_ps( lit_cfa ) ;
  put_word( get_word( DP ) , pop_ps() ) ;
  put_word( get_word( DP ) + 2 , pop_ps() ) ;
  put_word( DP , get_word( DP ) + 4 ) ;
}

/*
 *	Procedure to take a 16 bit code field address from the parameter stack
 *	and return true if the cfa pointer to an immediate word.
 */
int is_immediate( nfa )
     unsigned short nfa ;
{
  if( get_byte( nfa ) & IMMEDIATE_BIT )
    return( TRUE ) ;
  else
    return( FALSE ) ;
}

/*
 *	Procedure to take a 16 bit code filed address from the parameter stack
 *	and return true is it is executable.
 */
int executable( nfa )
     unsigned short nfa ;
{
  if( get_word( STATE ) == FFALSE )
    {
      return( TRUE ) ;
    }
  else
    return( is_immediate( nfa ) ) ;
}

/*
 *	Procedure to search the dictionary chain, starting from the vocabulary
 *	specified by the CONTEXT, for the entry that matches the counted string
 *	pointed to by DP. The pointer to the counted string is always returned
 *	together with a 16 bit truth value of false ( 0 ) if the search fails,
 *	or the name filed address of the matching dictionary word, and a 16 bit
 *	truth value of true ( -1 ) if the search is successful.
 */
void chain_find()
{
  push_ps( get_word(DP));
  push_ps( get_word( get_word( CONTEXT ) ) ) ;
  find_op() ;
  if( pop_ps() == FFALSE )
    {
      drop_op() ;
      push_ps( get_word( DP ) ) ;
      push_ps( get_word( get_word( get_word( CONTEXT ) - 2 ) ) ) ;
      find_op() ;
    }
  else
    push_ps( FTRUE ) ;
}

/*
 *	Procedure to compile the 16 bit quantity on the top of the parameter
 *	stack into the free dictionary.
 */
void compile_word()
{
  put_word( get_word( DP ) , pop_ps() ) ;
  put_word( DP , get_word( DP ) + 2 ) ;
}

main()
{
  unsigned short converted ;
  reset_ps() ;
  reset_rs() ;
  reset_trap () ;
  reset_exit() ;
  claim_memory() ;
  configure_variables() ;
  configure_term() ;
  configure_strm() ;
  build_dictionary() ;
  legand() ;
  do
    {
      if( terminal() )
	printf( "ok\n" ) ;
      inline_op() ;
      push_ps ( SPACE ) ;
      word_op() ;
      while( get_byte( get_word( DP ) )	!= NULL )
	{
	  chain_find() ;
	  if( pop_ps() == FTRUE )
	    {
	      nfa = pop_ps() ;
	      drop_op() ;
	      push_ps ( nfa + get_word( WIDTH ) + 3 ) ;
	      if( executable ( nfa ) )
		inner( get_word( INNER ) ) ;
	      else
		compile_word() ;
	    }
	  else
	    {
	      drop_op() ;
	      number_op() ;
	      converted = pop_ps() ;
	      if( converted == FFALSE && !trapped() )
		context_error() ;
	      else
		if( get_word( STATE ) == FTRUE )
		  {
		    if( converted == 2 )
		      {
			swap_op() ;
			compile_lit() ;
		      }
		    compile_lit() ;
		  }
	    }
	  reset_trap() ;
	  push_ps( SPACE ) ;
	  word_op() ;
	}
    }
  while( !finished() ) ;
  free_memory () ;
  unconfigure_term() ;
}
