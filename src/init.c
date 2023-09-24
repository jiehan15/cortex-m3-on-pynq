
#include "init.h"
#include "libs/types.h"
#include "libs/lib.h"
#include "libs/addresses.h"

static void __init__led(void)
{
    uint32* led = (uint32*)M3_GPIO_0_LED;
    *led = 0x0;
}

void __init__()
{
    /* System ticker */
    __number_of_ticks = 0;

    /* LEDs */
    __init__led();
}
