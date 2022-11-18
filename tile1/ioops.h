/*
 *	Module : ioops.h
 *	Author : Steven James
 *	Date : 25th January 1990
 *
 *	This module implements the five main input/output operations required by
 *	the forth enginee, namley KEY (EMIT) INLINE FILE STDIN? (.")
 *
 *	Functions
 *	terminal() configure_strm() open_strm() close_strm()
 *	key_op() emit_op() inline_op() file_op() stdin_op() string_op()
 *	congfigure_term() unconfigure_term()
 */

/* NOTE(MJ): Define macOS as a UNIX */
#if !defined(__unix__) && defined(__APPLE__) && defined(__MACH__)
#define __unix__
#endif

/* TODO(MJ): We should probably factor this out better... */
# if defined(CUSTOM_IO)
/* NOTE(MJ): Placeholder for custom IO functions e.g. UART */
#elif defined(__unix__)
#define ungetch(ch) ungetc(ch,stdin)

int getch(void);
int keypressed(void);
# else
#include <conio.h>

#define getch() _getch()
#define keypressed() _kbhit()
#endif

#ifdef __unix__
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#endif

#define EMIT_OP	700
#define KEY_OP	701
#define INLINE_OP	702
#define FILE_OP	703
#define STDIN_OP	704
#define STRING_OP	705

struct file_elmt
{
  FILE *stream ;
  struct file_elmt *link ;
} ;

struct file_elmt *file_ptr ;


#ifdef __unix__
/*************************************************************************
 * NOTE: Replace these functions for custom I/O e.g. UART                *
 *************************************************************************/

int getch(void) {
    struct termios original, tile;
    int ch;
    
    /* NOTE(MJ): Get original terminal I/O settings */
    tcgetattr(STDIN_FILENO, &original); 
    tile = original; 
    tile.c_lflag &= ~(ICANON | ECHO); 
    tile.c_cc[VTIME] = 0;
    tile.c_cc[VMIN] = 0;
    /* NOTE(MJ); Set new teminal I/O settings */
    tcsetattr(STDIN_FILENO, TCSANOW, &tile); 
    
    ch = getc(stdin);
 
    /* NOTE(MJ): Set original terminal I/O settings */   
    tcsetattr(STDIN_FILENO, TCSANOW, &original);
    
    return ch;
}
#endif

/* TODO(MJ): This hasn't been tested yet... */
int keypressed(void) {
    char ch = getch();

    if (ch != EOF) {
        ungetch(ch);
        return 1;
    }

    return 0;
}


/*
 *	Procedure to test if the current input stream is the terminal keyboard,
 *	and return TRUE if so, or FALSE if otherwise.
 */
int terminal()
{
  if( file_ptr->stream == stdin )
    return( TRUE ) ;
  else
    return( FALSE ) ;
}

/*
 *	Procedure to configure the input stream to that of the terminal keyboard.
 */
void configure_strm()
{
  struct file_elmt *new_file_ptr ;
  new_file_ptr = (struct file_elmt *)
    malloc( sizeof( struct file_elmt ) ) ;
  new_file_ptr->stream = stdin ;
  new_file_ptr->link = NULL ;
  file_ptr = new_file_ptr ;
}

/*
 *	Procedure to open a file as an anternative input stream. The previous
 *	stream pointer is placed upon the file stack, for later retrieval when
 *	the new input stream is exhausted.
 */
open_strm( strm_name )
  char *strm_name ;
{
  FILE *stream ;
  struct file_elmt *new_file_ptr ;
  stream = fopen( dp_string() , "r" ) ;
  if( stream == NULL )
    {
      printf("Unable to open file '%s'\n",strm_name ) ;
    }
  else
    {
      new_file_ptr = (struct file_elmt *)
	malloc( sizeof( struct file_elmt ) ) ;
      new_file_ptr->stream = stream ;
      new_file_ptr->link = file_ptr ;
      file_ptr = new_file_ptr ;
    }
}

/*
 *	Procedure to close the current input stream, and return to the previous
 *	input stream.
 */
close_strm()
{
  struct file_elmt *new_file_ptr ;
  fclose( file_ptr->stream ) ;
  new_file_ptr = file_ptr->link ;
  free( file_ptr ) ;
  file_ptr = new_file_ptr ;
}
/*
 *	Procedure to display the ASCII equivalent of the top 16 bit value on the
 *	parameter stack.
 */
void emit_op ()
{
#ifdef DEBUG
  printf("emit opcode\n") ;
#endif
  putchar( pop_ps() );
}

/*
 *	Procedure to scan the keyboard and push the ASCII equivalent of the key
 *	pressed onto the parameter stack as a 16 bit value.
 */
void key_op()
{
#ifdef DEBUG
  printf("key opcode\n") ;
#endif
  push_ps ( getchar() ) ;
}

/*
 *	Procedure to accept a line of text from the current input stream, and
 *	transfer it to the text input buffer. If an EOF is encountered then the
 *	input stream is reset to accept input from the keyboard. The text
 *	interpreter offset is set to point to the begining of the text input
 *	buffer reguardless of any stream directed action.
 */
void inline_op()
{
  char string[MAXLINE] ;
  unsigned short buffer = get_word( TIB ) ;
  int i = 0 ;
#ifdef DEBUG
  printf("inline opcode\n") ;
#endif
  if( fgets( string , MAXLINE , file_ptr->stream ) == NULL )
    {
      if( ! terminal() )
	{
	  printf( "[End of file]\n" ) ;
	  close_strm() ;
	}
      else
	set_exit() ;
    }
  else
    for( i = 0 ; strcmp( &string[i] , "\n" ) ; i++ )
      {
	if ( string[i] == TAB )
	  string[i] = ( char ) SPACE ;
	put_byte( buffer + i , string[i] ) ;
      }
  put_word( buffer + i , NULL ) ;
  put_word( IN , 0 ) ;
}

/*
 *	Procedure to take the string pointed to be the IN offset within the
 *	text input buffer, and attempt to open it as an input stream. If this
 *	generates an error then the input stream is reset to accept input from
 *	the keyboard, and an error messages is displayed.
 */
void file_op()
{
#ifdef DEBUG
  printf("file opcode\n");
#endif
  push_ps( SPACE ) ;
  word_op() ;
  open_strm( dp_string() ) ;
  forth_abort() ;
}

/*
 *	Procedure to check if the input is indirect via the standard input
 *	stream, and return a 16 bit value to reflect the result.
 */
void stdin_op()
{
#ifdef DEBUG
  printf("stdin opcode\n");
#endif
  if( terminal() )
    push_ps( FTRUE ) ;
  else
    push_ps( FFALSE ) ;
}

/*
 *	Procedure to display the counted string pointed to by the contents of
 *	the instruction register.
 */
void string_op()
{
  unsigned short count ;
#ifdef DEBUG
  printf("string opcode\n");
#endif
  count = get_byte ( i++ ) ;
  do
    {
      putchar( get_byte( i++ ) ) ;
      put_word( OUT , get_word( OUT + 1 ) ) ;
      count-- ;
    }
  while( count != 0 ) ;
}

/*
 *	Procedure to configure the terminal prier to processing by
 *	the forth input/output operations.
 */
void configure_term()
{
  /* NOTE: DO NOTHING */
}

/*
 *	Procedure to re-configure the terminal the state prier to
 *	envoking the configure term procedure.
 */
void unconfigure_term()
{
  /* NOTE: DO NOTHING */
} 
