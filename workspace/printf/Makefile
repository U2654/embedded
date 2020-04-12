printf : main.c entry.S
	../../riscv64-unknown-elf-gcc/bin/riscv64-unknown-elf-gcc main.c entry.S -g -o printf -march=rv32ima -mabi=ilp32 -Wl,-e_reset_vector
	
dump-elf: all
	../../riscv64-unknown-elf-gcc/bin/riscv64-unknown-elf-readelf -a printf
	
dump-code: all
	../../riscv64-unknown-elf-gcc/bin/riscv64-unknown-elf-objdump -D printf
	
clean:
	rm -f printf
