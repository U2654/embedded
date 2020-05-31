demo_irq.o: demo_irq.c
	../../riscv64-unknown-elf-gcc/bin/riscv64-unknown-elf-gcc -g -march=rv32ima  -mabi=ilp32 -mcmodel=medany -c -o demo_irq.o demo_irq.c

demo_irq: demo_irq.o
	../../riscv64-unknown-elf-gcc/bin/riscv64-unknown-elf-gcc -g -march=rv32ima  -mabi=ilp32 -mcmodel=medany demo_irq.o  -o demo_irq -L. -T flash.lds -nostartfiles
	
clean:
	rm demo_irq demo_irq.o	

