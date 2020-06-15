/* See LICENSE of license details. */

#include <stddef.h>
#include "semihost.h"

void *_sbrk(ptrdiff_t incr)
{
  char debug[64];
  extern char _end[];
  extern char _heap_end[];
  static char *curbrk = _end;
  if ((curbrk + incr < _end) || (curbrk + incr > _heap_end))
	   return NULL;
  curbrk += incr;
  return curbrk - incr;
}
