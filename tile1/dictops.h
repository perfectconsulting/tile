/*
 *	Module : dictops.h
 *	Author : Steven James
 *	Date : 10th February 1990
 *
 *	This module implements the five dictionary constructs required by the
 *	forth engine, namely WORD FIND NUMBER.
 *
 *	Functions
 *	word_op() find_op() number_op()
 */

#define WORD_OP	800
#define FIND_OP	801
#define NUMBER_OP	802

/*
 *	Procedure to copy a sequence of bytes, delimited by the value specified
 *	on top of the parameter stack, from the current position in the text
 *	input buffer to the top of the free dictionay as a counted string.
 *	The IN offset within the text input buffer is advanced to point the
 *	position directly after the delimiter specified.
 */
void word_op()
{
  unsigned short dp , tib , in , separator , count ;
#ifdef DEBUG
  printf("word opcode\n");
#endif
  dp = get_word( DP ) ;
  tib = get_word( TIB ) ;
  in = get_word( IN ) ;
  count = 0 ;
  separator = pop_ps() ;
  if ( isspace( separator ) )
    while( isspace( get_byte( tib + in ) ) )
      in++ ;
  while( get_byte( tib + in + count ) != separator &&
	 get_byte( tib + in + count ) != TILENULL )
    count++ ;
  put_byte( dp , count ) ;
  dp++ ;
  while( count != 0 )
    {
      put_byte( dp , get_byte( tib + in ) ) ;
      dp++ ;
      in++ ;
      count-- ;
    }
  put_word( IN , in + 1 ) ;
}

/*
 *	Procedure to search the dictionary, starting from the vocabulary
 *	specified by a 16 bit quantity on the top of the parameter stack, for
 *	the entry that matches the counted string pointed to by the second 16 bit
 *	quantity on the parameter stack. The pointer to the counted string is
 *	always returned together with a 16 bit truth value of false ( 0 ) if the
 *	search fails, or the name filed address of the matching dictionary word,
 *	and a 16 bit truth value of true ( -1 ) if the search is successful.
 */
void find_op()
{
  unsigned short width , count , cstring , lfa , nfa , offset ;
#ifdef DEBUG
  printf("find opcode\n") ;
#endif
  nfa = pop_ps() ;
  cstring = pop_ps() ;
  width = get_word( WIDTH ) ;
  do
    {
      lfa = nfa ;
      offset = cstring ;
      count = get_byte( cstring ) ;
      while( ( get_byte( nfa )	& LENGTH_MASK ) == count &&
	     !( get_byte( nfa ) & HIDDEN_BIT ) )
	{
	  if ( count > width )
	    count = width ;
	  do
	    {
	      nfa++ ;
	      offset++ ;
	      count-- ;
	    }
	  while( get_byte( nfa ) == get_byte( offset )
		 && count != 0 ) ;
	}
      if( count == 0 && get_byte( nfa ) == get_byte( offset ) )
	nfa = lfa ;
      else
	nfa = get_word( lfa + width + 1 ) ;
    }
  while( nfa != 0 && nfa != lfa ) ;
  push_ps ( cstring ) ;
  if( nfa == 0 )
    push_ps( FFALSE ) ;
  else
    {
      push_ps( nfa ) ;
      push_ps( FTRUE ) ;
    }
}

/*
 *	Procedure to convert a lowercase character into an uppercase character.
 */
char upper( n )
     char n ;
{
  if( islower( n ) )
    return( toupper( n ) ) ;
  else
    return( n )	;
}

/*
 *	Procedure convert the counted string on the top of the free dictionary
 *	to a decimal value using the user variable BASE as the current number
 *	base. The 16 bit decimal aproximation together with a 16 bit value of
 *	1 is returned if the counted string was a valid 16 bit number, or the
 *	32 bit decimal aproximation together with a 16 bit value of 2 if the
 *	counted string was a valid 32 bit number. Otherwise 16 bit value 0 and
 */
void number_op()
{
  unsigned short dp , count , base , number ;
  int result , negative , large , error ;
#ifdef DEBUG
  printf("number opcode\n") ;
#endif
  dp = get_word( DP ) ;
  base = get_word( BASE ) ;
  large = FALSE ;
  error = FALSE ;
  negative = FALSE ;
  count = get_byte( dp++ ) ;
  result = 0 ;
  if( get_byte( dp ) == 45 )
    {
      negative = TRUE ;
      dp++ ;
      count-- ;
    }
  do
    {
      number = upper( get_byte( dp ) ) ;
      if( number == 46 )
	{
	  if( large )
	    error = TRUE ;
	  else
	    large = TRUE ;
	  count-- ;
	  dp++ ;
	}
      else
	{
	  number -= 48 ;
	  if( number > 0 )
	    if ( number > 9 )
	      if( number > 16 )
		number = number - 7 ;
	      else
		error = TRUE ;
	  if( ( number < base )	&& !error )
	    {
	      result = result * base + number ;
	      count-- ;
	      dp++ ;
	    }
	  else
	    error = TRUE ;
	}
    }
  while( ( count != 0 )	&& ! error ) ;
  if( negative )
    result = -result ;
  push_ps( ( unsigned short ) result & 0xffff ) ;
  if( large )
    {
      if( result > 0xfff )
	push_ps( ( unsigned short ) ( result >> 16 ) ) ;
      else
	{
	  if( negative )
	    push_ps( -1 ) ;
	  else
	    push_ps( 0 ) ;
	}
    }
  if( ! error )
    if ( large )
      push_ps ( 2 ) ;
    else
      push_ps( 1 ) ;
  else
    push_ps( FFALSE ) ;
}
