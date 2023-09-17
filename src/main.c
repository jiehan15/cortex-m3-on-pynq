
#include "types.h"

uint32 num_1 = 0xdeadbeef;
uint32 num_2 = 0xdeadc0fe;

#define TICKS   10000000

SECTION_ITCM int fast_function()
{
    uint32* led = (uint32*)0x40010000;

    uint32 current_tick = 0;
    while (1)
    {
        if (current_tick < TICKS)
        {
            current_tick++;
        }
        else
        {
            *led += 1;
            current_tick = 0;
        }
    }

    return 0;
}

int main()
{
    uint32* addr = (uint32*)0x20100004;
    *addr = num_2;

    __number_of_ticks = 0;

    fast_function();
    return 0;
}
