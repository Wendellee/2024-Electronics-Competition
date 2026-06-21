#ifndef __BSP_LWX_DC_H
#define __BSP_LWX_DC_H
/* Introduce ----------------------------------------- *
	DAC_输出直流电压
	
 ----------------------------------------------------- */
/* Include ------------------------------------------- */
#include "stm32f4xx.h"
/* User Temp Include --------------------------------- */
/* LWX BSP Driver Lib -------------------------------- */
/* User Define --------------------------------------- */
/* User Variable ------------------------------------- */
/* User Extern --------------------------------------- */
/* User Function ------------------------------------- */
void DC1_Init(void);
void DC2_Init(void);
void DC12_Init(void);
void DC1_Set(uint16_t Voltage);
void DC2_Set(uint16_t Voltage);
void DC12_Set(uint16_t Voltage1,uint16_t Voltage2);
/* Main ---------------------------------------------- 
	DC12_Init();
	DC12_Set(1000,2000);
	
	DC1_Init();
	DC2_Init();
	DC1_Set();
	DC2_Set();
*/








#endif
