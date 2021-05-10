

Download Toolchain:

	https://github.com/xpack-dev-tools/riscv-none-embed-gcc-xpack/releases/download/v8.3.0-1.1/xpack-riscv-none-embed-gcc-8.3.0-1.1-linux-x64.tgz


Download openocd:
		
	https://github.com/xpack-dev-tools/openocd-xpack/releases/download/v0.10.0-13/xpack-openocd-0.10.0-13-linux-x64.tgz
		
		
Download the source:

	git clone https://github.com/sbzpro/riscv-gprof.git
	cd riscv-gprof

		
Add openocd 

	export PATH=<PATH/TO/OPENOCD>/bin:${PATH}
		
Run openocd and wait for connection

	cd build && openocd -f ../config/openocd.cfg
		
Add toolchain to PATH and Compile:

	open new terminal <ctrl>+<shift>+t; In new terminal type the following
	export PATH=<PATH/TO/TOOLCHAIN>/bin:${PATH}
	cd build && make 
       		
Run GDB and connect to target:

	$> riscv-none-embed-gdb riscv-gprof.elf	
			$ target extended-remote localhost:3333
			$ load riscv-gprof.elf
			$ c <ENTER>
				
				
If everything goes correct a message "done" is printed in openocd console.

Exit GDB and run cross gprof

	riscv-none-embed-gprof riscv-gprof.elf gmon.out >> analysis.txt


Adding Your code to profile:

	
	Code that needs to be instrumented should be present in  <PATH/TO>/riscv-gprof/src/ folder
	Funtions needs to be instrumented should be prepended with "PROFILE" macro
	prepend function with NO_INSTRUMENT macro to avoid instrumenting
	if new file is added to <PATH/TO>/riscv-gprof/src/ folder edit <PATH/TO>/riscv-gprof/build/src/subdir.mk and 
	add newly added filename for compilation.

