OUTPUT_ARCH( "riscv" )
ENTRY(_start)

SECTIONS
{
  . = 0x00000000;
  .text.init : { *(.text.init) }
  . = ALIGN(0x1000);
  .text : { *(.text) }
  /* . = ALIGN(0x1000); */
  . = 0x00800000;
  .tohost : { *(.tohost) }
  . = 0x00400000;
  .data : { *(.data) }
  .bss : { *(.bss) }
  . = ALIGN(0x1000);
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
//  .tohost : { *(.tohost) }
//  . = 0x01000000;
//  .data : { *(.data) }
//  .bss : { *(.bss) }
//  . = ALIGN(0x1000);
//  _end = .;
//}
*/
