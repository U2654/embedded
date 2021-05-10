/* See LICENSE of license details. */

#include <errno.h>
#include <sys/stat.h>

int _stat(const char* file, struct stat* st)
{
  return -1;
}
