
/*
external_rom: 128 KB
ITCM: 32KB
DTCM: 32KB
external_sram: 256 KB
*/

MEMORY
{
    external_rom                : ORIGIN = 0x00000000, LENGTH = 128*1024
    itcm                        : ORIGIN = 0x10000000, LENGTH = 32*1024

    /* DTCM */
    dtcm                        : ORIGIN = 0x20000000, LENGTH = 16*1024
    dtcm_heap                   : ORIGIN = 0x20004000, LENGTH = 8*1024
    dtcm_stack                  : ORIGIN = 0x20006000, LENGTH = 8*1024

    /* external_sram */
    external_sram_debug         : ORIGIN = 0x20100000, LENGTH = 8*1024   /* First 8KB as debug */
    external_sram               : ORIGIN = 0x20102000, LENGTH = 128*1024
    external_sram_heap          : ORIGIN = 0x20122000, LENGTH = 88*1024
    external_sram_dtcm_dump     : ORIGIN = 0x20138000, LENGTH = 32*1024
}

ENTRY(ResetISR)

SECTIONS
{
    .bootrom :
    {
        _bootrom = .;
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        *(.bootrom)
        _ebootrom = .;
    } > external_rom AT>external_rom

    __bootrom_sz = _ebootrom - _bootrom;

    .text :
    {
        . = ALIGN(4);
        _text = .;
        *(.text*)
        *(.rodata*)
        _etext = .;
    } > external_rom AT>external_rom

    /* Enternal SRAM Start */
    __external_sram_start = .;
    __tcm_section_offset = .;

    /* .data and .bss at external sram */
    .data :
    {
        _data = .;
        . = ALIGN(4);
        *(.data*)
        _edata = .;
    } > external_sram AT>external_rom
    __data_sz = _edata - _data;
    __tcm_section_offset += __data_sz;

    .bss :
    {
        _bss = .;
        . = ALIGN(4);
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > external_sram AT>external_rom
    __bss_sz = _ebss - _bss;
    __tcm_section_offset += __bss_sz;
    __external_sram_end = __external_sram_start + __data_sz + __bss_sz;

    /* ITCM and DTCM */
    __itcm_section_offset = __tcm_section_offset;

    .itcm :
    {
        _itcm = .;
        . = ALIGN(4);
        *(.itcm*)
        _eitcm = .;
    } > itcm AT>external_rom

    __itcm_sz = _eitcm - _itcm;
    __eitcm_abs = __itcm_section_offset + __itcm_sz;

    __dtcm_section_offset = __eitcm_abs;

    .dtcm :
    {
        _dtcm = .;
        . = ALIGN(4);
        *(.dtcm*)
        _edtcm = .;
    } > dtcm AT>external_rom

    __dtcm_sz = _edtcm - _dtcm;
    _edtcm_abs = __dtcm_section_offset + __dtcm_sz;
}
