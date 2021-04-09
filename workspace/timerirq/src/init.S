.section .text
.global _init

_init:
# set up global pointer 
.option push
.option norelax
    la gp, __global_pointer$
.option pop

# init stack pointer
    la sp, _sp

# data to ram
data_load:
    la t0, _lmadata
    la t1, _databegin
    la t2, _dataend 
    beq t0, t1, data_end # lma  == data , don't copy
    ble t2, t1, data_end # end <=  begin, don't copy
data_loop:
    lw a0, 0(t0)
    addi t0, t0, 4
    sw a0, 0(t1)
    addi t1, t1, 4
    bltu t1, t2, data_loop
data_end:
        
# clear .bss
bss_clear:
    la t0, _bssbegin
    la t1, _bssend
    ble t1, t0, bss_end
bss_loop:
    sw x0, 0(t0)
    addi t0, t0, 4
    bltu t0, t1, bss_loop
bss_end:

# goto main 
    call main

gotlost:
    j gotlost    
