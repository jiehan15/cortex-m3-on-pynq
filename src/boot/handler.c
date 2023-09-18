
#include "handler.h"
#include "libs/addresses.h"

SECTION_DTCM uint32 __number_of_ticks;

#define SET_ERR_CODE(code)  (*((uint32*)EXTERNAL_SARM_ERROR_CODE_ADDR) = code)

void Default_Handler()
{
    SET_ERR_CODE(0x1);
    return;
}

void HardFault_Handler()
{
    SET_ERR_CODE(0x2);
    return;
}

void BusFault_Handler()
{
    SET_ERR_CODE(0x4);
    return;
}

SECTION_ITCM void SystemTicker_Handler()
{
    __number_of_ticks++;
    return ;
}
