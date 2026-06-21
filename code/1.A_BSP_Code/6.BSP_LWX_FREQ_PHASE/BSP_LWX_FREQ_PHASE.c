/* Introduce ----------------------------------------- *
	
 ----------------------------------------------------- */
/* Include ------------------------------------------- */
#include "BSP_LWX_FREQ_PHASE.h"
/* User Temp Include --------------------------------- */
/* LWX BSP Driver Lib -------------------------------- */
/* User Define --------------------------------------- */
/* User Variable ------------------------------------- */
/* Phase ------- */
double  CH3_Count;				//全局变量，用于计数
double  CH4_Count;				//全局变量，用于计数
/* Frequency --- */
uint16_t cnt;
float CNT;
/* User Extern --------------------------------------- */
/* User Function ------------------------------------- */
/* Phase --------------------------------------------- */
void TIM2_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				//定义结构体变量
	/*开启时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);			//开启TIM2的时钟
	
	/*配置时钟源*/
	TIM_InternalClockConfig(TIM2);		//选择TIM2为内部时钟，若不调用此函数，TIM默认也为内部时钟
	
	/*时基单元初始化*/
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元功能
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//计数器模式，选择向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 0xFFFF;				//计数周期，即ARR的值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0;				//预分频器，即PSC的值
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;			//重复计数器，高级定时器才会用到
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);				//将结构体变量交给TIM_TimeBaseInit，配置TIM2的时基单元	
	
	TIM_ARRPreloadConfig(TIM2,ENABLE);
	/*TIM使能*/
	TIM_Cmd(TIM2, ENABLE);			//使能TIM2，定时器开始运行
	
}

void Phase_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	/*开启时钟*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);		//开启GPIOB的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	/*AFIO选择中断引脚*/
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);//PE2 连接到中断线2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);//PE3 连接到中断线3
	
	/*EXTI初始化*/
	//---------------------------------------------
	EXTI_InitStructure.EXTI_Line = EXTI_Line2 | EXTI_Line3;       // 
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
	EXTI_Init(&EXTI_InitStructure);//配置
	 //--------------------------------
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//外部中断2
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);//配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//外部中断3
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x04;//抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x04;//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);//配置
	 //---------------------------------
}
void EXTI2_IRQHandler(void)//外部中断2服务程序
{
	
		CH4_Count = TIM_GetCounter(TIM2);
		EXTI_ClearITPendingBit(EXTI_Line4);		//清除外部中断14号线的中断标志位
													//中断标志位必须清除
													//否则中断将连续不断地触发，导致主程序卡死
	 EXTI_ClearITPendingBit(EXTI_Line2);//清除LINE2上的中断标志位 
}
void EXTI3_IRQHandler(void)//外部中断3服务程序
{
	static uint8_t Flag = 1;
	if (EXTI_GetITStatus(EXTI_Line3) == SET)		//判断是否是外部中断14号线触发的中断
	{
		if(Flag == 1){TIM_SetCounter(TIM2,0);           EXTI_ClearITPendingBit(EXTI_Line3);	 Flag = 2;}
		if(Flag == 2){CH3_Count = TIM_GetCounter(TIM2); EXTI_ClearITPendingBit(EXTI_Line3);  Flag = 1;}
		
		//EXTI_ClearITPendingBit(EXTI_Line3);		//清除外部中断14号线的中断标志位
													//中断标志位必须清除											//否则中断将连续不断地触发，导致主程序卡死
	}
}
/* Frequency------------------------------------------ */
//TIM4负责计时  TIM3负责技术 PA1 0-131 070Hz
void TIM4_Int_Init(void) //定时0.5秒
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  ///使能TIM4时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = 10000; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=4200-1;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);//初始化TIM4
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM4,ENABLE); //使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

//定时器5通道1输入捕获配置
//arr：自动重装值(TIM2,TIM5是32位的!!)
//psc：时钟预分频数
void TIM5_CH1_Cap(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM5时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTA时钟	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //GPIOA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //下拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA0

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5); //PA0复用位定时器5
    
	TIM_TimeBaseStructure.TIM_Prescaler=0;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=0xffff;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=0; 
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);
			
	TIM_TIxExternalClockConfig(TIM5, TIM_TIxExternalCLK1Source_TI2,TIM_ICPolarity_Falling,0);
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
   
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级3
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
//	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
	TIM_SetCounter(TIM5,0);//??TIM2?????0
	TIM_Cmd(TIM5,ENABLE ); 	//使能定时器5
}
//捕获状态
//[7]:0,没有成功的捕获;1,成功捕获到一次.
//[6]:0,还没捕获到低电平;1,已经捕获到低电平了.
//[5:0]:捕获低电平后溢出的次数(对于32位定时器来说,1us计数器加1,溢出时间:4294秒)
//u8 flag=0;
uint32_t capture = 0;
void TIM5_IRQHandler(void)//定时器5中断服务程序	 
{ 		    
	if(TIM_GetITStatus(TIM5, TIM_IT_Update) == SET) 
	{
		
	TIM_ClearITPendingBit(TIM5, TIM_IT_Update); //清除中断标志位			
    }
}
void TIM4_IRQHandler(void)//定时器4中断服务函数
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) //溢出中断
	{
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  //清除中断标志位
		cnt = TIM_GetCounter(TIM5);
		CNT = cnt*2;
		if(CNT>=10000&&CNT<29990) CNT-=1;
		if(CNT>=29990&&CNT<39990) CNT-=2;
		if(CNT>=39990&&CNT<49990) CNT-=3;
		if(CNT>=49990&&CNT<59990) CNT-=4;
		if(CNT>=59990&&CNT<79990) CNT-=5;
		if(CNT>=79990&&CNT<89990) CNT-=6;
		if(CNT>=89990&&CNT<99990) CNT-=7;
		if(CNT>=99990) CNT-=8;
		TIM_SetCounter(TIM5,0);
		TIM_SetCounter(TIM4,0);	
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  //清除中断标志位
}
/* Main ----------------------------------------------
//-------------------------------------
//    配置ETR外部引脚输入的方式
//    GPIO_InitTypeDef GPIO_InitStructure;
//    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
// 
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
// 
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//    GPIO_Init(GPIOE, &GPIO_InitStructure);
// 
//    GPIO_PinAFConfig(GPIOE, GPIO_PinSource7, GPIO_AF_TIM1);
// 
//    TIM_TimeBaseStructure.TIM_Prescaler = 0x00;
//    TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
//    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
//    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);  // Time base configuration
// 
//    TIM_ETRClockMode2Config(TIM1, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0x0F);
// 
//    TIM_SetCounter(TIM1, 0);
//    TIM_Cmd(TIM1, ENABLE);
//-----------------------------------
*/
