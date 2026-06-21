/* Introduce ----------------------------------------- *
	多路ADC采集
	A0->CH0		
	A1->CH1		
	A2->CH2		
	A3->CH3		
	A4->CH4		
 ----------------------------------------------------- */
/* Include ------------------------------------------- */
#include "BSP_LWX_MULTI_ADC.h"
/* User Temp Include --------------------------------- */
/* LWX BSP Driver Lib -------------------------------- */
/* User Define --------------------------------------- */
/* User Variable ------------------------------------- */
/* User Extern --------------------------------------- */
/* User Function ------------------------------------- */
uint16_t Get_AD1(uint8_t ADC1_Channel)   
{
	  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ADC1_Channel, 1, ADC_SampleTime_480Cycles );	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
  
	ADC_SoftwareStartConv(ADC1);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}
uint16_t Get_AD1_Average(uint8_t ADC1_Channel,uint8_t Times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<Times;t++)
	{
		temp_val+=Get_AD1(ADC1_Channel);
	}
	return temp_val/Times;
} 
uint16_t Get_AD2(uint8_t ADC2_Channel)   
{
	  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC2, ADC2_Channel, 1, ADC_SampleTime_480Cycles );	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
  
	ADC_SoftwareStartConv(ADC2);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC2);	//返回最近一次ADC1规则组的转换结果
}
uint16_t Get_AD2_Average(uint8_t ADC2_Channel,uint8_t Times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<Times;t++)
	{
		temp_val+=Get_AD2(ADC2_Channel);
	}
	return temp_val/Times;
} 
uint16_t Get_AD3(uint8_t ADC3_Channel)   
{
	  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC3, ADC3_Channel, 1, ADC_SampleTime_480Cycles );	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
  
	ADC_SoftwareStartConv(ADC3);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC3);	//返回最近一次ADC1规则组的转换结果
}
uint16_t Get_AD3_Average(uint8_t ADC3_Channel,uint8_t Times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<Times;t++)
	{
		temp_val+=Get_AD3(ADC3_Channel);
	}
	return temp_val/Times;
} 
/* Main ---------------------------------------------- */
void BSP_MULTI_ADC1_Init(void)//PA0->CH0 PA1->CH1 PA2->CH2 //已开启
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //使能ADC1时钟

	//先初始化ADC1通道5 IO口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//不带上下拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化  
 
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1复位
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//复位结束	 
 
	//*******ADC普通配置*********//
	ADC_CommonInitStructure.ADC_Mode 			= ADC_Mode_Independent;//独立模式
	ADC_CommonInitStructure.ADC_TwoSamplingDelay 		= ADC_TwoSamplingDelay_5Cycles;//两个采样阶段之间的延迟5个时钟
	ADC_CommonInitStructure.ADC_DMAAccessMode 		= ADC_DMAAccessMode_Disabled; //DMA失能   //直接采集
	ADC_CommonInitStructure.ADC_Prescaler 			= ADC_Prescaler_Div4;//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz 
	ADC_CommonInit(&ADC_CommonInitStructure);//初始化
	//*******ADC配置**********//
	ADC_InitStructure.ADC_Resolution 			= ADC_Resolution_12b;//12位模式
	ADC_InitStructure.ADC_ScanConvMode 			= DISABLE;//非扫描模式	
	ADC_InitStructure.ADC_ContinuousConvMode 		= DISABLE;//关闭连续转换
	ADC_InitStructure.ADC_ExternalTrigConvEdge		= ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
	ADC_InitStructure.ADC_DataAlign				= ADC_DataAlign_Right;//右对齐	
	ADC_InitStructure.ADC_NbrOfConversion 			= 1;//1个转换在规则序列中 也就是只转换规则序列1  在扫描模式下可以非1
	ADC_Init(ADC1, &ADC_InitStructure);//ADC初始化
	
	ADC_Cmd(ADC1, ENABLE);//开启AD转换器	
}
void BSP_MULTI_ADC2_Init(void)//PB0——CH8 PB1——CH9 //已开启
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE); //使能ADC1时钟

	//先初始化ADC1通道5 IO口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//不带上下拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化  
 
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2,ENABLE);	  //ADC1复位
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2,DISABLE);	//复位结束	 
 
	//*******ADC普通配置*********//
	ADC_CommonInitStructure.ADC_Mode 			= ADC_Mode_Independent;//独立模式
	ADC_CommonInitStructure.ADC_TwoSamplingDelay 		= ADC_TwoSamplingDelay_5Cycles;//两个采样阶段之间的延迟5个时钟
	ADC_CommonInitStructure.ADC_DMAAccessMode 		= ADC_DMAAccessMode_Disabled; //DMA失能   //直接采集
	ADC_CommonInitStructure.ADC_Prescaler 			= ADC_Prescaler_Div4;//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz 
	ADC_CommonInit(&ADC_CommonInitStructure);//初始化
	//*******ADC配置**********//
	ADC_InitStructure.ADC_Resolution 			= ADC_Resolution_12b;//12位模式
	ADC_InitStructure.ADC_ScanConvMode 			= DISABLE;//非扫描模式	
	ADC_InitStructure.ADC_ContinuousConvMode 		= DISABLE;//关闭连续转换
	ADC_InitStructure.ADC_ExternalTrigConvEdge		= ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
	ADC_InitStructure.ADC_DataAlign				= ADC_DataAlign_Right;//右对齐	
	ADC_InitStructure.ADC_NbrOfConversion 			= 1;//1个转换在规则序列中 也就是只转换规则序列1  在扫描模式下可以非1
	ADC_Init(ADC2, &ADC_InitStructure);//ADC初始化
	
	ADC_Cmd(ADC2, ENABLE);//开启AD转换器	
}
void BSP_MULTI_ADC3_Init(void)//CH11_[PC1] CH12_[PC2] CH13_[PC3] //已开启
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE); //使能ADC1时钟

	//先初始化ADC1通道5 IO口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_1 | GPIO_Pin_3;//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//不带上下拉
	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化  
 
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,ENABLE);	  //ADC1复位
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,DISABLE);	//复位结束	 
 
	//*******ADC普通配置*********//
	ADC_CommonInitStructure.ADC_Mode 			= ADC_Mode_Independent;//独立模式
	ADC_CommonInitStructure.ADC_TwoSamplingDelay 		= ADC_TwoSamplingDelay_5Cycles;//两个采样阶段之间的延迟5个时钟
	ADC_CommonInitStructure.ADC_DMAAccessMode 		= ADC_DMAAccessMode_Disabled; //DMA失能   //直接采集
	ADC_CommonInitStructure.ADC_Prescaler 			= ADC_Prescaler_Div4;//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz 
	ADC_CommonInit(&ADC_CommonInitStructure);//初始化
	//*******ADC配置**********//
	ADC_InitStructure.ADC_Resolution 			= ADC_Resolution_12b;//12位模式
	ADC_InitStructure.ADC_ScanConvMode 			= DISABLE;//非扫描模式	
	ADC_InitStructure.ADC_ContinuousConvMode 		= DISABLE;//关闭连续转换
	ADC_InitStructure.ADC_ExternalTrigConvEdge		= ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
	ADC_InitStructure.ADC_DataAlign				= ADC_DataAlign_Right;//右对齐	
	ADC_InitStructure.ADC_NbrOfConversion 			= 1;//1个转换在规则序列中 也就是只转换规则序列1  在扫描模式下可以非1
	ADC_Init(ADC3, &ADC_InitStructure);//ADC初始化
	
	ADC_Cmd(ADC3, ENABLE);//开启AD转换器	
}

