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
	li t1, 0xffb7ffff
	lw t0, 0x4(s0)
	and t0, t0, t1
	sw t0, 0x4(s0)
# enable output
	li t2, 0x00480000
	lw t0, 0x8(s0)
	or t0, t0, t2
	sw t0, 0x8(s0)

# disable timer interrupt
    li t0, 0x80
    csrc mie, t0
# read time
    li t0, mtime
# get current time
    lw t3, 0(t0)
# add 16384
    addi t4, x0, 0x80
    slli t4, t4, 7
    add t4, t4, t3
# set timecmp
    li t0, mtimecmp
    sw t4, 0(t0)
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

.align 4
handler:
# get current time
    li t0, mtime
    lw t3, 0(t0)
# add 16384
    addi t4, x0, 0x80
    slli t4, t4, 7
    add t4, t4, t3
# set timecmp
    li t0, mtimecmp
    sw t4, 0(t0)
# toggle leds
    li t2, 0x00480000
    lw t0, 0xC(s0)
    xor t0, t0, t2
    sw t0, 0xC(s0)
    mret

