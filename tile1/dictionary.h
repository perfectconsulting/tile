/*
 *	Module : dictionary.h
 *	Author : Steven James
 *	Date : 10th February 1990
 *
 *	This module implements the dictionary structure required by the forth
 *	engine.
 *
 *	Functions
 *	build_dictionary()
 */

/*
 *	Procedure to store a 16 bit quantity at the current dictionary address,
 *	and increment the dictionary pointer.
 */
void dpword( value )
     unsigned short value ;
{
  put_word( dp , value ) ;
  dp += 2 ;
}

/*
 *	Procedure to store an 8 bit quabtity at the current dictionary address,
 *	and increment the dictionary pointer.
 */
void dpbyte( value )
     unsigned char value ;
{
  put_byte( dp , value ) ;
  dp++ ;
}

/*
 *	Procedure to construct a dictionay header for the name specified,
 *	and maintain the overall dictionary link structure.
 */
void header( string )
     char string[INITIAL_WIDTH] ;
{
  int i = 0 ;
  dpbyte( ( unsigned char ) strlen( string ) ) ;
  do
    {
      if ( i < strlen( string ) )
	dpbyte( string[i] ) ;
      else
	dpbyte( TILENULL ) ;
      i++;
    }
  while( i < INITIAL_WIDTH ) ;
  dpword( last ) ;
  last = dp - ( INITIAL_WIDTH + 3 ) ;
}

/*
 *	Procedure to set the IMMEDIATE_BIT on the name filed address of the
 *	most reciently defined header.
 */
void immediate()
{
  put_byte( last , get_byte( last ) ^ IMMEDIATE_BIT ) ;
}

/*
 *	Procedure to construct the initial forth dictionary.
 */
void build_dictionary()
{
  unsigned exec_cfa , trap_cfa , word_cfa ;
  dp = INITIAL_DP ;
  last = 0 ;
  colon_cfa = dp ;
  dpword( COLON_OP ) ;
  
  semi_cfa = dp ;
  dpword( dp + 2 ) ;
  dpword( SEMI_OP ) ;

  trap_cfa = dp ;
  dpword( dp + 2 ) ;

  dpword( TRAP_OP ) ;
  header( "execute" ) ;
  exec_cfa = dp ;
  dpword( dp + 2 ) ;
  dpword( EXEC_OP ) ;

  header( "abort" ) ;
  dpword( dp + 2 ) ;
  dpword( ABORT_OP ) ;

  header( "bye" ) ;
  dpword( dp + 2 ) ;
  dpword( EXIT_OP ) ;

  header( "debug") ;
  dpword( dp + 2 ) ;
  dpword( DEBUG_OP ) ;

  
  put_word( INNER , dp ) ;
  dpword( exec_cfa ) ;
  dpword( trap_cfa ) ;

  header( "drop" ) ;
  dpword( dp + 2 ) ;
  dpword( DROP_OP ) ;

  header( "dup" ) ;
  dpword( dp + 2 ) ;
  dpword( DUP_OP ) ;

  header( "swap" ) ;
  dpword( dp + 2 ) ;
  dpword( SWAP_OP ) ;

  header( "over" ) ;
  dpword( dp + 2 ) ;
  dpword( OVER_OP ) ;

  header( "rot" ) ;
  dpword( dp + 2 ) ;
  dpword( ROT_OP ) ;

  header( ">r" ) ;
  dpword( dp + 2 ) ;
  dpword( PUSHR_OP ) ;

  header( "r>" ) ;
  dpword( dp + 2 ) ;
  dpword ( POPR_OP ) ;

  header( "r" ) ;
  dpword( dp + 2 ) ;
  dpword( R_OP ) ;

  header( "i" ) ;
  dpword( dp + 2 ) ;
  dpword( R_OP ) ;

  header( "j" ) ;
  dpword( dp + 2 ) ;
  dpword( J_OP ) ;

  header( "empty?" ) ;
  dpword( dp + 2 ) ;
  dpword( EMPTY_OP ) ;

  header( "!" ) ;
  dpword( dp + 2 ) ;
  dpword( STORE_OP ) ;

  header( "@" ) ;
  dpword( dp + 2 ) ;
  dpword( FETCH_OP ) ;

  header( "c!" ) ;
  dpword( dp + 2 ) ;
  dpword( CSTORE_OP ) ;

  header( "c@" ) ;
  dpword( dp + 2 ) ;
  dpword( CFETCH_OP ) ;

  header( "+" ) ;
  dpword( dp + 2 ) ;
  dpword( ADD_OP ) ;

  header( "d+" ) ;
  dpword( dp + 2 ) ;
  dpword( DADD_OP ) ;

  header( "u*" ) ;
  dpword( dp + 2 ) ;
  dpword( UMUL_OP ) ;

  header( "u/" ) ;
  dpword( dp + 2 ) ;
  dpword( UDIV_OP ) ;

  header( "minus" ) ;
  dpword( dp + 2 ) ;
  dpword( MINUS_OP ) ;

  header( "dminus" ) ;
  dpword( dp + 2 ) ;
  dpword( DMINUS_OP ) ;

  header( "and" ) ;
  dpword( dp + 2 ) ;
  dpword( AND_OP ) ;

  header( "or" ) ;
  dpword( dp + 2 ) ;
  dpword( OR_OP ) ;

  header( "xor" ) ;
  dpword( dp + 2 ) ;
  dpword( XOR_OP ) ;

  header( "not" ) ;
  dpword( dp + 2 ) ;
  dpword( NOT_OP ) ;

  header( "=" ) ;
  dpword( dp + 2 ) ;
  dpword( EQUAL_OP ) ;

  header( ">" ) ;
  dpword( dp + 2 ) ;
  dpword( GREATER_OP ) ;

  header( "<" ) ;
  dpword( dp + 2 ) ;
  dpword( LESS_OP ) ;

  header( "lit" ) ;
  lit_cfa = dp ;
  dpword( dp + 2 ) ;
  dpword( LIT_OP ) ;

  header( "0branch" ) ;
  dpword( dp + 2 ) ;
  dpword( BRANCH_OP ) ;

  header( "branch" ) ;
  dpword( dp + 2) ;
  dpword( JUMP_OP ) ;

  header( "(do)" ) ;
  dpword( dp + 2 ) ;
  dpword( DO_OP ) ;

  header( "(loop)" ) ;
  dpword( dp + 2 ) ;
  dpword( LOOP_OP ) ;

  header( "(+loop)" ) ;
  dpword( dp + 2 ) ;
  dpword( ADDLOOP_OP ) ;

  header( "(emit)" ) ;
  dpword( dp + 2 ) ;
  dpword( EMIT_OP ) ;

  header( "key" ) ;
  dpword( dp + 2 ) ;
  dpword( KEY_OP ) ;

  header( "inline" ) ;
  dpword( dp + 2 ) ;
  dpword( INLINE_OP ) ;

  header( "load" ) ;
  dpword( dp + 2 ) ;
  dpword( FILE_OP ) ;

  header( "stdin?" ) ;
  dpword( dp + 2 ) ;
  dpword( STDIN_OP ) ;

  header( "(.\")" ) ;
  dpword( dp + 2 ) ;
  dpword( STRING_OP ) ;

  header( "word" ) ;
  word_cfa = dp ;
  dpword( dp + 2 ) ;
  dpword( WORD_OP ) ;

  header( "(find)" ) ;
  dpword( dp + 2 ) ;
  dpword( FIND_OP ) ;

  header( "number" ) ;
  dpword( dp + 2 ) ;
  dpword( NUMBER_OP ) ;

  builds_cfa = dp ;
  dpword( BUILDS_OP ) ;

  header( "create" ) ;
  dpword( dp + 2 ) ;
  dpword( CREATE_OP ) ;

  header( "(:)" ) ;
  dpword( dp + 2 ) ;
  dpword( DEFINE_OP ) ;

  header( "(;)" ) ;
  dpword( dp + 2 ) ;
  dpword( END_OP ) ;
  immediate() ;

  header( "\\" ) ;
  dpword( colon_cfa ) ;
  dpword( lit_cfa ) ;
  dpword( 0 ) ;
  dpword( word_cfa ) ;
  dpword( semi_cfa ) ;
  immediate() ;

  dpword( last ) ;
  put_word( CURRENT , dp ) ;
  put_word( CONTEXT , dp ) ;
  dpword( last ) ;

  put_word( DP , dp ) ;
}
