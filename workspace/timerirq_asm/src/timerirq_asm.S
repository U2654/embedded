# defines
.equ gpio_base, 0x10012000
.equ mtimecmp, 0x2004000
.equ mtime, 0x200bff8
.text
	.globl main
main:
# gpio...
	li s0, gpio_base
# disable input
	li t1, 0xffffffdf

	lw t0, 0x4(s0)
	and t0, t0, t1
	sw t0, 0x4(s0)
#disable iof
	lw t0, 0x38(s0)
	and t0, t0, t1
	sw t0, 0x38(s0)

# enable output
	li t2, 0x00000020

	lw t0, 0x8(s0)
	or t0, t0, t2
	sw t0, 0x8(s0)

# disable timer interrupt
    li t0, 0x80
    csrc mie, t0

# read time (64 bit)
    li t0, mtime
# get current time
    lw t3, 0(t0)
    lw t4, 4(t0)

# build 16384 
    addi t5, x0, 0x80
    slli t5, t5, 7

# and add but beware of overflow
    add t3, t3, t5
# check overflow
    sltu t6, t3, t5
    add t4, t4, t6

# set timecmp, cf. Vol II 
    li t0, mtimecmp
    li t5, -1
    sw t5, 0(t0)
    sw t4, 4(t0)
    sw t3, 0(t0)

# set time handler
    la t0, handler
    csrw mtvec, t0
# enable timer irq
    li t0, 0x80
    csrs mie, t0
# enable interrupts
    csrsi mstatus, 0x8

loop:
# wait for interrupt
    wfi
	j	loop

.align 2
handler:
# attention, no care of registers.
# read time (64 bit)
    li t0, mtime
# get current time
    lw t3, 0(t0)
    lw t4, 4(t0)

# build 16384 
    addi t5, x0, 0x80
    slli t5, t5, 7

# and add but beware of overflow
    add t3, t3, t5
# check overflow
    sltu t6, t3, t5
    add t4, t4, t6

# set timecmp, cf. Vol II 
    li t0, mtimecmp
    li t5, -1
    sw t5, 0(t0)
    sw t4, 4(t0)
    sw t3, 0(t0)

# toggle led
    li t2, 0x00000020
    lw t0, 0xC(s0)
    xor t0, t0, t2
    sw t0, 0xC(s0)
    mret

