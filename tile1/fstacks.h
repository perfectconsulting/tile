/*
 *	Module : fstacks.h
 *	Author : Steven James
 *	Date : 18th Jaunary 1990
 *
 *	This module implements the two main stacks used by the forth engine,
 *	namely the parameter and return stacks, each of which has associated
 *	push, pop and empty functions.
 *
 *	Functions
 *	push_ps(ushort) push_rs(ushort)	ushort pop_j?s() ushort pop_rs()
 *	bool empty_ps() bool empty_rs()
 *	reset_ps() reset_rs()
 */

#define RSTKSIZE	10000
#define PSTKSIZE	1000

unsigned short rstk[ RSTKSIZE ] ;
unsigned short pstk [ PSTKSIZE ] ;

int rs , ps ;

/*
 *	Procedure to test if the parameter stack is empty and return a boolean
 *	integer representing the result of the test ( 0 = false , -1 = true )
 */
int empty_ps ()
{
  return( ps == 0 ) ;
}

/*
 *	Procedure to test if the parameter stack is empty and return a boolean
 *	integer representing the result of the test ( 0 = false , -1 = true )
 */
int empty_rs ()
{
  return( rs == 0 ) ;
}

/*
 *	procedure to push a 16 bit value onto the parameter stack.
 */
void push_ps( n )
     unsigned short n ;
{
  if( ! trapped() )
    if ( ps == PSTKSIZE )
      {
        if(terminal())
        {
	        printf( "Parameter stack overflow.\n" ) ;
        }
        else
        {
          printf( "Parameter stack overflow. #%d\n", file_ptr->line ) ;
        }
	forth_abort() ;
      }
    else
      pstk[ ps++ ] = n ;
}

/*
 *	Procedure to push a 16 bit value onto the return stack.
 */
void push_rs( n )
     unsigned short n ;
{
  if( ! trapped() )
    if( rs == RSTKSIZE )
      {
	printf( "Return stack overflow.\n" ) ;
	forth_abort() ;
      }
    else
      rstk[ rs++ ] = n ;
}

/*
 *	Procedure to pop a 16 bit value from the parameter stack. The routine
 *	does not trap parameter stack underflow, and will return a zero under
 *	such circumstances.
 */
unsigned short pop_ps()
{
  unsigned short n = 0 ;
  if( empty_ps() )
    {
      if( ! trapped() )
	{
        if(terminal())
        {
	        printf( "Parameter stack underflow.\n" ) ;
        }
        else
        {
          printf( "Parameter stack underflow. #%d\n", file_ptr->line ) ;
        }
	  forth_abort() ;
	}
    }
  else
    n = pstk[ --ps ] ;
  return( n ) ;
}

/*
 *	Procedure to pop a 16 bit value from the return stack. The routine does
 *	not trap return stack underflow, and will return a zero under such
 *	circumstances.
 */
unsigned short pop_rs()
{
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
    n = rstk[--rs ] ;
  return( n )	;
}

/*
 *	Procedure to empty the parameter stack.
 */
void reset_ps()
{
  ps = 0 ;
}

/*
 *	Procedure to empty the parameter stack.
 */
void reset_rs()
{
  rs = 0 ;
}
