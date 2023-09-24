
#ifndef __LIB_H
#define __LIB_H

#include "types.h"

void *memcpy(void *dest, const void *src, size_t n);

void *memset(void *str, int c, size_t n);

void *malloc(size_t size);
void free(void* ptr);

#endif /* #ifndef __LIB_H */
