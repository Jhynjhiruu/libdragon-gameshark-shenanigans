OUTPUT_FORMAT ("elf32-bigmips", "elf32-bigmips", "elf32-littlemips")
OUTPUT_ARCH (mips)
EXTERN (_start)
ENTRY (_start)

PHDRS {
    main PT_LOAD AT ( 0x80200000 );
}

SECTIONS {
    .text 0x80200000 : {
        . = ALIGN(16);
        *(.text.*)
        . = ALIGN(16);
    } :main

    .rodata : {
        . = ALIGN(16);
        *(.rodata.*)
        . = ALIGN(16);
    }

    .data : {
        . = ALIGN(16);
        *(.data.*)
        . = ALIGN(16);
    }

    .bss (NOLOAD) : {
        . = ALIGN(16);
        *(.bss.*)
        . = ALIGN(16);
    }
}
