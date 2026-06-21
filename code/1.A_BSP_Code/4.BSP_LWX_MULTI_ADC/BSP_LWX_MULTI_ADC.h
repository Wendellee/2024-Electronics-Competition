/* Introduce ----------------------------------------- *
	多路ADC采集
 ----------------------------------------------------- */
#ifndef __BSP_LWX_MULTI_ADC_H
#define __BSP_LWX_MULTI_ADC_H
/* Include ------------------------------------------- */
#include "stm32f4xx.h"
/* User Temp Include --------------------------------- */
/* LWX BSP Driver Lib -------------------------------- */
/* User Define --------------------------------------- */
/* User Variable ------------------------------------- */
/* User Extern --------------------------------------- */
/* User Function ------------------------------------- */
void BSP_MULTI_ADC1_Init(void);//PA0->CH0 PA1->CH1 PA2->CH2 //已开启
void BSP_MULTI_ADC2_Init(void);//PB0——CH8 PB1——CH9 //已开启
void BSP_MULTI_ADC3_Init(void);//CH11_[PC1] CH12_[PC2] CH13_[PC3] //已开启
uint16_t Get_AD1(uint8_t ADC1_Channel);
uint16_t Get_AD1_Average(uint8_t ADC1_Channel,uint8_t Times);
uint16_t Get_AD2(uint8_t ADC2_Channel)  ;
uint16_t Get_AD2_Average(uint8_t ADC2_Channel,uint8_t Times);
uint16_t Get_AD3(uint8_t ADC3_Channel) ;
uint16_t Get_AD3_Average(uint8_t ADC3_Channel,uint8_t Times);
/* Main ---------------------------------------------- 
		BSP_MULTI_ADC1_Init();
		BSP_MULTI_ADC2_Init();
		BSP_MULTI_ADC3_Init();
		printf("A0.val=%d\xff\xff\xff",Get_AD1(ADC_Channel_0)*3300/4095);
		printf("A1.val=%d\xff\xff\xff",Get_AD1(ADC_Channel_1)*3300/4095);
		printf("A2.val=%d\xff\xff\xff",Get_AD1(ADC_Channel_2)*3300/4095);
		printf("B0.val=%d\xff\xff\xff",Get_AD2(ADC_Channel_8)*3300/4095);
		printf("B1.val=%d\xff\xff\xff",Get_AD2(ADC_Channel_9)*3300/4095);
		printf("C1.val=%d\xff\xff\xff",Get_AD3(ADC_Channel_11)*3300/4095);
		printf("C2.val=%d\xff\xff\xff",Get_AD3(ADC_Channel_12)*3300/4095);
		printf("C3.val=%d\xff\xff\xff",Get_AD3(ADC_Channel_13)*3300/4095);
		
		Serial_Printf(USART1,"A0.val=%d\r\n",Get_AD1(ADC_Channel_0)*3300/4095);
		Serial_Printf(USART1,"A1.val=%d\r\n",Get_AD1(ADC_Channel_1)*3300/4095);
		Serial_Printf(USART1,"A2.val=%d\r\n",Get_AD1(ADC_Channel_2)*3300/4095);
		Serial_Printf(USART1,"B0.val=%d\r\n",Get_AD2(ADC_Channel_8)*3300/4095);
		Serial_Printf(USART1,"B1.val=%d\r\n",Get_AD2(ADC_Channel_9)*3300/4095);
		Serial_Printf(USART1,"C1.val=%d\r\n",Get_AD3(ADC_Channel_11)*3300/4095);
		Serial_Printf(USART1,"C2.val=%d\r\n",Get_AD3(ADC_Channel_12)*3300/4095);
		Serial_Printf(USART1,"C3.val=%d\r\n",Get_AD3(ADC_Channel_13)*3300/4095);
		delay_ms(500);
//		Serial_Printf(USART1,"A0.val=%d\xff\xff\xff",Get_AD1(ADC_Channel_0)*3300/4095);
//		Serial_Printf(USART1,"A1.val=%d\xff\xff\xff",Get_AD1(ADC_Channel_1)*3300/4095);
//		Serial_Printf(USART1,"A2.val=%d\xff\xff\xff",Get_AD1(ADC_Channel_2)*3300/4095);
//		Serial_Printf(USART1,"B0.val=%d\xff\xff\xff",Get_AD2(ADC_Channel_8)*3300/4095);
//		Serial_Printf(USART1,"B1.val=%d\xff\xff\xff",Get_AD2(ADC_Channel_9)*3300/4095);
//		Serial_Printf(USART1,"C1.val=%d\xff\xff\xff",Get_AD3(ADC_Channel_11)*3300/4095);
//		Serial_Printf(USART1,"C2.val=%d\xff\xff\xff",Get_AD3(ADC_Channel_12)*3300/4095);
//		Serial_Printf(USART1,"C3.val=%d\xff\xff\xff",Get_AD3(ADC_Channel_13)*3300/4095);
*/













#endif

