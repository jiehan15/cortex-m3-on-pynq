
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
    __tcm_section_offset = .;

    .bootrom :
    {
        _bootrom = .;
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        *(.bootrom)
        _ebootrom = .;
    } > external_rom AT>external_rom

    __bootrom_sz = _ebootrom - _bootrom;
    __tcm_section_offset += __bootrom_sz;

    .text :
    {
        . = ALIGN(4);
        _text = .;
        *(.text*)
        *(.rodata*)
        _etext = .;
    } > external_rom AT>external_rom

    __text_sz = _etext - _text;
    __tcm_section_offset += __text_sz;

    /* Why?
     *  00000160 <__fast_function_veneer>:
     *  160:	f85f f000 	ldr.w	pc, [pc]	@ 164 <__fast_function_veneer+0x4>
     *  164:	10000001 	andne	r0, r0, r1  <-- looks like this line is considered in text section
     */
    __tcm_section_offset += 4;

    /* .data and .bss at external sram */
    __external_sram_start = __tcm_section_offset;

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
        . = ALIGN(4);
        _bss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > external_sram AT>external_rom

    __bss_sz = _ebss - _bss;
    __external_sram_end = __external_sram_start + __data_sz + __bss_sz;
    __tcm_section_offset += __bss_sz;

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
