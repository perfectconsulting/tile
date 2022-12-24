/*
 *	Module : Innerops.h
 *	Author : Steven James
 *	Date : 21st January 1990
 *
 *	This module implements the eight main inner interpreter operations
 *	required by the forth engine, namely RUN NEXT COLON SEMI EXEC TRAP
 *	EXIT ABORT .
 *
 *	Functions
 *	run() next() colon_op() semi_op() exec_op() trap_op() exit_op()
 *	abort_op() ;
 */

#define COLON_OP 1
#define SEMI_OP 2
#define EXEC_OP 3
#define TRAP_OP 4
#define EXIT_OP 5
#define ABORT_OP 6
#define DEBUG_OP 7

unsigned short i,wa,ca ;

/*
 *	Procedure to fetch the word pointed to by the word address register,
 *	and place it in the code address register. Then increment the
 *	word address register.
 */
void run()
{
  ca = get_word( wa ) ;
  wa += 2 ;
}

/*
 *	Procedure to fetch the word pointed to by the instruction register,
 *	and place it in the word address register. Then increment the
 *	instruction register.
 */
void next()
{
  wa = get_word( i ) ;
  i += 2 ;
  run()	;
}

/*
 *	Procedure to push the instruction register onto the return stack,
 *	and transfer the word addresss register to the instruction register.
 */
void colon_op()
{
#ifdef DEBUG
  printf("colon opcode\n");
#endif
  push_rs( i ) ;
  i = wa ;
}

/*
 *	Procedure to pop the top item on the return stack into the instrcution
 *	register.
 */
void semi_op()
{
#ifdef DEBUG
  printf("semi opcode\n");
#endif
  i = pop_rs() ;
}

/*
 *	Procedure to pop the top item on the parameter stack into the word
 *	address register.
 */
void exec_op()
{
#ifdef DEBUG
  printf("exec opcode\n");
#endif
  wa = pop_ps() ;
}

/*
 *	Procedure to generate a trap so that the inner interpreter will trip
 *	back into the outer interpreter at the end of this execution cycle.
 */
void trap_op()
{
#ifdef DEBUG
  printf("trap opcode\n");
#endif
  set_trap() ;
}

/*
 *	Procedure to set the exit condition so that the outer interpreter will
 *	terminate at the end of the inner interpreter execution cycle.
 */
void exit_op ()
{
#ifdef DEBUG
  printf("exit opcode\n");
#endif
  set_exit() ;
}

/*
 *	Procedure to generate a trap, reset the parameter stack pointer and
 *	set the STATE user variable to false, so that the inner interpreter
 *	will trip back into the outer interpreter at the end of this execution
 *	cycle.
 */
void abort_op()
{
#ifdef DEBUG
  printf("abort opcode\n");
#endif
  forth_abort() ;
}

void debug_op()
{
  for(int i = 0; i < ps; i++)
  {
    printf("%d (0x%04X)", pstk[i], pstk[i]);
    char c = ',';
    if(i + 1 ==  ps)
    {
      c = '\n';
    }
    putchar(c);
  }
}