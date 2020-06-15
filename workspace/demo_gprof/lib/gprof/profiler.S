# define RSIZE 4

.section .text
.align 2
.globl  _mcount
 _mcount:
  addi sp,sp,-4*RSIZE
  sw ra, 3*RSIZE(sp)
  mv	a1,ra
  jal  _mcount_internal
  lw ra,  3*RSIZE(sp)
  addi sp,sp,4*RSIZE
  ret
