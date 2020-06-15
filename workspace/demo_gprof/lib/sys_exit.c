/* See LICENSE of license details. */

#include <unistd.h>
#include <string.h>
#include "semihost.h"
#include "gprof/gmon.h"

void _exit(int code)
{
  const char debug[]="Done";
  _mcleanup();
  semi_write(debug,strlen(debug)+1);
  for (;;);
}
