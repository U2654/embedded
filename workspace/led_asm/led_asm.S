# assembler blinky
.text
	.globl main
main:

	li  s0, 0x10012000 	# gpio base

						# init. disable input
	li t1, 0xffbfffff	# all one except bit 22 = zero
	lw	t0, 0x4(s0)		# unset bit 22 in 0x4 (input_en)
	and t0, t0, t1
	sw	t0, 0x4(s0)
						# init. enable output
	li  t2, 0x400000	# all zero except bit 22 = one
	lw  t0, 0x8(s0) 	# set bit 22 in 0x8 (output_en)
	or t0, t0, t2
	sw  t0, 0x8(s0)

loop:
	lw  t0, 0xC(s0)		# set bit 22 in 0xC (output_val)
	or t0, t0, t2
	sw  t0, 0xC(s0)
	call	delay		# delay

	lw  t0, 0xC(s0)		# unset bit 22 in 0xC (output_val(
	and t0, t0, t1
	sw  t0, 0xC(s0)
	call	delay		# delay

	j	 loop			# continue loop

delay:
	li t0, 04001001		# countdown to zero
countdown:
	add t0, t0, -1
	bne t0, x0, countdown
	jr ra				# return

