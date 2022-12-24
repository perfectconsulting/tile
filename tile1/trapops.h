/*
 *	Module : Trapops.h
 *	Author : Steven James
 *	Date : 13th February 1990
 *
 *	This module implements the seven main trap operations required by the
 *	forth engine, namely trap and exit ( set, reset and test ) and abort.
 *	and abort.
 *
 *	Functions
 *	set_trap() reset_trap() int trapped() forth_abort ()
 *	set_exit() reset_exit() int finished()
 */

int trap_evnt , exit_evnt ;

/*
 *	Procedure to set the trap flag so that the innner interpreter will trip
 *	back into the outer interpreter at the end of this execution cycle.
 */
void set_trap()
{
  trap_evnt = TRUE ;
}

/*
 *	Procedure to reset the trap flag to avert the associated actions.
 */
void reset_trap()
{
  trap_evnt = FALSE ;
}

/*
 *	Procedure to test if the trap flag is set and return true, otherwise
 *	return false.
 */
int trapped()
{
  return( trap_evnt == TRUE ) ;
}

/*
 *	Procedure to terminate the text input buffer interpretation.
 */
void forth_abort()
{
  put_word( get_word( TIB ) + get_word( IN ) , TILENULL ) ;
  set_trap() ;
  reset_ps() ;
  reset_rs() ;
  put_word( STATE , FFALSE ) ;
}

/*
 *	Procedure to set the exit flag so that the outer interpreter will
 *	terminate at the end of the inner interpreter cycle.
 */
void set_exit()
{
  exit_evnt = TRUE ;
}

/*
 *	Procedure to reset the trap flag to avert the associated actions.
 */
void reset_exit()
{
  exit_evnt = FALSE ;
}

/*
 *	Procedure to test if the exit flag is set and return true, otherwise
 * return false.
 */
int finished()
{
  return( exit_evnt == TRUE ) ;
}
