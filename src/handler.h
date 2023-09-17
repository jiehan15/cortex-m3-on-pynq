
#ifndef __HANDLER_H
#define __HANDLER_H

#include "types.h"

void Default_Handler(void);
void HardFault_Handler(void);
void BusFault_Handler(void);
void SystemTicker_Handler(void);

#endif
