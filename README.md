# Tools for Embedded Systems Lab

## Objective
The aim of this repository is to provide a solution for lab assignments relating to distance teaching of the embedded systems course at the Bielefeld University of Applied Sciences, Campus Minden.

For further information, please vision https://www.iot-minden.de. 

## Introduction 

We use the RISC-V based virtual prototyp of AGRA Uni Bremen (https://github.com/agra-uni-bremen/riscv-vp) so that we have a virtual embedded system with breadboard. Further, we provide examples based on parts of FreeRTOS and of SiFive Freedom-E-SDK. You find the corresponding licenses of these and their examples in their directories. 

## Instruction for our toolchain

1. We will use Eclipse with GNU MCU plugin as IDE (https://github.com/gnu-mcu-eclipse/org.eclipse.epp.packages/releases). Alternatively, we could use a shell and command line interface. However, we recommend using Eclipse for our labs. 

2. Further, we provide a Docker file for building a container with the RISC-V based virtual prototyp. Thus, please install Docker (https://www.docker.com/products/docker-desktop).

3. As we will use a GUI for the virtual breadboard which runs in the container, we need an XServer, e.g. XQuartz (https://www.xquartz.org) for macOS. Please install an XServer. 

4. Clone our project
```> git clone https://github.com/U2654/embedded.git"
```

5. In order to make writing Makefiles etc. easier, we will use the following directory structure. We use this directory structure in the following:

*~/embedded/workspace* for our (Eclipse) projects
*~/embedded/bin* for scripts running the virtual breadboard with Docker
*~/embedded/conf* for configuration files for virtual the virtual breadboard
*~/embedded/docker* for our Dockerfile for building the container
*~/embedded/riscv64-unknown-elf-gcc* where we assume the GCC toolchain for RISC-V

6. Furthermore, we assume the RISC-V toolchain of SiFive (https://www.sifive.com/boards, see prebuilt RISC‑V GCC Toolchain and Emulator) which must be moved to ~/embedded/riscv64-unknown-elf-gcc bewegen.

7. Build the Docker container.

```> cd ~/embedded/docker
> docker build -t breadboard .
```
8. Start an XServer and allow localhost access.
```> xhost +localhost
```
9. Test an example. We need three shells now.

Build an example project.
```> cd ~/embedded/workspace/demo_gpio/
> make
```
There should be a file in elf demo_gpio now.

Start breadboard.
```> cd ~/embedded
> bin/breadboard.sh conf/sevensegment.json
```
Use a further shell and run 
```> cd ~/embedded/
> bin/hifive.sh workspace/demo_gpio/demo_gpio
```
Finally, run a gdb (after adding to your path the bin of the riscv64-unknown-elf-gcc toolchain)
```> riscv64-unknown-elf-gdb
> target remote:5005
> c
```
Now we should see the virtual breadboard running. Quit with q in the virtual breadboard window.

10. Finally, we can set up Eclipse if we like to. Here is how to with macOS. 

Make a new project in Eclipse with *Makefile Project with Existing Code" and select a project in our workspace. Toolchain choose RISC-V. Create a build target for the project with the same name as the project but change to *make*. Now you can build the project. 

In order to debug, we have to start a virtual prototyp. This can be done with external tools in Eclipse. We will use  scripts which we include as external tools as follows:
* Name: FlashRiscvVP, Location: ${workspace_loc}/../bin/riscv.sh, Working Directory: ${workspace_loc}/../, Arguments: workspace/${project_name}/${project_name}
* Name: FlashHiFiveVP Location: /usr/bin/script, Working Directory: ${workspace_loc}/../, Arguments: -Fq /dev/null /bin/sh -c "bin/hifive.sh workspace${project_path}/${project_name}"
* Name: RunBreadboard, Location: /usr/bin/script, Working Directory: ${workspace_loc}/../,  Arguments:  -Fq /dev/null /bin/sh -c '${workspace_loc}/../bin/breadboard.sh conf/sevensegment.json'
* Name: Kill HiFiveVP, Location: ${workspace_loc}/../bin/kill-vp.sh

Note: adapt the scripts if necessary.

## Debug a project

Create debug configuration for the project as follows. Choos C/C++ Remote Application and set Project to the project name and C/C++ Application to the project name. Set Using GDB (DSF) Manual Remote Debugging. IN the Debugger tab, set GDB debugger to riscv64-unknown-elf-gdb (located in ~/embedded/riscv64-unknown-elf-gcc/bin). and Connection to Host localhost with Port number: 5005.

Done. Compile with the Build Target, Select the current project. For a RISC-V project, run the external tool FlashRiscvVP; for a HiFive-Project start a breadboard with RunBreadboard, virtually flash with FlashHiFiveVP. In both cases, start the debug configuration and continue.


