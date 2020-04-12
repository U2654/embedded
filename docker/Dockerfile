FROM ubuntu:18.04

RUN apt-get update && apt-get install -y xterm build-essential qt5-default nano gedit sudo git wget cmake

RUN export uid=1000 gid=1000 && \
    mkdir -p /home/embedded && \
    echo "embedded:x:${uid}:${gid}:Embedded,,,:/home/embedded:/bin/bash" >> /etc/passwd && \
    echo "embedded:x:${uid}:" >> /etc/group && \
    echo "embedded ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/embedded && \
    chmod 0440 /etc/sudoers.d/embedded && \
    chown ${uid}:${gid} -R /home/embedded

USER embedded
ENV HOME /home/embedded

RUN cd ~ && \
    sudo apt-get install -y autoconf automake autotools-dev curl libmpc-dev libmpfr-dev libgmp-dev gawk bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev libboost-all-dev && \
    git clone --depth 1 https://github.com/riscv/riscv-gnu-toolchain.git && \
    cd riscv-gnu-toolchain/ && \
    git submodule update --init --recursive

RUN cd ~/riscv-gnu-toolchain/ && \
    ./configure --prefix=$(pwd)/../riscv-gnu-toolchain-dist-rv32imac-ilp32 --with-arch=rv32imac --with-abi=ilp32 && \
    make && \
    cd ~ && \
    git clone --depth 1 https://github.com/U2654/riscv-vp.git
    
RUN cd ~/riscv-vp && \
    git submodule update --init vp/src/core/common/gdb-mc/libgdb/mpc && \
    cd vp/dependencies/ && \
    ./build_systemc_233.sh && \
    ./build_softfloat.sh

RUN cd ~/riscv-vp/vp/ && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make install

RUN cd ~ && \
    git clone --depth 1 https://github.com/agra-uni-bremen/riscv-freertos.git

ENV PATH /home/embedded/riscv-gnu-toolchain-dist-rv32imac-ilp32/bin:/home/embedded/riscv-vp/vp/build/bin:$PATH

RUN cd ~/riscv-vp/env/hifive/vp-breadboard/ && \
    cmake . && \
    make

ENV PATH /home/embedded/riscv-vp/env/hifive/vp-breadboard:$PATH
ENV DISPLAY host.docker.internal:0
WORKDIR /home/embedded/shared

CMD ["vp-breadboard"]
