#!/bin/bash
echo $@
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
script -qefc "hifive-vp --debug-mode "$@"" /dev/null
elif [[ "$OSTYPE" == "darwin"* ]]; then
script -Fq /dev/null hifive-vp --debug-mode "$@"
fi
