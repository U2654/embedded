led_asm.o: led_asm.S
	../../riscv64-unknown-elf-gcc/bin/riscv64-unknown-elf-gcc -march=rv32ima  -mabi=ilp32 -mcmodel=medany -g -c -o led_asm.o led_asm.S

led_asm: led_asm.o
	../../riscv64-unknown-elf-gcc/bin/riscv64-unknown-elf-gcc -march=rv32ima  -mabi=ilp32 -mcmodel=medany -g led_asm.o  -o led_asm -L. -T flash.lds -nostartfiles
	
	
clean:
	rm led_asm led_asm.o	
