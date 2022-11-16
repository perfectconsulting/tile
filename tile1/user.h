/*
 *	Module : User.h
 *	Author : Steven James
 *	Date : 29th January 1990
 *
 *	This module implements the initialisation, and configuration of the
 *	seven user variables required by the forth engine.
 *
 *	Functions :-
 *	configure variables()
 */

void put_word() ;

#define DP	0
#define STATE	2
#define TIB	4
#define IN	6
#define BASE	8
#define CURRENT	10
#define CONTEXT	12
#define WIDTH	14
#define OUT	16
#define INNER	18

#define INITIAL_DP	120
#define INITIAL_STATE	0
#define INITIAL_TIB	40
#define INITIAL_IN	0
#define INITIAL_BASE	10
#define INITIAL_CURRENT	0
#define INITIAL_CONTEXT	0
#define INITIAL_WIDTH	20
#define INITIAL_OUT	0
#define INITIAL_INNER	0


/*
 *	Procedure to initialises the user variables outlined above to their
 *	initial cold start values.
 */
void configure_variables()
{
  put_word( DP , INITIAL_DP );
  put_word( STATE, INITIAL_STATE ) ;
  put_word( TIB , INITIAL_TIB ) ;
  put_word( IN , INITIAL_IN ) ;
  put_word( BASE , INITIAL_BASE ) ;
  put_word( CURRENT , INITIAL_CURRENT ) ;
  put_word( CONTEXT , INITIAL_CONTEXT ) ;
  put_word( WIDTH , INITIAL_WIDTH ) ;
  put_word( OUT , INITIAL_OUT ) ;
  put_word ( INNER , INITIAL_INNER ) ;
}
