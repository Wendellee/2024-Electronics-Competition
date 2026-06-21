/* Introduce ----------------------------------------- *
	
 ----------------------------------------------------- */
/* Include ------------------------------------------- */
#include "BSP_LWX_AD.h"
/* User Temp Include --------------------------------- */
/* LWX BSP Driver Lib -------------------------------- */
/* User Define --------------------------------------- */
/* User Variable ------------------------------------- */
/* User Extern --------------------------------------- */
/* User Function ------------------------------------- */
/* Main ---------------------------------------------- */
//-----BSP_Driver_Control_Unit----------------------	
#define BSP_AD1_PLAN_A        1
#define BSP_AD2_PLAN_B        1
#define BSP_AD3_PLAN_C        1
#define BSP_ZGT6_FILTER_CODE  0

#define DATA 2048

//---------------------------	

//PLAN A  Fs = 1Mhz ContinueConversion 10000 Point
#if  BSP_AD1_PLAN_A

uint16_t BSP_G_AD_A[DATA];//__attribute__((at(0X68000011)));
//Model Description 
//Very Well AD  One Can Real Time Require Waves
//              Two Wave Not Have Break Point

void BSP_ADC1_GPIO_Init(void)//GPIOA PA1  [TIM2_CH2]  TIM5_CH2
{
	GPIO_InitTypeDef GPIO_InitStructure;
		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM2);                     //打开引脚复用功能//
	GPIO_InitStructure.GPIO_Mode					=GPIO_Mode_AN;                //模拟输入//
	GPIO_InitStructure.GPIO_Pin					=GPIO_Pin_1;                  //PA0//
	GPIO_InitStructure.GPIO_PuPd					=GPIO_PuPd_NOPULL;            //不上拉//
	GPIO_InitStructure.GPIO_Speed					=GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void BSP_TIM2_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision		=TIM_CKD_DIV1;                     //不分频//
	TIM_TimeBaseInitStructure.TIM_CounterMode		=TIM_CounterMode_Up;               //向上计数//
	TIM_TimeBaseInitStructure.TIM_Period			=84-1;                             //ARR//
	TIM_TimeBaseInitStructure.TIM_Prescaler			=1-1;                              //PSC//
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;                       
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	TIM_SelectOutputTrigger(TIM2,TIM_TRGOSource_Update);
	TIM_Cmd(TIM2,ENABLE);
	
}
void BSP_ADC1_Init(void)
{	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	//*******ADC普通配置*********//
	ADC_CommonInitStructure.ADC_DMAAccessMode		=ADC_DMAAccessMode_Disabled;                  //ADC_DMA失能，多重ADC模式下势能//     
	ADC_CommonInitStructure.ADC_Mode				=ADC_Mode_Independent;                        //ADC独立模式//
	ADC_CommonInitStructure.ADC_Prescaler			=ADC_Prescaler_Div2;                          //2分频//
	ADC_CommonInitStructure.ADC_TwoSamplingDelay	=ADC_TwoSamplingDelay_10Cycles;               //两次转换之间的时间差//   10
	
	ADC_CommonInit(&ADC_CommonInitStructure);
	
	//*******ADC配置**********//
	ADC_InitStructure.ADC_ContinuousConvMode		=DISABLE;                                      //单次转换//
	ADC_InitStructure.ADC_DataAlign					=ADC_DataAlign_Right;                          //数据右对齐//
	ADC_InitStructure.ADC_ExternalTrigConv			=ADC_ExternalTrigConv_T2_TRGO;                 //TIM2的更新(溢出)事件//
	ADC_InitStructure.ADC_ExternalTrigConvEdge		=ADC_ExternalTrigConvEdge_Rising;              //极性：上升沿//
	ADC_InitStructure.ADC_NbrOfConversion			=1;                                            //通道数：1//
	ADC_InitStructure.ADC_Resolution				=ADC_Resolution_12b;                           //数据12位//
	ADC_InitStructure.ADC_ScanConvMode				=DISABLE;                                      //不扫描//
	        
	ADC_Init(ADC1,&ADC_InitStructure);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_15Cycles); 	      //规则组通道配置//    
	ADC_DMARequestAfterLastTransferCmd(ADC1,ENABLE);
	ADC_DMACmd(ADC1,ENABLE); 
	ADC_Cmd(ADC1,ENABLE);
}

void BSP_ADC1_DMA_Init(uint16_t BUFFER_SIZE)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);
	
	//DMA_DeInit(DMA2_Stream0);//or DMA2_Stream4
	DMA_InitStructure.DMA_BufferSize				=BUFFER_SIZE;                                //数组长度//
	DMA_InitStructure.DMA_Channel					=DMA_Channel_0;                              //通道0//
	DMA_InitStructure.DMA_DIR						=DMA_DIR_PeripheralToMemory;                 //传输方向：外设到内存//
	DMA_InitStructure.DMA_FIFOMode					=DMA_FIFOMode_Disable;                       //FIFO失能//
	DMA_InitStructure.DMA_FIFOThreshold				=DMA_FIFOThreshold_HalfFull;                 //FIFO传输的长度//        
	DMA_InitStructure.DMA_Memory0BaseAddr			=(uint32_t)BSP_G_AD_A;                        //内存地址//
 	DMA_InitStructure.DMA_MemoryBurst				=DMA_MemoryBurst_Single;                     //  
	DMA_InitStructure.DMA_MemoryDataSize			=DMA_MemoryDataSize_HalfWord;                //传输长度：半字//
	DMA_InitStructure.DMA_MemoryInc					=DMA_MemoryInc_Enable;                       //内存地址自增//
	DMA_InitStructure.DMA_Mode						=DMA_Mode_Circular;                            //单次搬运//
	DMA_InitStructure.DMA_PeripheralBaseAddr		=((uint32_t)&(ADC1->DR));                    //外设地址//
	DMA_InitStructure.DMA_PeripheralBurst			=DMA_PeripheralBurst_Single;                 //
	DMA_InitStructure.DMA_PeripheralDataSize		=DMA_PeripheralDataSize_HalfWord;            //半字//
	DMA_InitStructure.DMA_PeripheralInc				=DMA_PeripheralInc_Disable;                  //外设地址自增失能//
	DMA_InitStructure.DMA_Priority					=DMA_Priority_High;                          //优先级高//
	
	DMA_Init(DMA2_Stream0,&DMA_InitStructure);
	DMA_Cmd(DMA2_Stream0,ENABLE);
	
}


void BSP_ADC1_All_SETUP(void)
{
	BSP_ADC1_GPIO_Init();
	BSP_TIM2_Init();
	BSP_ADC1_Init();
	BSP_ADC1_DMA_Init(DATA);
}


#endif

//----------------------------	
//PLAN B  Fs = 1Mhz ContinueConversion 10000 Point
#if  BSP_AD2_PLAN_B


uint16_t BSP_G_AD_B[DATA];//__attribute__((at(0X68000000)));
//Model Description 
//Very Well AD  One Can Real Time Require Waves
//              Two Wave Not Have Break Point

void BSP_ADC2_GPIO_Init(void)//GPIOB PB0  [TIM2_CH2]  TIM5_CH2
{
	GPIO_InitTypeDef GPIO_InitStructure;
		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM2);                     //打开引脚复用功能//
	GPIO_InitStructure.GPIO_Mode					=GPIO_Mode_AN;                //模拟输入//
	GPIO_InitStructure.GPIO_Pin					=GPIO_Pin_0;                  //PA0//
	GPIO_InitStructure.GPIO_PuPd					=GPIO_PuPd_NOPULL;            //不上拉//
	GPIO_InitStructure.GPIO_Speed					=GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

//void BSP_TIM2_Init(void)
//{
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
//	
//	TIM_TimeBaseInitStructure.TIM_ClockDivision		=TIM_CKD_DIV1;                     //不分频//
//	TIM_TimeBaseInitStructure.TIM_CounterMode		=TIM_CounterMode_Up;               //向上计数//
//	TIM_TimeBaseInitStructure.TIM_Period			=84-1;                             //ARR//
//	TIM_TimeBaseInitStructure.TIM_Prescaler			=1-1;                              //PSC//
//	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;                       
//	
//	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
//	TIM_SelectOutputTrigger(TIM2,TIM_TRGOSource_Update);
//	TIM_Cmd(TIM2,ENABLE);
//	
//}
void BSP_ADC2_Init(void)
{	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE);
	//*******ADC普通配置*********//
	ADC_CommonInitStructure.ADC_DMAAccessMode		=ADC_DMAAccessMode_Disabled;                  //ADC_DMA失能，多重ADC模式下势能//     
	ADC_CommonInitStructure.ADC_Mode			=ADC_Mode_Independent;                        //ADC独立模式//
	ADC_CommonInitStructure.ADC_Prescaler			=ADC_Prescaler_Div2;                          //2分频//
	ADC_CommonInitStructure.ADC_TwoSamplingDelay		=ADC_TwoSamplingDelay_10Cycles;               //两次转换之间的时间差//   10
	
	ADC_CommonInit(&ADC_CommonInitStructure);
	
	//*******ADC配置**********//
	ADC_InitStructure.ADC_ContinuousConvMode			=DISABLE;                                      //单次转换//
	ADC_InitStructure.ADC_DataAlign					=ADC_DataAlign_Right;                          //数据右对齐//
	ADC_InitStructure.ADC_ExternalTrigConv				=ADC_ExternalTrigConv_T2_TRGO;                 //TIM2的更新(溢出)事件//
	ADC_InitStructure.ADC_ExternalTrigConvEdge			=ADC_ExternalTrigConvEdge_Rising;              //极性：上升沿//
	ADC_InitStructure.ADC_NbrOfConversion				=1;                                            //通道数：1//
	ADC_InitStructure.ADC_Resolution				=ADC_Resolution_12b;                           //数据12位//
	ADC_InitStructure.ADC_ScanConvMode				=DISABLE;                                      //不扫描//
	        
	ADC_Init(ADC2,&ADC_InitStructure);
	ADC_RegularChannelConfig(ADC2,ADC_Channel_8,1,ADC_SampleTime_15Cycles); 	      //规则组通道配置//    
	ADC_DMARequestAfterLastTransferCmd(ADC2,ENABLE);
	ADC_DMACmd(ADC2,ENABLE); 
	ADC_Cmd(ADC2,ENABLE);
}

void BSP_ADC2_DMA_Init(uint16_t BUFFER_SIZE)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);
	
	//DMA_DeInit(DMA2_Stream3);//or DMA2_Stream2
	DMA_InitStructure.DMA_BufferSize				=BUFFER_SIZE;                                //数组长度//
	DMA_InitStructure.DMA_Channel					=DMA_Channel_1;                              //通道0//
	DMA_InitStructure.DMA_DIR					=DMA_DIR_PeripheralToMemory;                 //传输方向：外设到内存//
	DMA_InitStructure.DMA_FIFOMode					=DMA_FIFOMode_Disable;                       //FIFO失能//
	DMA_InitStructure.DMA_FIFOThreshold				=DMA_FIFOThreshold_HalfFull;                 //FIFO传输的长度//        
	DMA_InitStructure.DMA_Memory0BaseAddr			 	=(uint32_t)BSP_G_AD_B;                        //内存地址//
 	DMA_InitStructure.DMA_MemoryBurst				=DMA_MemoryBurst_Single;                     //  
	DMA_InitStructure.DMA_MemoryDataSize				=DMA_MemoryDataSize_HalfWord;                //传输长度：半字//
	DMA_InitStructure.DMA_MemoryInc					=DMA_MemoryInc_Enable;                       //内存地址自增//
	DMA_InitStructure.DMA_Mode					=DMA_Mode_Circular;                            //单次搬运//
	DMA_InitStructure.DMA_PeripheralBaseAddr			=((uint32_t)&(ADC2->DR));                    //外设地址//
	DMA_InitStructure.DMA_PeripheralBurst				=DMA_PeripheralBurst_Single;                 //
	DMA_InitStructure.DMA_PeripheralDataSize			=DMA_PeripheralDataSize_HalfWord;            //半字//
	DMA_InitStructure.DMA_PeripheralInc				=DMA_PeripheralInc_Disable;                  //外设地址自增失能//
	DMA_InitStructure.DMA_Priority					=DMA_Priority_High;                          //优先级高//
	
	DMA_Init(DMA2_Stream2,&DMA_InitStructure);
	DMA_Cmd(DMA2_Stream2,ENABLE);
	
}


void BSP_ADC2_All_SETUP(void)
{
	BSP_ADC2_GPIO_Init();
	//BSP_TIM2_Init();
	BSP_ADC2_Init();
	BSP_ADC2_DMA_Init(DATA);
	
}


#endif

//----------------------------	
//PLAN C  Fs = 1Mhz ContinueConversion 10000 Point
#if  BSP_AD3_PLAN_C

//#define DATA 8192

uint16_t BSP_G_AD_C[DATA];//__attribute__((at(0X68000000)));
//Model Description 
//Very Well AD  One Can Real Time Require Waves
//              Two Wave Not Have Break Point

void BSP_ADC3_GPIO_Init(void)//GPIOC PC1  [TIM2_CH2]  TIM5_CH2
{
	GPIO_InitTypeDef GPIO_InitStructure;
		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource1,GPIO_AF_TIM2);                     //打开引脚复用功能//
	GPIO_InitStructure.GPIO_Mode					=GPIO_Mode_AN;                //模拟输入//
	GPIO_InitStructure.GPIO_Pin					=GPIO_Pin_1;                  //PA0//
	GPIO_InitStructure.GPIO_PuPd					=GPIO_PuPd_NOPULL;            //不上拉//
	GPIO_InitStructure.GPIO_Speed					=GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}

//void BSP_TIM2_Init(void)
//{
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
//	
//	TIM_TimeBaseInitStructure.TIM_ClockDivision		=TIM_CKD_DIV1;                     //不分频//
//	TIM_TimeBaseInitStructure.TIM_CounterMode		=TIM_CounterMode_Up;               //向上计数//
//	TIM_TimeBaseInitStructure.TIM_Period			=84-1;                             //ARR//
//	TIM_TimeBaseInitStructure.TIM_Prescaler			=1-1;                              //PSC//
//	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;                       
//	
//	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
//	TIM_SelectOutputTrigger(TIM2,TIM_TRGOSource_Update);
//	TIM_Cmd(TIM2,ENABLE);
//	
//}
void BSP_ADC3_Init(void)
{	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3,ENABLE);
	//*******ADC普通配置*********//
	ADC_CommonInitStructure.ADC_DMAAccessMode		=ADC_DMAAccessMode_Disabled;                  //ADC_DMA失能，多重ADC模式下势能//     
	ADC_CommonInitStructure.ADC_Mode			=ADC_Mode_Independent;                        //ADC独立模式//
	ADC_CommonInitStructure.ADC_Prescaler			=ADC_Prescaler_Div2;                          //2分频//
	ADC_CommonInitStructure.ADC_TwoSamplingDelay		=ADC_TwoSamplingDelay_10Cycles;               //两次转换之间的时间差//   10
	
	ADC_CommonInit(&ADC_CommonInitStructure);
	
	//*******ADC配置**********//
	ADC_InitStructure.ADC_ContinuousConvMode			=DISABLE;                                      //单次转换//
	ADC_InitStructure.ADC_DataAlign					=ADC_DataAlign_Right;                          //数据右对齐//
	ADC_InitStructure.ADC_ExternalTrigConv				=ADC_ExternalTrigConv_T2_TRGO;                 //TIM2的更新(溢出)事件//
	ADC_InitStructure.ADC_ExternalTrigConvEdge			=ADC_ExternalTrigConvEdge_Rising;              //极性：上升沿//
	ADC_InitStructure.ADC_NbrOfConversion				=1;                                            //通道数：1//
	ADC_InitStructure.ADC_Resolution				=ADC_Resolution_12b;                           //数据12位//
	ADC_InitStructure.ADC_ScanConvMode				=DISABLE;                                      //不扫描//
	        
	ADC_Init(ADC3,&ADC_InitStructure);
	ADC_RegularChannelConfig(ADC3,ADC_Channel_11,1,ADC_SampleTime_15Cycles); 	      //规则组通道配置//    
	ADC_DMARequestAfterLastTransferCmd(ADC3,ENABLE);
	ADC_DMACmd(ADC3,ENABLE); 
	ADC_Cmd(ADC3,ENABLE);
}

void BSP_ADC3_DMA_Init(uint16_t BUFFER_SIZE)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);
	
	//DMA_DeInit(DMA2_Stream1);//or DMA2_Stream0
	DMA_InitStructure.DMA_BufferSize				=BUFFER_SIZE;                                //数组长度//
	DMA_InitStructure.DMA_Channel					=DMA_Channel_2;                              //通道0//
	DMA_InitStructure.DMA_DIR					=DMA_DIR_PeripheralToMemory;                 //传输方向：外设到内存//
	DMA_InitStructure.DMA_FIFOMode					=DMA_FIFOMode_Disable;                       //FIFO失能//
	DMA_InitStructure.DMA_FIFOThreshold				=DMA_FIFOThreshold_HalfFull;                 //FIFO传输的长度//        
	DMA_InitStructure.DMA_Memory0BaseAddr			 	=(uint32_t)BSP_G_AD_C;                        //内存地址//
 	DMA_InitStructure.DMA_MemoryBurst				=DMA_MemoryBurst_Single;                     //  
	DMA_InitStructure.DMA_MemoryDataSize				=DMA_MemoryDataSize_HalfWord;                //传输长度：半字//
	DMA_InitStructure.DMA_MemoryInc					=DMA_MemoryInc_Enable;                       //内存地址自增//
	DMA_InitStructure.DMA_Mode					=DMA_Mode_Circular;                            //单次搬运//
	DMA_InitStructure.DMA_PeripheralBaseAddr			=((uint32_t)&(ADC3->DR));                    //外设地址//
	DMA_InitStructure.DMA_PeripheralBurst				=DMA_PeripheralBurst_Single;                 //
	DMA_InitStructure.DMA_PeripheralDataSize			=DMA_PeripheralDataSize_HalfWord;            //半字//
	DMA_InitStructure.DMA_PeripheralInc				=DMA_PeripheralInc_Disable;                  //外设地址自增失能//
	DMA_InitStructure.DMA_Priority					=DMA_Priority_High;                          //优先级高//
	
	DMA_Init(DMA2_Stream0,&DMA_InitStructure);
	DMA_Cmd(DMA2_Stream0,ENABLE);
	
}


void BSP_ADC3_All_SETUP(void)
{
	BSP_ADC3_GPIO_Init();
	BSP_TIM2_Init();
	BSP_ADC3_Init();
	BSP_ADC3_DMA_Init(DATA);
	
}


#endif

//-------------------------	
//PLAN D fs can change and array can select
#if BSP_ZGT6_FILTER_CODE

//uint16_t BEFORE_FILTER[INPUT_POINT]__attribute__((at(0X64000000)));

void ADC_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3);    //打开引脚复用功能//
	GPIO_InitStructure.GPIO_Mode				=GPIO_Mode_AN;               //模拟输入//
	GPIO_InitStructure.GPIO_Pin					=GPIO_Pin_0;                  //PB0//
	GPIO_InitStructure.GPIO_PuPd				=GPIO_PuPd_NOPULL;           //不上拉//
	GPIO_InitStructure.GPIO_Speed				=GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void TIM3_Init(uint16_t ARR,uint16_t PSC)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision	=TIM_CKD_DIV1;                 //不分频//
	TIM_TimeBaseInitStructure.TIM_CounterMode	=TIM_CounterMode_Up;             //向上计数//
	TIM_TimeBaseInitStructure.TIM_Period		=ARR-1;                             //ARR//84000000/409600-1;
	TIM_TimeBaseInitStructure.TIM_Prescaler		=PSC-1;                              //PSC//
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;                       
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	TIM_SelectOutputTrigger(TIM3,TIM_TRGOSource_Update);
	TIM_Cmd(TIM3,ENABLE);
}
void ADC1_Init(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	//*******ADC普通配置*********//
	ADC_CommonInitStructure.ADC_DMAAccessMode	=ADC_DMAAccessMode_Disabled;         //ADC_DMA失能，多重ADC模式下势能//     
	ADC_CommonInitStructure.ADC_Mode			=ADC_Mode_Independent;                        //ADC独立模式//
	ADC_CommonInitStructure.ADC_Prescaler		=ADC_Prescaler_Div2;                     //2分频//
	ADC_CommonInitStructure.ADC_TwoSamplingDelay=ADC_TwoSamplingDelay_10Cycles;    //两次转换之间的时间差//   10
	
	ADC_CommonInit(&ADC_CommonInitStructure);
	
	//*******ADC配置**********//
	ADC_InitStructure.ADC_ContinuousConvMode	=DISABLE;                             //单次转换//
	ADC_InitStructure.ADC_DataAlign				=ADC_DataAlign_Right;                          //数据右对齐//
	ADC_InitStructure.ADC_ExternalTrigConv		=ADC_ExternalTrigConv_T3_TRGO;          //TIM3的更新(溢出)事件//
	ADC_InitStructure.ADC_ExternalTrigConvEdge	=ADC_ExternalTrigConvEdge_Rising;   //极性：上升沿//
	ADC_InitStructure.ADC_NbrOfConversion		=1;                                      //通道数：1//
	ADC_InitStructure.ADC_Resolution			=ADC_Resolution_12b;                          //数据12位//
	ADC_InitStructure.ADC_ScanConvMode			=DISABLE;                                   //不扫描//
	        
	ADC_Init(ADC1,&ADC_InitStructure);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_8,1,ADC_SampleTime_15Cycles); 	      //规则组通道配置//    15
	ADC_DMARequestAfterLastTransferCmd(ADC1,ENABLE);
	ADC_DMACmd(ADC1,ENABLE); 
	ADC_Cmd(ADC1,ENABLE);
}

void ADC_DMA_Init(uint16_t *ARRAY,uint16_t POINT)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);
	
	DMA_DeInit(DMA2_Stream0);
	DMA_InitStructure.DMA_BufferSize			=POINT;                               //数组长度//
	DMA_InitStructure.DMA_Channel				=DMA_Channel_0;                              //通道0//
	DMA_InitStructure.DMA_DIR					=DMA_DIR_PeripheralToMemory;                     //传输方向：外设到内存//
	DMA_InitStructure.DMA_FIFOMode				=DMA_FIFOMode_Disable;                      //FIFO失能//
	DMA_InitStructure.DMA_FIFOThreshold			=DMA_FIFOThreshold_HalfFull;           //FIFO传输的长度//        
	DMA_InitStructure.DMA_Memory0BaseAddr		=(uint32_t)ARRAY;                 //内存地址//
 	DMA_InitStructure.DMA_MemoryBurst			=DMA_MemoryBurst_Single;                 //  
	DMA_InitStructure.DMA_MemoryDataSize		=DMA_MemoryDataSize_HalfWord;         //传输长度：半字//
	DMA_InitStructure.DMA_MemoryInc				=DMA_MemoryInc_Enable;                     //内存地址自增//
	DMA_InitStructure.DMA_Mode					=DMA_Mode_Circular;                               //循环搬运//
	DMA_InitStructure.DMA_PeripheralBaseAddr	=((uint32_t)&(ADC1->DR));         //外设地址//
	DMA_InitStructure.DMA_PeripheralBurst		=DMA_PeripheralBurst_Single;         //
	DMA_InitStructure.DMA_PeripheralDataSize	=DMA_PeripheralDataSize_HalfWord; //半字//
	DMA_InitStructure.DMA_PeripheralInc			=DMA_PeripheralInc_Disable;            //外设地址自增失能//
	DMA_InitStructure.DMA_Priority				=DMA_Priority_High;                         //优先级高//
	
	DMA_Init(DMA2_Stream0,&DMA_InitStructure);
	DMA_Cmd(DMA2_Stream0,ENABLE);
}
void ADC_All_Init(uint16_t ARR,uint16_t PSC,uint16_t *ARRAY,uint16_t POINT)
{
	ADC_GPIO_Init();
	TIM3_Init(ARR,PSC);
	ADC1_Init();
	ADC_DMA_Init(ARRAY,POINT);
}

#endif
