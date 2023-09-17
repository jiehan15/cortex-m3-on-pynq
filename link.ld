
MEMORY
{
    external_rom    : ORIGIN = 0x00000000, LENGTH = 256*1024
    itcm            : ORIGIN = 0x10000000, LENGTH = 8*1024
    dtcm            : ORIGIN = 0x20000000, LENGTH = 32*1024
    external_sram   : ORIGIN = 0x20102000, LENGTH = 240*1024 /* First 8KB as debug */
}

ENTRY(ResetISR)

SECTIONS
{
    __data_section_offset = .;
    __itcm_section_offset = .;

    .bootrom :
    {
        _bootrom = .;
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        *(.bootrom)
        _ebootrom = .;
    } > external_rom AT>external_rom

    __bootrom_sz = _ebootrom - _bootrom;
    __data_section_offset += __bootrom_sz;

    .text :
    {
        . = ALIGN(4);
        _text = .;
        *(.text*)
        *(.rodata*)
        _etext = .;
    } > external_rom AT>external_rom

    __text_sz = _etext - _text;
    __data_section_offset += __text_sz;

    .bss :
    {
        . = ALIGN(4);
        _bss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > external_sram AT>external_rom

    __bss_sz = _ebss - _bss;
    __data_section_offset += __bss_sz;

    __itcm_section_offset = __data_section_offset;

    .itcm :
    {
        _itcm = .;
        . = ALIGN(4);
        *(.itcm*)
        _eitcm = .;
    } > itcm AT>external_rom

    __itcm_sz = _eitcm - _itcm;
    __eitcm_abs = __itcm_section_offset + __itcm_sz;
    __data_section_offset += __itcm_sz;

    .data :
    {
        _data = .;
        . = ALIGN(4);
        *(.data*)
        _edata = .;
    } > dtcm AT>external_rom

    _edata_abs = __data_section_offset + _edata - _data;
}
