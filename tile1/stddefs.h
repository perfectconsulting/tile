
/* Standard definitions */

#include <stdbool.h>

#define TRUE true
#define FALSE false
//#define DEBUG 1

#define TILENULL 0

struct file_elmt
{
  FILE *stream ;
  struct file_elmt *link ;
  int line;
} ;

struct file_elmt *file_ptr ;