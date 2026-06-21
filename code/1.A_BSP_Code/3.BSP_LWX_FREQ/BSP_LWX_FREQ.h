/* Introduce ----------------------------------------- *
	¶¨Ê±Æ÷²âÆµÂÊ:
	PIN:PA1
	0-20Mhz
 ----------------------------------------------------- */
#ifndef __BSP_LWX_FREQ_H
#define __BSP_LWX_FREQ_H
/* Include ------------------------------------------- */
#include "stm32f4xx.h"
/* User Temp Include --------------------------------- */
/* LWX BSP Driver Lib -------------------------------- */
/* User Define --------------------------------------- */
/* User Variable ------------------------------------- */
/* User Extern --------------------------------------- */ 
extern float CNT1;
/* User Function ------------------------------------- */
void TIM4_Int_Init(void);
void TIM5_CH1_Cap(void);
/* Main ----------------------------------------------
	TIM4_Int_Init();
	TIM5_CH1_Cap();


	printf("%f\n",CNT1);
*/








#endif

