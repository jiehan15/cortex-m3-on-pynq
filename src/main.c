
#include "libs/types.h"
#include "init.h"

uint32 num_1 = 0xdeadbeef;
uint32 num_2 = 0xdeadc0fe;

#define TICKS   2500000

SECTION_ITCM int fast_function()
{
    uint32* led = (uint32*)0x40010000;

    uint32 current_tick = 0;
    uint32 led_swtch_num = 0;
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
            led_swtch_num++;
        }

        if (led_swtch_num == 32)
        {
            return led_swtch_num;
        }
    }

    return 0;
}

int main()
{
    __init__();

    uint32 iters = fast_function();

    uint32* addr = (uint32*)0x20100004;
    *addr = iters;

    while (1) {};

    return 0;
}
