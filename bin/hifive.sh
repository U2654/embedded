#!/bin/bash
export PATH=/usr/local/bin:$PATH
echo "start hifive-vp"
echo $@ 
docker exec -it hifive1 hifive-vp --debug-mode $@
