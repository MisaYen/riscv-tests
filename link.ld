OUTPUT_ARCH( "riscv" )
ENTRY(_start)

MEMORY
{
    code_ram   (rx!rw) : ORIGIN = 0x00000000, LENGTH = 0x100000
    data_ram   (rw!x)  : ORIGIN = 0x00400000, LENGTH = 0x100000
}

SECTIONS
{
  .text :
  {
    *(.text.init)
    . = ALIGN(0x1000);
    *(.text)

  } > code_ram

  . = 0x00800000;
  .tohost : { *(.tohost) }

  .data :
  {
    *(.data)
    *(.bss)
    . = ALIGN(0x1000);

  } > data_ram

  _end = .;
}


/*
//SECTIONS
//{
//  . = 0x00000000;
//  .text.init : { *(.text.init) }
//  . = ALIGN(0x1000);
//  .text : { *(.text) }
//  . = ALIGN(0x1000);
//  . = 0x00800000;
//  .tohost : { *(.tohost) }
//  . = 0x01000000;
//  .data : { *(.data) }
//  .bss : { *(.bss) }
//  . = ALIGN(0x1000);
//  _end = .;
//}
*/
