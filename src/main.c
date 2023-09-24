
#include "libs/types.h"
#include "libs/addresses.h"
#include "libs/lib.h"
#include "init.h"

uint32 num_1 = 0xdeadbeef;
uint32 num_2 = 0xdeadc0fe;

#define TICKS   2500000

SECTION_ITCM int fast_function()
{
    uint32* led = (uint32*)M3_GPIO_0_LED;

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

static void __halt(uint32 result_code)
{
    uint32* addr = (uint32*)0x20100004;
    *addr = result_code;
    while (1) {};
}

int main()
{
    __init__();

    uint32 iters = fast_function();

    uint32* test_2 = malloc(1024);

    uint32* addr = (uint32*)0x20100100;
    *addr = (uint32)test_2;

    free(test_2);
    test_2 = malloc(768);

    addr = (uint32*)0x20100200;
    *addr = (uint32)test_2;

    uint32 dummy[8] = {
        1, 2, 3, 4, 5, 6, 7, 0x114514
    };

    memcpy(test_2, dummy, sizeof(uint32)*8);
    memset((test_2 + 8), 0xff, 4*sizeof(uint32));

    uint32* test_1 = malloc(8*sizeof(uint32));
    uint32* test_3 = malloc(8*sizeof(uint32));
    memcpy(test_3, dummy, sizeof(uint32)*8);
    memset(test_1, 0xfe, 8*sizeof(uint32));

    memcpy((test_2 + 16), test_3, sizeof(uint32)*8);
    memcpy((test_2 + 32), test_1, sizeof(uint32)*8);

    /* Stop here until reset by outside */
    __halt(iters);
    return 0;
}
