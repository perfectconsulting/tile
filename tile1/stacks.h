/*
 *	Module : Stacks.h
 *	Author : Steven James
 *	Date : 18th Jaunary 1990
 *
 *	This module implements the two main stacks used by the forth engine,
 *	namely the parameter and return stacks, each of which has associated
 *	push, pop and empty functions.
 *
 *	Functions
 *	push_j>s (ushort) push_rs(ushort)	ushort pop_ps() ushort pop_rs()
 *	bool empty_ps() bool empty_rs()
 *	reset_ps() reset_rs()
 */

struct stk_elmt
{
  unsigned short value ;
  struct stk_elmt *link ;
} ;

struct stk_elmt *ps ;
struct stk_elmt *rs ;

/*
 *	Procedure to test if the parameter stack is empty and return a boolean
 *	integer representing the result of the test ( 0 = false , -1 = true )
 */
int empty__ps ()
{
  return(ps == NULL) ;
}

/*
 *	Procedure to test if the parameter stack is empty and return a boolean
 *	integer representing the result of the test ( 0 = false , -1 = true )
 */
int empty_rs()
{
  return(rs == NULL) ;
}

/*
 *	procedure to push a 16 bit value onto the parameter stack.
 */
void push_ps( n )
     unsigned short n ;
{
  if( ! trapped() )
    {
      struct stk_elmt *new_ps ;
      new_ps = (struct stk_elmt *)
	malloc( sizeof( struct stk_elmt ) ) ;
      new_ps->value = n ;
      new_ps->link = ps ;
      ps = new_ps ;
    }
}

/*
 *	Procedure to push a 16 bit value onto the return stack.
 */
void push_rs( n )
     unsigned short n ;
{
  if( ! trapped() )
    {
      struct stk_elmt *new_rs ;
      new_rs = (struct stk_elmt *)
	malloc ( sizeof( struct stk_elmt ) ) ;
      new_rs->value = n ;
      new_rs->link = rs ;
      rs = new_rs ;
    }
}

/*
 *	Procedure to pop a 16 bit value from the parameter stack. The routine
 *	does not trap parameter stack underflow, and will return a zero under
 *	such circumstances.
 */
unsigned short pop_ps()
{
  struct stk_elmt *new_ps ;
  unsigned short n = 0 ;
  if ( empty_ps() )
    {
      if( ! trapped() )
	{
	  printf( "Parameter stack underflow.\n" ) ;
	  forth_abort() ;
	}
    }
  else
    {
      new_ps = ps->link ;
      n = ps->value ;
      free( ps ) ;
      ps = new_ps ;
    }
  return( n ) ;
}

/*
 *	Procedure to pop a 16 bit value from the return stack. The routine does
 *	not trap return stack underflow, and will return a zero under such
 *	circumstances.
 */
unsigned short pop_rs()
{
  struct stk_elmt *new_rs ;
  unsigned short n = 0 ;
  if( empty_rs() )
    {
      if ( ! trapped () )
	{
	  printf( "Return stack underflow.\n" );
	  forth_abort() ;
	}
    }
  else
    {
      new_rs = rs->link ;
      n = rs->value ;
      free( rs ) ;
      rs = new_rs ;
    }
  return( n ) ;
}

/*
 *	Procedure to empty the parameter stack.
 */
void reset_ps()
{
  while ( !empty_ps() )
    pop_ps() ;
}

/*
 *	Procedure to empty the parameter stack.
 */
void reset_rs()
{
  while( !empty_rs() )
    pop_rs() ;
}
