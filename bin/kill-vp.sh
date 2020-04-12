#!/bin/bash
export PATH=/usr/local/bin:$PATH
docker exec hifive1 bash -c 'pidof hifive-vp | xargs kill'
docker exec hifive1 bash -c 'pidof risc-vp | xargs kill'

