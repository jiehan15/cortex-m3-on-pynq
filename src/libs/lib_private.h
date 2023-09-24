
#ifndef __LIB_PRIVATE_H
#define __LIB_PRIVATE_H

#include "types.h"

/**
 *  If the size asked for is larger than the __MALLOC_SZ_USE_EXTERNAL_MEMPOOL, we will use heap
 *  pool from external heap space.
 */
#define __MALLOC_SZ_USE_EXTERNAL_MEMPOOL    (256)

/** whether this node is in use */
#define __HEAP_NODE_IN_USE_BM                   0x00000001
#define __HEAP_NODE_REUSE_BM                    0x00000002

#define __HEAP_POOL_DTCM_MAX                8192
#define __HEAP_POOL_EXTERNAL_SRAM_MAX       90112

typedef struct __malloc_mem_block_node_t
{
    /* must be first member */
    struct __malloc_mem_block_node_t* next;
    uint32 bitmap;
    /* size of mem block */
    size_t sz;
    /* mem block */
    char mptr[];
} __malloc_mem_block_node_t;

typedef struct __malloc_mem_block_list_t
{
    __malloc_mem_block_node_t* head;
    __malloc_mem_block_node_t* tail; /** unused for now */
    uint32 count;
    size_t heap_available; /** Maybe less useable due to mem fragmentation */
} __malloc_mem_block_list_t;

/* src/libs/lib_malloc.c */
__malloc_mem_block_node_t* __malloc_get_node(size_t size);

#endif /* #ifndef __LIB_PRIVATE_H */
