#include "system_init.h"
#include <stdint.h>
#include "stdbool.h"

extern uint32_t ui32SysClock;

// SysTick_Handler interrupt
void SysTick_Handler(void)
{   
	
}

void sys_init()
{
    ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                      SYSCTL_OSC_MAIN |
                                      SYSCTL_USE_PLL |
                                      SYSCTL_CFG_VCO_320), 120000000);
		SysTickIntRegister(SysTick_Handler);
	  SysTickIntEnable();
    SysTickEnable();
}

