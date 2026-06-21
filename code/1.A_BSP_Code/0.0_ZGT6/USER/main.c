/* Introduce ----------------------------------------- *
	ZGT6初始化代码
	包含DSP库
	可用延时操作
	包含SRAM
	三路FFT采集分析
 ----------------------------------------------------- */
/* Include ------------------------------------------- */
#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "sram.h"
#include "FFTInc.h"
/* User Temp Include --------------------------------- */
#include "LED.h"
/* LWX BSP Driver Lib -------------------------------- */
#include "BSP_LWX_AD.h"
#include "DSP_LWX_FFT.h"
#include "VET6_BSP_USART3.h"
/* User Define --------------------------------------- */
/* User Variable ------------------------------------- */
/* User Extern --------------------------------------- */
/* User Function ------------------------------------- */
/* Main ---------------------------------------------- */
int main(void)
{
	//Serial_Printf(USART3,"");
	delay_init(168);
	uart_init(115200);
	FSMC_SRAM_Init();
	uart3_init(115200);
	LED_Init();
	
	BSP_ADC1_All_SETUP();
	BSP_ADC2_All_SETUP();
  while(1)
	{
		
		//LED_Shine(100);
		        
		//printf("cle s1.id,0\xff\xff\xff");
		while(1)
		{
			Serial_Printf(USART3,"cle s1.id,0\xff\xff\xff");
			Serial_Printf(USART3,"cle s1.id,1\xff\xff\xff");
			cfft_f32_mag0();
			cfft_f32_mag1();
			/* 串口打印求解的幅频 */
			for(int i=0; i<2048/2; i+=4)
			{			
					//printf("%d\r,%f\r\n",i, s[i].real/4095);
				//向曲线s0的通道0传输1个数据,add指令不支持跨页面
				//printf("add s1.id,0,%d\xff\xff\xff",(int)(s[i].real/4095));
				Serial_Printf(USART3,"add s1.id,0,%d\xff\xff\xff",(int)(s0[i].real/4095));
				Serial_Printf(USART3,"add s1.id,1,%d\xff\xff\xff",(int)(s1[i].real/4095));
			}
		}
	}
}




