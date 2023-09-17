
#ifndef __TYPES_H
#define __TYPES_H

#define SECTION_BOOTROM __attribute__((section (".bootrom")))
#define SECTION_ITCM    __attribute__((section (".itcm")))

#include <stdint.h>
#include <stddef.h>

typedef uint32_t uint32;

/* src/handler.c */
extern uint32 __number_of_ticks;

void *memcpy(void *dest, const void *src, size_t n);

#endif
