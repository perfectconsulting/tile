/*
 *	Module : Forward.h
 *	Author : Steven James
 *	Date : 13th February 1990
 *
 *	This module defines all forward references used within the tile
 *	source code.
 */

unsigned short dp , nfa , last ;
unsigned short lit_cfa , colon_cfa , semi_cfa , builds_cfa ;

void reset_ps() ;
void reset_rs() ;

unsigned short get_word() ;
unsigned char get_byte() ;
int terminal();

void put_byte() ;

void word_op() ;

