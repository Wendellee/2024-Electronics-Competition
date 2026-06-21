#ifndef __LED_H
#define __LED_H
/* Introduce ----------------------------------------- *
	PC0->LED0
 ----------------------------------------------------- */
/* Include ------------------------------------------- */
#include "stm32f4xx.h"                  // Device header
#include "delay.h"
/* User Temp Include --------------------------------- */
/* LWX BSP Driver Lib -------------------------------- */
/* User Define --------------------------------------- */
/* User Variable ------------------------------------- */
/* User Extern --------------------------------------- */
/* User Function ------------------------------------- */

void LED_Init(void);//PC0->LED0

void LED_Shine(uint16_t time);



#endif


