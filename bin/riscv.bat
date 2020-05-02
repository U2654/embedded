@ECHO OFF
echo "start risc-vp"
echo %1
docker run --name hifive1 --rm  -p 5005:5005 -v ~/embedded:/home/embedded/shared breadboard riscv-vp --debug-mode %1
PAUSE