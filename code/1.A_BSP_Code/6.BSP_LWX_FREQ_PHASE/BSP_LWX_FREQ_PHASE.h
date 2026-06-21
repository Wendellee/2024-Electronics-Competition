/* Introduce ----------------------------------------- *
	
 ----------------------------------------------------- */
#ifndef __BSP_LWX_FREQ_PHASE_H
#define __BSP_LWX_FREQ_PHASE_H
/* Include ------------------------------------------- */
#include "stm32f4xx.h"
/* User Temp Include --------------------------------- */
/* LWX BSP Driver Lib -------------------------------- */
/* User Define --------------------------------------- */
/* User Variable ------------------------------------- */
/* User Extern --------------------------------------- */
/* Phase ------- */
extern double  CH3_Count;				//全局变量，用于计数
extern double  CH4_Count;				//全局变量，用于计数
/* Frequency --- */
extern uint16_t cnt;
extern float CNT;
/* User Function ------------------------------------- */
void TIM2_Init(void);
void Phase_Init(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void TIM4_Int_Init(void);
void TIM5_CH1_Cap(void);
void TIM5_IRQHandler(void);
void TIM4_IRQHandler(void);
/* Main ---------------------------------------------- 
	// Frequency ---
	TIM4_Int_Init();
	TIM5_CH1_Cap(); 
	// Phase -------
	TIM2_Init();
	Phase_Init();
		
		printf("%f\r,%lf\r\n",CNT*2/2,CH4_Count*CNT/84000000*360.0 + CNT/10000 - 1);   //      *CNT/84000000*360.0           *100000/84000000*360.0
		
		TIM_SetAutoreload(TIM2,(uint32_t)84000000/(CNT-1));//即时修改arr 



*/











#endif
