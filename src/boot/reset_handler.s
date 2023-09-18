.syntax unified
.globl  ResetISR
.section .bootrom, "xa"
.thumb_func
ResetISR:
    // copy .data to DTCM
    .extern __dtcm_section_offset
    .extern _edtcm_abs
    ldr r0, =__dtcm_section_offset      // start address of data section in external rom
    ldr r1, =_edtcm_abs     // end address of data section in external rom
    ldr r2, =0x20000000     // start address of DTCM
    ldr r4, =0x0 // counter
copy_loop_dtcm:
    add r4, r4, #1
    ldr r3, [r0], #4
    str r3, [r2], #4
    cmp r0, r1
    blt copy_loop_dtcm
    // debug...
    ldr r3, =0x20100020
    ldr r0, =__dtcm_section_offset
    str r0, [r3], #4
    str r1, [r3], #4
    str r2, [r3], #4
    str r4, [r3], #4

    // copy code to itcm
    .extern __itcm_section_offset
    .extern __eitcm_abs
    ldr r0, =__itcm_section_offset
    ldr r1, =__eitcm_abs
    ldr r2, =0x10000000  // start address of ITCM
    ldr r4, =0x0 // counter
copy_loop_itcm:
    add r4, r4, #1
    ldr r3, [r0], #4
    str r3, [r2], #4
    cmp r0, r1
    blt copy_loop_itcm
    // debug...
    ldr r3, =0x20100040
    ldr r0, =__itcm_section_offset
    str r0, [r3], #4
    str r1, [r3], #4
    str r2, [r3], #4
    str r4, [r3], #4

    // copy code to .data and .bss
    .extern __external_sram_start
    .extern __external_sram_end
    ldr r0, =__external_sram_start
    ldr r1, =__external_sram_end
    ldr r2, =0x20102000  // start address of external sram
    ldr r4, =0x0 // counter
copy_loop_data_bss:
    add r4, r4, #1
    ldr r3, [r0], #4
    str r3, [r2], #4
    cmp r0, r1
    blt copy_loop_data_bss
    // debug...
    ldr r3, =0x20100060
    ldr r0, =__external_sram_start
    str r0, [r3], #4
    str r1, [r3], #4
    str r2, [r3], #4
    str r4, [r3], #4
    // go to main
    .extern main
    bl main
