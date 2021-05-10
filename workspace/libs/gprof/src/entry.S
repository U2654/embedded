/*See LICENSE of license details.*/

#include "encoding.h"


#define RSIZE 4

  .section 		.text
  .align 2
  .global 		riscv_trap_entry
riscv_trap_entry:
  addi sp, sp, -32*RSIZE
  sw x1, 1*RSIZE(sp)
  sw x2, 2*RSIZE(sp)
  sw x3, 3*RSIZE(sp)
  sw x4, 4*RSIZE(sp)
  sw x5, 5*RSIZE(sp)
  sw x6, 6*RSIZE(sp)
  sw x7, 7*RSIZE(sp)
  sw x8, 8*RSIZE(sp)
  sw x9, 9*RSIZE(sp)
  sw x10, 10*RSIZE(sp)
  sw x11, 11*RSIZE(sp)
  sw x12, 12*RSIZE(sp)
  sw x13, 13*RSIZE(sp)
  sw x14, 14*RSIZE(sp)
  sw x15, 15*RSIZE(sp)
  sw x16, 16*RSIZE(sp)
  sw x17, 17*RSIZE(sp)
  sw x18, 18*RSIZE(sp)
  sw x19, 19*RSIZE(sp)
  sw x20, 20*RSIZE(sp)
  sw x21, 21*RSIZE(sp)
  sw x22, 22*RSIZE(sp)
  sw x23, 23*RSIZE(sp)
  sw x24, 24*RSIZE(sp)
  sw x25, 25*RSIZE(sp)
  sw x26, 26*RSIZE(sp)
  sw x27, 27*RSIZE(sp)
  sw x28, 28*RSIZE(sp)
  sw x29, 29*RSIZE(sp)
  sw x30, 30*RSIZE(sp)
  sw x31, 31*RSIZE(sp)


  csrr a0, mcause
  csrr a1, mepc
  mv a2, sp

  call trap_handler

  li t0, MSTATUS_MPP  // stay in M mode
  csrs mstatus, t0

  lw x1, 1*RSIZE(sp)
  lw x2, 2*RSIZE(sp)
  lw x3, 3*RSIZE(sp)
  lw x4, 4*RSIZE(sp)
  lw x5, 5*RSIZE(sp)
  lw x6, 6*RSIZE(sp)
  lw x7, 7*RSIZE(sp)
  lw x8, 8*RSIZE(sp)
  lw x9, 9*RSIZE(sp)
  lw x10, 10*RSIZE(sp)
  lw x11, 11*RSIZE(sp)
  lw x12, 12*RSIZE(sp)
  lw x13, 13*RSIZE(sp)
  lw x14, 14*RSIZE(sp)
  lw x15, 15*RSIZE(sp)
  lw x16, 16*RSIZE(sp)
  lw x17, 17*RSIZE(sp)
  lw x18, 18*RSIZE(sp)
  lw x19, 19*RSIZE(sp)
  lw x20, 20*RSIZE(sp)
  lw x21, 21*RSIZE(sp)
  lw x22, 22*RSIZE(sp)
  lw x23, 23*RSIZE(sp)
  lw x24, 24*RSIZE(sp)
  lw x25, 25*RSIZE(sp)
  lw x26, 26*RSIZE(sp)
  lw x27, 27*RSIZE(sp)
  lw x28, 28*RSIZE(sp)
  lw x29, 29*RSIZE(sp)
  lw x30, 30*RSIZE(sp)
  lw x31, 31*RSIZE(sp)

  addi sp, sp, 32*RSIZE
  mret

