demo_led.o: demo_led.c
	../../riscv64-unknown-elf-gcc/bin/riscv64-unknown-elf-gcc -O0 -g --save-temps -march=rv32ima  -mabi=ilp32 -mcmodel=medany -c -o demo_led.o demo_led.c

demo_led: demo_led.o
	../../riscv64-unknown-elf-gcc/bin/riscv64-unknown-elf-gcc -O0 -g -march=rv32ima  -mabi=ilp32 -mcmodel=medany demo_led.o  -o demo_led -L. -T flash.lds -nostartfiles -Wl,--gc-sections
	
clean:
	rm demo_led demo_led.o	

