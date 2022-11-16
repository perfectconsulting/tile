/*
 *	Module : fstring.h
 *	Author : Steven January 1990
 *	Date : 14th February 1990
 *
 *	This module implements the string handeling routines that enable 'c'
 *	to manipulate the 'tile' counted string construct.
 *
 *	Functions
 *	char *dp_string()
 */

/*
 *	Procedure to construct a 'cr string from the 'tile' counted string
 *	stored at he top of the free dictionary.
 */
char *dp_string()
{
  char string[MAXLINE] ;
  unsigned short buffer , length ;
  int i ;
  buffer = get_word( DP ) ;
  length = get_byte( buffer++ ) & LENGTH_MASK ;
  for( i = 0 ; i < length ; i++ )
    string[i] = ( char ) get_byte( buffer + i ) ;
  string[i] = ( char ) NULL ;
  return( string ) ;
}
