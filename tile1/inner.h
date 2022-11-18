/*
 *	Module : inner.h
 *	Author : Steven James
 *	Date : 31th January 1990
 *
 *	This module implements the operation of the forth inner interpreter.
 *
 *	Functions
 *	inner	() ;
 */

/*
 *	Procedure to implements the operation of the forth inner interpreter.
 *	On entry the address specified is placed in the instruction register
 *	and a next is executed. The inner intrpreter will continue to operate
 *	until a trap or invalid instruction is encounted, at which point the
 *	interpreter will hault and return control back to the calling
 *	procedure or program.
 */
void inner( addr )
     unsigned short addr;
{
  i = addr ;
  next() ;
#ifdef DEBUG
  printf("registers : i %d wa %d ca %d\n", i, wa,ca) ;
#endif
  do
    {
      switch ( get_word( ca ) )
	{
	case COLON_OP : colon_op() ;
	  next() ;
	  break ;
	case SEMI_OP	:	semi_op()	;
	  next() ;
	  break ;
	case EXEC_OP	:	exec_op()	;
	  run()	;
	  break ;
	case TRAP_OP	:	trap_op()	;
	  break ;
	case EXIT_OP	:	exit_op()	;
	  next() ;
	  break ;
	case ABORT_OP : abort_op() ;
	  next() ;
	  break ;
	case DROP_OP	:	drop_op() ;
	  next() ;
	  break ;
	case DUP_OP	:	dup_op() ;
	  next() ;
	  break ;
	case SWAP_OP	:	swap_op() ;
	  next() ;
	  break ;
	case OVER_OP	:	over_op()	;
	  next() ;
	  break ;
	case ROT_OP	:	rot_op() ;
	  next() ;
	  break ;
	case PUSHR_OP	: pushr_op() ;
	  next() ;
	  break ;
	case POPR_OP	:	popr_op()	;
	  next() ;
	  break ;
	case R_OP	:	r_op() ;
	  next() ;
	  break ;
	case J_OP	:	j_op() ;
	  next() ;
	  break ;
	case EMPTY_OP	: empty_op() ;
	  next() ;
	  break ;
	case STORE_OP : store_op() ;
	  next()	;
	  break ;
	case FETCH_OP : fetch_op() ;
	  next() ;
	  break ;
	case CSTORE_OP : cstore_op() ;
	  next()	;
	  break ;
	case CFETCH_OP : cfetch_op() ;
	  next() ;
	  break ;
	case ADD_OP	:	add_op() ;
	  next() ;
	  break ;
	case DADD_OP	:	dadd_op()	;
	  next() ;
	  break ;
	case UMUL_OP	:	umul_op()	;
	  next() ;
	  break ;
	case UDIV_OP	:	udiv_op()	;
	  next() ;
	  break ;
	case MINUS_OP : minus_op() ;
	  next() ;
	  break ;
	case DMINUS_OP : dminus_op() ;
	  next() ;
	  break ;
	case AND_OP	:	and_op()	;
	  next() ;
	  break ;
	case OR_OP	:	or_op() ;
	  next() ;
	  break ;
	case XOR_OP	:	xor_op()	;
	  next() ;
	  break ;
	case NOT_OP	:	not_op()	;
	  next() ;
	  break ;
	case EQUAL_OP : equal_op() ;
	  next() ;
	  break ;
	case GREATER_OP : greater_op()	;
	  next() ;
	  break ;
	case LESS_OP : less_op() ;
	  next() ;
	  break ;
	case LIT_OP	: lit_op() ;
	  next()	;
	  break ;
	case CONST_OP : const_op() ;
	  next() ;
	  break ;
	case BRANCH_OP : branch_op() ;
	  next() ;
	  break ;
	case JUMP_OP	: jump_op() ;
	  next() ;
	  break ;
	case	DO_OP	:	do_op() ;
	  next() ;
	  break ;
	case	LOOP_OP	:	loop_op()	;
	  next() ;
	  break ;
	case ADDLOOP_OP : addloop_op() ;
	  next() ;
	  break ;
	case	EMIT_OP	:	emit_op()	;
	  next() ;
	  break ;
	case	KEY_OP	:	key_op() ;
	  next() ;
	  break ;
	case INLINE_OP : inline_op() ;
	  next() ;
	  break ;
	case	FILE_OP	:	file_op() ;
	  next() ;
	  break ;
	case STDIN_OP : stdin_op() ;
	  next() ;
	  break ;
	case STRING_OP : string_op() ;
	  next() ;
	  break ;
	case	WORD_OP	:	word_op() ;
	  next() ;
	  break ;
	case FIND_OP : find_op() ;
	  next() ;
	  break ;
	case	NUMBER_OP	:	number_op()	;
	  next() ;
	  break ;
	case	BUILDS_OP	:	builds_op()	;
	  next() ;
	  break ;
	case DOES_OP : does_op() ;
	  next() ;
	  break ;
	case CREATE_OP : create_op() ;
	  next() ;
	  break ;
	case DEFINE_OP : define_op() ;
	  next() ;
	  break ;
	case END_OP	:	end_op() ;
	  next() ;
	  break ;
	default	:	printf("bad	opcode\n") ;
	  forth_abort() ;
	  break ;
	}
#ifdef DEBUG
      printf ("registers : i %d wa %d ca %d\n", i, wa, ca) ;
#endif
    }
  while ( ! trapped() ) ;
  reset_trap() ;
}
