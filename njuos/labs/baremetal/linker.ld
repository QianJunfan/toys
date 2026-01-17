ENTRY(_start)

SECTIONS
{
    . = 0x100000;
    .text : {
        *(.text)
    }
    .data : {
        *(.data)
    }
    .bss : {
        *(.bss)
        *(COMMON)
    }
    . = ALIGN(8);
    . = . + 0x1000;
    stack_top = .;
}

