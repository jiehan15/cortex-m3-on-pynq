
#include "lib_private.h"

#define __HEAP_POOL_DTCM_START              0x20004000
#define __HEAP_POOL_EXTERNAL_SRAM_START     0x20122000

#define __HEAP_NODE_IN_USE(node)                ((node)->bitmap & __HEAP_NODE_IN_USE_BM)

SECTION_DTCM __malloc_mem_block_list_t __malloc_mem_block_list_dtcm = {
    .head = NULL, .tail = NULL, .count = 0,
    /* Maybe less useable due to mem fragmentation */
    .heap_available = __HEAP_POOL_DTCM_MAX, /* 8KB */
};

SECTION_DTCM __malloc_mem_block_list_t __malloc_mem_block_list_exsram = {
    .head = NULL, .tail = NULL, .count = 0,
    /* Maybe less useable due to mem fragmentation */
    .heap_available = __HEAP_POOL_EXTERNAL_SRAM_MAX, /* 88KB */
};

SECTION_ITCM static __malloc_mem_block_node_t* __malloc_get_node_from_list(
    size_t size, __malloc_mem_block_list_t *list)
{
    if (size > (list->heap_available + sizeof(__malloc_mem_block_node_t)))
    {
        if (list == &__malloc_mem_block_list_dtcm)
        {
            /* No space from DTCM, see if avaliable from external sram */
            return __malloc_get_node_from_list(size, &__malloc_mem_block_list_exsram);
        }
        else
        {
            return NULL;
        }
    }

    if (!list->head)
    {
        list->heap_available -= size + sizeof(__malloc_mem_block_node_t);

        if (list == &__malloc_mem_block_list_dtcm)
        {
            list->head = (__malloc_mem_block_node_t*)__HEAP_POOL_DTCM_START;
        }
        else
        {
            list->head = (__malloc_mem_block_node_t*)__HEAP_POOL_EXTERNAL_SRAM_START;
        }

        list->head->next = NULL;
        list->head->bitmap = 0;
        return list->head;
    }

    __malloc_mem_block_node_t* current = list->head;
    __malloc_mem_block_node_t* tail = NULL;
    while (current)
    {
        /* TODO: use tail from list */
        if (!current->next)
        {
            tail = current;
        }

        if (__HEAP_NODE_IN_USE(current))
        {
            current = current->next;
        }
        else
        {
            /* current node is not in use, see if we can fit it this node... */
            if (size <= current->sz)
            {
                current->bitmap |= __HEAP_NODE_REUSE_BM;
                return current;
            }
        }
    }

    /* no existing suitable node and we have enough space, allocate a new node */
    __malloc_mem_block_node_t* new_node =
        (__malloc_mem_block_node_t*)(((char*)tail) + tail->sz + sizeof(__malloc_mem_block_node_t));

    tail->next = new_node;
    new_node->next = NULL;
    new_node->bitmap = 0;
    list->heap_available -= size + sizeof(__malloc_mem_block_node_t);

    return new_node;
}

SECTION_ITCM __malloc_mem_block_node_t* __malloc_get_node(size_t size)
{
    __malloc_mem_block_node_t* new_node = NULL;
    if (size > __MALLOC_SZ_USE_EXTERNAL_MEMPOOL)
    {
        new_node = __malloc_get_node_from_list(size, &__malloc_mem_block_list_exsram);
    }
    else
    {
        /* Will try to allocate at DTCM. But may use external SRAM */
        new_node = __malloc_get_node_from_list(size, &__malloc_mem_block_list_dtcm);
    }

    if (!new_node)
    {
        return NULL;
    }

    new_node->sz = size;
    new_node->bitmap |= __HEAP_NODE_IN_USE_BM;
}
