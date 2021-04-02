.text
	.globl main
main:
	li s0, 0x10012000

	li t1, 0xffffffdf
	lw t0, 0x4(s0)
	and t0, t0, t1
	sw t0, 0x4(s0)

	lw t0, 0x38(s0)
	and t0, t0, t1
	sw t0, 0x38(s0)

	li t2, 0x00000020
	lw t0, 0x8(s0)
	or t0, t0, t2
	sw t0, 0x8(s0)

loop:
	lw t0, 0xC(s0)
	or t0, t0, t2
	sw t0, 0xC(s0)
	call delay

	lw t0, 0xC(s0)
	and t0, t0, t1
	sw t0, 0xC(s0)
	call delay  

	j loop
delay:
	li t0, 0x400000
countdown:
	add t0, t0, -1
	bne t0, x0, countdown
	jr ra
