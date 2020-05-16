OUTPUT_ARCH( "riscv" )

ENTRY( main )

MEMORY
{
  flash (rxai!w) : ORIGIN = 0x20000000, LENGTH = 512M
  ram (wxa!ri) : ORIGIN = 0x80000000, LENGTH = 16K
}


SECTIONS
{
  .text           :
  {
    *(.text .text.*)
  } >flash 

}
