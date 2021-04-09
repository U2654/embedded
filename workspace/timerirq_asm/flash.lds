OUTPUT_ARCH( "riscv" )

ENTRY( main )

MEMORY
{
  flash (irx!wa) : ORIGIN = 0x20010000, LENGTH = 512M
  ram (arw!xi) : ORIGIN = 0x80000000, LENGTH = 16K
}


SECTIONS
{
  .text           :
  {
    *(.text .text.*)
  } >flash 

}
