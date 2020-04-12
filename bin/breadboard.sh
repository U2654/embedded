#!/bin/bash
export PATH=/usr/local/bin:$PATH
docker run --name hifive1 -ti --rm -p 5005:5005 -v ~/embedded:/home/embedded/shared -v /tmp/.X11-unix:/tmp/.X11-unix breadboard vp-breadboard -c $@

