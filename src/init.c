
#include "init.h"
#include "libs/types.h"
#include "libs/lib.h"
#include "libs/addresses.h"

void __init__()
{
    __number_of_ticks = 0;

#ifdef DEBUG_LINK_SCRIPT_ENABLE
#define ARR_SZ 5

    uint32 arr[ARR_SZ] = {
        _text, _etext, __text_sz, __external_sram_start, __external_sram_end
    };
    memcpy((uint32*)EXTERNAL_SARM_C_DEBUG_ADDR, arr, sizeof(uint32) * ARR_SZ);
#endif /* #ifdef DEBUG_LINK_SCRIPT_ENABLE */
}
