#!/bin/bash
echo $@
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
script -qefc "redv-vp --debug-mode "$@"" /dev/null
elif [[ "$OSTYPE" == "darwin"* ]]; then
script -Fq /dev/null redv-vp --debug-mode "$@"
fi
