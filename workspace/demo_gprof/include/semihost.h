/*
 * semihost.h
 *
 *  Created on: 08-Mar-2019
 *
 * semi-hosting calls originally implemented has been modified to fit for this project
 * Only Supports minimal functionality  1. open 2.close 3.read 4.write and "semi_write" which write to debug console
 * No buffered IO.
 * "open" system calls does't check if file to open exits. So user has to take care of following
 *         1. Read a file that does't exits
 *         2. Create a new file which already exits with same name
 *  To avoid any complications delete gmon.out file before re-running the program to generate profiling data
 *
 *  check semihost.c for license details
 */


#ifndef INCLUDE_SEMIHOST_H_
#define INCLUDE_SEMIHOST_H_
#include <stdio.h>


#define RISCV_SEMIHOSTING_CALL_NUMBER 7
#define OS_INTEGER_TRACE_SEMIHOSTING_BUFF_ARRAY_SIZE  (16)


#define OS_INTEGER_SEMIHOSTING_MAX_OPEN_FILES (2)

struct file
{
  int handle;
  off_t pos;
};

typedef void* field_t ;

int semi_write (const void* buf, int nbyte);  //accepts two arguments 1: string buffer 2: size of the buffer

void init_handles(void);// has to be called before using any semihosting calls




#endif /* INCLUDE_SEMIHOST_H_ */
