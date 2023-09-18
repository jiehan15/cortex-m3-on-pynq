
#include "lib.h"

SECTION_ITCM void *memcpy(void *dest, const void *src, size_t n)
{
    uint8 *__dest = (uint8*)dest;
    uint8 *__src = (uint8*)src;

    for (size_t i = 0; i < n; i++)
    {
        *(__dest + i) = *(__src + i);
    }
    return NULL;
}
