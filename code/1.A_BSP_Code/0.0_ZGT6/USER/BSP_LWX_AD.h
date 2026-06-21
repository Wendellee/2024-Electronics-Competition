#ifndef BSP_LWX_AD
#define BSP_LWX_AD
/* Introduce ----------------------------------------- *
	三路ADC 用定时器触发 DMA搬用 
	ADC1	PA1	BSP_G_AD_A
	ADC2	PB0	BSP_G_AD_B
	ADC3	PC1	BSP_G_AD_C
 ----------------------------------------------------- */
/* Include ------------------------------------------- */
#include "stm32f4xx.h"                  // Device header
/* User Temp Include --------------------------------- */
/* LWX BSP Driver Lib -------------------------------- */
/* User Define --------------------------------------- */
#define DATA 2048
/* User Variable ------------------------------------- */
/* User Extern --------------------------------------- */
extern uint16_t BSP_G_AD_A[DATA];
extern uint16_t BSP_G_AD_B[DATA];
extern uint16_t BSP_G_AD_C[DATA];
/* User Function ------------------------------------- */
//PLAN A  Fs = 1Mhz ContinueConversion 10000 Point
void BSP_ADC1_GPIO_Init(void);
void BSP_TIM2_Init(void);
void BSP_ADC1_Init(void);
void BSP_ADC1_DMA_Init(uint16_t BUFFER_SIZE);
void BSP_ADC1_All_SETUP(void);

//PLAN B  Fs = 1Mhz ContinueConversion 10000 Point
void BSP_ADC2_GPIO_Init(void);
//void BSP_TIM2_Init(void);
void BSP_ADC2_Init(void);
void BSP_ADC2_DMA_Init(uint16_t BUFFER_SIZE);
void BSP_ADC2_All_SETUP(void);

//PLAN C  Fs = 1Mhz ContinueConversion 10000 Point
void BSP_ADC3_GPIO_Init(void);
//void BSP_TIM2_Init(void);
void BSP_ADC3_Init(void);
void BSP_ADC3_DMA_Init(uint16_t BUFFER_SIZE);
void BSP_ADC3_All_SETUP(void);

//PLAN D 
//-------------------------	
#define INPUT_POINT  32768
void ADC_GPIO_Init(void);
void TIM3_Init(uint16_t ARR,uint16_t PSC);
void ADC1_Init(void);
void ADC_DMA_Init(uint16_t *ARRAY,uint16_t POINT);

void ADC_All_Init(uint16_t ARR,uint16_t PSC,uint16_t *ARRAY,uint16_t POINT);
//--------------------------	
//2024.7.20修改


#endif


