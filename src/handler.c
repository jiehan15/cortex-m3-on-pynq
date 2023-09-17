
#include "handler.h"

#define ERROR_CODE_ADDR (uint32*)0x20100000

uint32 __number_of_ticks;

void Default_Handler()
{
    *(ERROR_CODE_ADDR) = 0x1;
    return;
}

void HardFault_Handler()
{
    *(ERROR_CODE_ADDR) = 0x2;
    return;
}

void BusFault_Handler()
{
    *(ERROR_CODE_ADDR) = 0x4;
    return;
}

void SystemTicker_Handler()
{
    __number_of_ticks++;
    return ;
}
