/* Introduce ----------------------------------------- *
	DAC_输出直流电压
 ----------------------------------------------------- */
/* Include ------------------------------------------- */
#include "BSP_LWX_DC.h"
/* User Define --------------------------------------- */
/* User Variable ------------------------------------- */
/* User Extern --------------------------------------- */
/* User Function ------------------------------------- */
void DC1_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitType;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//使能DAC时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//下拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化

	 DAC_InitType.DAC_Trigger=DAC_Trigger_Software;	//不使用触发功能 TEN1=0
	 DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//不使用波形发生
	 DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//屏蔽、幅值设置
	DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;	//DAC1输出缓存关闭 BOFF1=1
	DAC_Init(DAC_Channel_1,&DAC_InitType);	 //初始化DAC通道1

	 DAC_SoftwareTriggerCmd(DAC_Channel_1,ENABLE);
	 DAC_Cmd(DAC_Channel_1, ENABLE);  //使能DAC通道1
}
void DC2_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitType;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//使能DAC时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//下拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化

	 DAC_InitType.DAC_Trigger=DAC_Trigger_Software;	//不使用触发功能 TEN1=0
	 DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//不使用波形发生
	 DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//屏蔽、幅值设置
	DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;	//DAC1输出缓存关闭 BOFF1=1
	DAC_Init(DAC_Channel_2,&DAC_InitType);	 //初始化DAC通道1

	 DAC_SoftwareTriggerCmd(DAC_Channel_2,ENABLE);
	 DAC_Cmd(DAC_Channel_2, ENABLE);  //使能DAC通道1
}


void DC12_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitType;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//使能DAC时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//下拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化

	 DAC_InitType.DAC_Trigger=DAC_Trigger_Software;	//不使用触发功能 TEN1=0
	 DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//不使用波形发生
	 DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//屏蔽、幅值设置
	 DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;	//DAC1输出缓存关闭 BOFF1=1
	 DAC_Init(DAC_Channel_1,&DAC_InitType);	 //初始化DAC通道1
         
	 DAC_InitType.DAC_Trigger=DAC_Trigger_Software;	//不使用触发功能 TEN1=0
	 DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//不使用波形发生
	 DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//屏蔽、幅值设置
	 DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;	//DAC1输出缓存关闭 BOFF1=1
	 DAC_Init(DAC_Channel_2,&DAC_InitType);	 //初始化DAC通道1
         
	 DAC_SoftwareTriggerCmd(DAC_Channel_1,ENABLE);
	 DAC_Cmd(DAC_Channel_1, ENABLE);  //使能DAC通道1
	 DAC_SoftwareTriggerCmd(DAC_Channel_2,ENABLE);
	 DAC_Cmd(DAC_Channel_2, ENABLE);  //使能DAC通道1
}
void DC1_Set(uint16_t Voltage)
{
	DAC_SetChannel1Data(DAC_Align_12b_R, Voltage*4095/3300);
	DAC_SoftwareTriggerCmd(DAC_Channel_1,ENABLE);
}
void DC2_Set(uint16_t Voltage)
{
	DAC_SetChannel2Data(DAC_Align_12b_R, Voltage*4095/3300);
	DAC_SoftwareTriggerCmd(DAC_Channel_2,ENABLE);
}
void DC12_Set(uint16_t Voltage1,uint16_t Voltage2)
{
	DAC_SetChannel1Data(DAC_Align_12b_R, Voltage1*4095/3300);
	DAC_SetChannel2Data(DAC_Align_12b_R, Voltage2*4095/3300);
	DAC_SoftwareTriggerCmd(DAC_Channel_2,ENABLE);
	DAC_SoftwareTriggerCmd(DAC_Channel_1,ENABLE);
}
