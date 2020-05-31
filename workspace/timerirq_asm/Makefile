timerirq_asm.o: timerirq_asm.S
	../../riscv64-unknown-elf-gcc/bin/riscv64-unknown-elf-gcc -g -march=rv32ima  -mabi=ilp32 -mcmodel=medany -c -o timerirq_asm.o timerirq_asm.S

timerirq_asm: timerirq_asm.o
	../../riscv64-unknown-elf-gcc/bin/riscv64-unknown-elf-gcc -g -march=rv32ima  -mabi=ilp32 -mcmodel=medany timerirq_asm.o  -o timerirq_asm -L. -T flash.lds -nostartfiles
	
	
clean:
	rm timerirq_asm timerirq_asm.o	
