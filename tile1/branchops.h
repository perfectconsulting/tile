/*
 *	Module : Branchops
 *	Author : Steven James
 *	Date : 26th January 1990
 *
 *	This module implements the branching operations required by the forth
 *	engine, namely BRANCH JUMP DO LOOP +LOOP.
 *
 *	Functions
 *	branch_op () jump_op () do_op () loop_op () addloop_op ()
 */

#define BRANCH_OP	600
#define JUMP_OP	601
#define DO_OP	602
#define LOOP_OP	603
#define ADDLOOP_OP	604

/*
 *	Procedure to perform a relative jump by the value pointed to by the
 *	instruction register if the top value on the parameter stack is zero.
 */
void branch_op()
{
#ifdef DEBUG
  printf("branch opcode\n") ;
#endif
  if( pop_ps() == 0 )
    i += get_word( i ) ;
  else
    i += 2 ;
}

/*
 *	Procedure to perform a relative jump by the value pointed to by the
 *	instruction register.
 */
void jump_op ()
{
#ifdef DEBUG
  printf("else opcode\n") ;
#endif
  i += get_word( i ) ;
}

/*
 *	Procedure to push the top two 16 bit quantities form the parameter
 *	stack to the return stack.
 */
void do_op()
{
  unsigned short top ;
#ifdef DEBUG
  printf("do opcode\n") ;
#endif
  top = pop_ps() ;
  push_rs ( pop_ps () ) ;
  push_rs( top ) ;
}

/*
 *	Procedure to increment the top 16 bit quantity on the return stack, and
 *	compare it with the second 16 bit quantity. If the second is greater
 *	than the firsth then a relative backward jump is made, otherwise the
 *	return stack is decremented and the instruction register is incremented
 *	to contine normal execution.
 */
void loop_op()
{
  short top , bottom ;
#ifdef DEBUG
  printf("loop opcode\n") ;
#endif
  top = pop_rs() +1 ;
  bottom = pop_rs() ;
  if( top < bottom )
    {
      push_rs( bottom ) ;
      push_rs( top ) ;
      i += get_word( i ) ;
    }
  else
    i += 2 ;
}

/*
 *	Procedure to increment the top 16 bit quantity on the return stack by
 *	the top 16 bit quantity on the parameter stack, and compare it with the
 *	second 16 bit quantity on the return stack. If the increment is negative
 *	and the first 16 bit quantity is greater than the second, or the
 *	imcrement is positive and the first 16 bit quantity is smaller than the
 *	second, then a relative backward jump is made, otherwise the return stack
 *	is is decremented and the instruction register is incremented to contine
 *	normal execution.
 */
void addloop_op()
{
  short increment , top , bottom ;
#ifdef DEBUG
  printf("addloop opcode\n") ;
#endif
  top = pop_rs() ;
  increment = pop_ps() ;
  top += increment ;
  bottom = pop_rs() ;
  if( ( increment >0 ) && ( top < bottom ) )
    {
      push_rs( bottom ) ;
      push_rs( top ) ;
      i += get_word( i ) ;
    }
  else
    {
      if( ( increment < 0 ) && ( top > bottom ) )
	{
	  push_rs( bottom ) ;
	  push_rs( top ) ;
	  i += get_word( i ) ;
	}
      else
	i += 2 ;
    }
}
