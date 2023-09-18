
#ifndef __INIT_H
#define __INIT_H

#include "libs/types.h"

void __init__(void);

#ifdef DEBUG_LINK_SCRIPT_ENABLE
extern const uint32 _text;
extern const uint32 _etext;
extern const uint32 __text_sz;

extern const uint32 __external_sram_start;
extern const uint32 __external_sram_end;
#endif /* #ifdef DEBUG_LINK_SCRIPT_ENABLE */

#endif
