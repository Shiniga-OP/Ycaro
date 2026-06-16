SECTIONS
{
    . = 0x0;
    .entrada : { *(.entrada) }
    .text : { *(.text) }
    .data : { *(.data) }
    .bss : { *(.bss) }
    .rodata : { *(.rodata) *(.rodata.*) }
}