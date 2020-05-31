OUTPUT_ARCH( "riscv" )

ENTRY( main )

MEMORY
{
  flash (rxai!w) : ORIGIN = 0x20400000, LENGTH = 512M
  ram (wxa!ri) : ORIGIN = 0x80000000, LENGTH = 16K
}

SECTIONS
{
  __stack_size = DEFINED(__stack_size) ? __stack_size : 1K;

  .text           :
  {
    *(.text .text.*)
  } >flash 

  .data          :
  {
    *(.data .data.*)
    . = ALIGN(8);
    PROVIDE( __global_pointer$ = . + 0x800 );
  } >ram AT>flash

  .bss            :
  {
    *(.sbss*)
    *(.bss .bss.*)
    *(COMMON)
    . = ALIGN(4);
  } >ram AT>ram 

  . = ALIGN(8);
  
   .stack ORIGIN(ram) + LENGTH(ram) - __stack_size :
  {
    PROVIDE( _heap_end = . );
    . = __stack_size;
    PROVIDE( _sp = . );
  } >ram AT>ram 
}
