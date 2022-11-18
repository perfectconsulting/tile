/*
 *	Module : Memory.h
 *	Author : Steven James
 *	Date : 19th January 1990
 *
 *	This module implements the memory addresing mechanisms of the forth
 *	engine, and simulates the 64K of contigious 8 bit bytes required by the
 *	interpreter.
 *
 *	Functions
 *	put_byte(ushort,char) char get_byte(ushort)
 *	put_word(ushort,ushort) ushort get_word(ushort)
 *	c1aim_memory() f ree_memory()
 */

#define BLOCKSIZE 0xffff

char *base ;

/*
 *	Procedure to initialise the address space to map onto the 64K of
 *	contigious 8 bit bytes required by the interpreter.
 */
void claim_memory()
{
  base = ( char * ) malloc( BLOCKSIZE ) ;
}

/*
 *	Procedure to free the 64K of contigious 8 bit bytes used by the i
 *	interpreter and return them to the free heap.
 */
void free_memory()
{
  free( base ) ;
}

/*
 *	Procedure to store an 8 bit quantity in the 68K address space.
 */
void put_byte( addr, value )
     unsigned short addr;
     unsigned char value ;
{
  char *place ;
  place = base + addr ;
  *place = value ;
}

/*
 *	Procedure to store a 16 bit quantity in the 64K address space.
 *	A 16 bit value is stored as two consecutive 8 bit bytes with the
 *	most significant byte first.
 */
void put_word( addr , value )
     unsigned short addr, value ;
{
  put_byte( addr , value >> 8 ) ;
  put_byte( addr + 1 , value & 0xff );
}

/*
 *	Procedure to fetech an 8 bit quantity from the 64K address space.
 */
unsigned char get_byte( addr )
     unsigned short addr ;
{
  char *place ;
  place = base + addr ;
  return( *place ) ;
}

/*
 *	Procedure to fetch a 16 bit quantity from the 64K address space.
 *	A 16 bit value is stored as two consecutive 8 bit bytes with the
 *	most significant byte first.
 */
unsigned short get_word( addr )
     unsigned short addr ;
{
  unsigned short value ;
  value = get_byte( addr ) << 8 ;
  value = value + get_byte ( addr + 1 ) ;
  return( value ) ;
}
