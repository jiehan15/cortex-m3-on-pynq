
#ifndef __TYPES_H
#define __TYPES_H

#define SECTION_BOOTROM __attribute__((section (".bootrom")))
#define SECTION_ITCM    __attribute__((section (".itcm")))
#define SECTION_DTCM    __attribute__((section (".dtcm")))

#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})

#include <stdint.h>
#include <stddef.h>

typedef uint32_t uint32;
typedef uint8_t uint8;

/* src/handler.c */
extern uint32 __number_of_ticks;

#endif
