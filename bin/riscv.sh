#!/bin/bash
export PATH=/usr/local/bin:$PATH
echo "start risc-vp"
echo $@ 
docker run --name hifive1 --rm  -p 5005:5005 -v ~/embedded:/home/embedded/shared breadboard riscv-vp --debug-mode $@ 
