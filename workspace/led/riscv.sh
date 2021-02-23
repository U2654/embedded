#!/bin/bash
echo $@
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
script -qefc "/home/debian/riscv/riscv-vp/vp/build/bin/hifive-vp --debug-mode "$@"" /dev/null
elif [[ "$OSTYPE" == "darwin"* ]]; then
script -Fq /dev/null hifive-vp --debug-mode "$@"
fi
