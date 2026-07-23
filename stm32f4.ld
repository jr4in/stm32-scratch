__STACK_SIZE = 0x400;


MEMORY
{
  ROM  (rx): ORIGIN = 0x08000000, LENGTH = 1M
  SRAM (rw): ORIGIN = 0x20000000, LENGTH = 128K
  /* CCM (rw): ORIGIN = 0x10000000, LENGTH = 192K */
  BSRAM (rw): ORIGIN = 0x08000000, LENGTH = 4K
}

ENTRY(Reset_Handler)

SECTIONS
{
  .vectors (READONLY) :
  {
    KEEP(*(.vectors))
  } > ROM
  .text :
  {
    *(.text)
    *(.rodata)
  } > ROM

  .data : 
  {
    PROVIDE(__data_start_lma__ = LOADADDR(.data));
    PROVIDE(__data_start_vma__ = .);
    *(.data)
    PROVIDE(__data_end_vma__ = .);
  } > SRAM AT> ROM

  .bss (NOLOAD):
  {
    PROVIDE(__bss_start__ = .);
    *(.bss)
    PROVIDE(__bss_end__ = .);
  } > SRAM

  .stack (ORIGIN(SRAM) + LENGTH(SRAM) - __STACK_SIZE) (NOLOAD) :
  {
    PROVIDE(__STACK = .);
    PROVIDE(__STACK_TOP = ORIGIN(SRAM) + LENGTH(SRAM));
  } > SRAM

  /DISCARD/ : 
  {
    *(.comment)
    *(.ARM.attributes)
  }
}


