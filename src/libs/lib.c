
#include "lib.h"
#include "lib_private.h"

SECTION_ITCM void *memcpy(void *dest, const void *src, size_t n)
{
    char *__dest = (char*)dest;
    char *__src = (char*)src;

    for (size_t i = 0; i < n; i++)
    {
        *(__dest + i) = *(__src + i);
    }
    return dest;
}

SECTION_ITCM void *memset(void *str, int c, size_t n)
{
    unsigned char *__str = (unsigned char*)str;
    for (size_t i = 0; i < n; i++)
    {
        *(__str + i) = (unsigned char)c;
    }

    return str;
}

SECTION_ITCM void *malloc(size_t size)
{
    __malloc_mem_block_node_t* new_node = __malloc_get_node(size);

    if (!new_node)
    {
        return NULL;
    }

    return (void*)new_node->mptr;
}

SECTION_ITCM void free(void* ptr)
{
    /* TODO: Deal with mem framentation */
    __malloc_mem_block_node_t* node =
        (__malloc_mem_block_node_t*)container_of(ptr, __malloc_mem_block_node_t, mptr);

    node->bitmap = node->bitmap & (~__HEAP_NODE_IN_USE_BM);
}
