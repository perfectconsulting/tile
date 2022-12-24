/*
 *	Module : Memoryops.h
 *	Author : Steven James
 *	Date : 23rd January 1990
 *
 *	This module implements the six main memory interfacing operations
 *	required by the forth engine, namely ! (fetch) @ (store) , (comma)
 *	for both 8 and 16 quantities
 *
 *	Functions
 *	store_op() fetch_op() cstore_op() cfetch_op()
 */

#define STORE_OP	200
#define FETCH_OP	201
#define CSTORE_OP	202
#define CFETCH_OP	203

/*
 *	Procedure to store a 16 bit quantity from the second position on the
 *	parameter stack to the address on the top of the parameter stack.
 */
void store_op()
{
  unsigned short addr,value ;
#ifdef DEBUG
  printf("store opcode\n");
#endif
  addr = pop_ps () ;
  value = pop_ps() ;
  put_word( addr , value );
}

/*
 *	Procedure to fetch the contents of the address on the top of the
 *	parameter stack, and push it as a 16 bit quantity onto the parameter
 *	stack.
 */
void fetch_op()
{
  unsigned short addr ;
#ifdef DEBUG
  printf("fetch opcode\n");
#endif
  addr = pop_ps() ;
  push_ps ( get_word( addr ) ) ;
}

/*
 *	Procedure to store an 8 bit quantity from the second position on the
 *	parameter stack to the address on the top of the parameter stack.
 */
void cstore_op()
{
  unsigned short addr,value ;
#ifdef DEBUG
  printf("cstore opcode\n");
#endif
  addr = pop_ps() ;
  value = pop_ps() ;
  put_byte( addr,value ) ;
}

/*
 *	Procedure to fetch the contents of the address on the top of the
 *	parameter stack, and push it as an 8 bit quantity onto the parameter
 *	stack.
 */
void cfetch_op()
{
  unsigned short addr ;
#ifdef DEBUG
  printf("cfetch opcode\n") ;
#endif
  addr = pop_ps () ;
  push_ps( get_byte( addr ) ) ;
}
