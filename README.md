# Tools for Embedded Systems Lab

## Objective
The aim of this repository is to provide a solution for lab assignments relating to distance teaching of the embedded systems course at the Bielefeld University of Applied Sciences, Campus Minden.

For further information, please vision https://www.iot-minden.de. 

## Introduction 

We use the RISC-V based virtual prototyp of AGRA Uni Bremen (https://github.com/agra-uni-bremen/riscv-vp) so that we have a virtual embedded system with breadboard. Further, we provide examples based on parts of FreeRTOS and of SiFive Freedom-E-SDK. You find the corresponding licenses of these and their examples in their directories. 

## Instruction for our toolchain

1. We will use Eclipse with GNU MCU plugin as IDE (https://github.com/gnu-mcu-eclipse/org.eclipse.epp.packages/releases). Alternatively, we could use a shell and command line interface. However, we recommend using Eclipse for our labs. 

2. Further, we provide a Docker file for building a container with the RISC-V based virtual prototyp. Thus, please install Docker (https://www.docker.com/products/docker-desktop).

3. As we will use a GUI for the virtual breadboard which runs in the container, we need an XServer, e.g. [XQuartz](https://www.xquartz.org) for macOS or e.g [VcXSrv](https://uni-tuebingen.de/fakultaeten/wirtschafts-und-sozialwissenschaftliche-fakultaet/faecher/fachbereich-wirtschaftswissenschaft/fachbereich-wirtschaftswissenschaft/wirtschaftswissenschaft/einrichtungen-wirtschaftswissenschaft/it/services/services/computing-asp/tools/x-server/vcxsrv/) for Windows.  Please install an XServer. 

4. Clone this project
```
> git clone https://github.com/U2654/embedded.git
```

5. In order to make writing Makefiles etc. easier, we will use the following directory structure. We use this directory structure in the following:

   *~/embedded/workspace* for our (Eclipse) projects

   *~/embedded/bin* for scripts running the virtual breadboard with Docker

   *~/embedded/conf* for configuration files for virtual the virtual breadboard

   *~/embedded/docker* for our Dockerfile for building the container

   *~/embedded/riscv64-unknown-elf-gcc* where we assume the GCC toolchain for RISC-V

6. Furthermore, we assume the RISC-V toolchain of SiFive (https://www.sifive.com/boards, see prebuilt RISC‑V GCC Toolchain and Emulator) which must be moved to ~/embedded/riscv64-unknown-elf-gcc.

7. Build the Docker container.

```
> cd ~/embedded/docker
> docker build -t breadboard .
```
8. Start an XServer and allow localhost access.
```
> xhost +localhost
```

For VcXSrv:
> 1. Start XLaunch
> 2. Follow the wizard and select: Muliple Windows; Display Number -1
> 3. Start no client
> 4. Clipboard (and primary Selection), Native opengl


9. (For Windows only) Since most UNIX systems have make preinstalled, this step is not necessary for MacOS and Linux users. There are many ways to install make. A simple one is via the package manager chocolatery.
* Install chocolatey from [here](https://chocolatey.org/install)
* Then, `choco install make`

10. Test an example. We need three shells now. For Windows you can use the same commands, but use the .bat files instead of .sh. Correct the Paths Windows-like, but remember not to change the parameters of the script files, since they are used for the Linux-Docker machine.

Build an example project.
```
> cd ~/embedded/workspace/demo_gpio/
> make
```
There should be a file in elf demo_gpio now.

Start breadboard.
```
> cd ~/embedded
> bin/breadboard.sh conf/sevensegment.json
```

Use a further shell and run 
```
> cd ~/embedded/
> bin/hifive.sh workspace/demo_gpio/demo_gpio
```

Finally, run a gdb (after adding to your path the bin of the riscv64-unknown-elf-gcc toolchain)
```
> riscv64-unknown-elf-gdb
> target remote:5005
> c
```
Now we should see the virtual breadboard running. Quit with q in the virtual breadboard window.

11. Finally, we can set up Eclipse if we like to. Here is how to with macOS. 

>Make a new project in Eclipse with *Makefile Project with Existing Code" and select a project in our workspace. Toolchain choose RISC-V. Create a build target for the project with the same name as the project but change to *make*. Now you can build the project. 

>In order to debug, we have to start a virtual prototyp. This can be done with external tools in Eclipse. We will use  scripts which we include as external tools as follows:

>* Name: FlashRiscvVP, Location: ${workspace_loc}/../bin/riscv.sh, Working Directory: ${workspace_loc}/../, Arguments: workspace/${project_name}/${project_name}

>* Name: FlashHiFiveVP Location: /usr/bin/script, Working Directory: ${workspace_loc}/../, Arguments: -Fq /dev/null /bin/sh -c 'bin/hifive.sh workspace${project_path}/${project_name}'

>* Name: RunBreadboard, Location: /usr/bin/script, Working Directory: ${workspace_loc}/../,  Arguments:  -Fq /dev/null /bin/sh -c '${workspace_loc}/../bin/breadboard.sh conf/sevensegment.json'

>* Name: KillHiFiveVP, Location: ${workspace_loc}/../bin/kill-vp.sh

>Note: adapt the scripts if necessary.

With Windows there are a few problems with the tty consoles, so a different way has to be chosen here.
> Make a new project in Eclipse with *Makefile Project with Existing Code" and select a project in our workspace. Toolchain choose RISC-V. Create a build target for the project with the same name as the project but change to *make*. Now you can build the project.

>In order to debug, we have to start a virtual prototyp. This cannot be done with external tools in Eclipse, since the internal Eclipse terminal has problems with tty connections. We will use a combination of the eclipse internal docker tool and the eclipse TP terminal, which is included in the CDT installation:

>* Create a Docker Deamon connection via Docker tooling perspective: New Docker Connection -> Name "Local Docker" -> TCP Connection: http://localhost:2375. Check with ping. If it is not working, tick the "Expose daemon on tcp://localhost:2375 without TLS" optionm in your Docker settings.

>* Crate a Launch Configuration for Breadboard Docker: 

> > Create Launch Configuration -> Run-|Run Docker Image

>> Name "RunBreadboard"

>> image "Breadboard:latest"

>> Containername hifive1

>> Command: wp-breadboard -c conf/sevensegment.json

>> Tick Options: -i, -t, --rm. 

>> Under Volumes add:

>>> Container path: /home/embedded/shared Mount a host: C:\Users\...\embedded  

>>> Container path: /tmp/.X11-unix, Mount a host: /tmp/.X11-unix

>> Under Ports add: Container port: 5005, type: tcp, Host Port: 5005

> Now you can start the breadboard docker container from eclipse.

> The scripts must still be used for the other modules. However, these can be used from the TM Terminal in Eclipse.

Alternatively, cygwin with the packages (make and xinit) can be used for make and the xserver




## Debug a project

Create debug configuration for the project as follows. Choose C/C++ Remote Application and set Project to the project name and C/C++ Application to the project name. Set Using GDB (DSF) Manual Remote Debugging. In the Debugger tab, set GDB debugger to riscv64-unknown-elf-gdb (located in ~/embedded/riscv64-unknown-elf-gcc/bin). and Connection to Host localhost with Port number: 5005.

Done. Compile with the Build Target, Select the current project. For a RISC-V project, run the external tool FlashRiscvVP; for a HiFive-Project start a breadboard with RunBreadboard, virtually flash with FlashHiFiveVP. In both cases, start the debug configuration and continue. If something goes wrong, terminate the process with KillHiFiveVP. 

