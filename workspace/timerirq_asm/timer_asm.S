.text
	.globl main
main:
	li s0, 0x10012000

	li t1, 0xffb7fffd
	lw t0, 0x4(s0)
	and t0, t0, t1
	sw t0, 0x4(s0)

	li t2, 0x00480002
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
	li t0, 0x200bff8
	lw t3, 0(t0)
	addi t4, x0, 0x80
	slli t4, t4, 8
	add t4, t4, t3
countdown:
	lw t3, 0(t0)
	ble t3, t4, countdown
	jr ra

