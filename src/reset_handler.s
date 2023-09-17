.syntax unified
.globl  ResetISR
.section .bootrom, "xa"
.thumb_func
ResetISR:
    // copy .data to DTCM
    .extern __data_section_offset
    .extern _edata_abs
    ldr r0, =__data_section_offset      // start address of data section in external rom
    ldr r1, =_edata_abs     // end address of data section in external rom
    ldr r2, =0x20000000     // start address of DTCM
    ldr r4, =0x0 // counter
copy_loop_data:
    add r4, r4, #1
    ldr r3, [r0], #4
    str r3, [r2], #4
    cmp r0, r1
    blt copy_loop_data
    // debug...
    ldr r3, =0x20100008
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
copy_loop_code:
    add r4, r4, #1
    ldr r3, [r0], #4
    str r3, [r2], #4
    cmp r0, r1
    blt copy_loop_code
    // debug...
    ldr r3, =0x20100040
    str r0, [r3], #4
    str r1, [r3], #4
    str r2, [r3], #4
    str r4, [r3], #4
    // go to __boot_entry
    .extern main
    bl main
