demo_button.o: demo_button.c
	../../riscv64-unknown-elf-gcc/bin/riscv64-unknown-elf-gcc -g -march=rv32ima  -mabi=ilp32 -mcmodel=medany -c -o demo_button.o demo_button.c

demo_button: demo_button.o
	../../riscv64-unknown-elf-gcc/bin/riscv64-unknown-elf-gcc -g -march=rv32ima  -mabi=ilp32 -mcmodel=medany demo_button.o  -o demo_button -L. -T flash.lds -nostartfiles
	
clean:
	rm demo_button demo_button.o	

