/* Includes ------------------------------------------------------------------*/
#include "ti/devices/msp432e4/driverlib/driverlib.h"
#include <stdint.h>
#include <stdbool.h>
#include "stdio.h"
#include "delay.h"
#include "system_init.h"
#include "led.h"
//#include "button.h"
#include "uart.h"
//#include "ADS112C04_i2c.h"
//#include "ADS112C04.h"
//#include "AD9910.h"
#include "math.h"
#include "uartstdio.h"
#include "tim.h"
#include "CD4051.h"
#include "AD9959.h"

#include "adc.h"

//#include "string.h"

/* Private define ------------------------------------------------------------*/
#define FFT_LENGTH 1024 
#define PI 3.1415926
/* Private variables ---------------------------------------------------------*/
	uint32_t ui32SysClock;
	uint16_t i,j;
//HMI
	uint8_t HMI_Commond = 0;
//ADC
	extern uint32_t ui32SysClock;
	uint16_t dataBufferA[1];
	uint16_t dataBufferB[1];
	volatile bool bgetConvStatus = false;;
	uint16_t adc_buff[FFT_LENGTH];//存放ADC采集的数据
//C Measure
	double Q_Vin = 0;
	double Q_Vout = 0;
	double C=0;
	//double Freq = 1000;
	double C_Pow = 0;
	double Q_fz=0;
	double Q_fm=0;
	uint16_t R = 10000;
//Phase
	uint32_t Count1;
	uint32_t Count2;
	float Phase;
	uint32_t freq1;
	uint32_t loc2;
	uint32_t flag;
//L Measure
	double L_Vin = 0;
	double L_Vout = 0;
	double L=0;
	double Freq = 1000;
	double L_Pow = 0;
	double L_fz=0;
	double L_fm=0;

/* Private function prototypes -----------------------------------------------*/
double Filter(void); 
double Filter1(void);
void bubble_sort(float ADC1_Value[],uint16_t Num); 
void Correct_Phase(void);
void Correct_Vrms(void);

uint8_t Serial_GetRxFlag(void);

void HMI_DDS_9959(void);
void DDS_Init(void);
void HMI_Reset_Sys_Init(void);
void HMI_Reset_Sys(void);

void ADC_All_Init(void);//waiting ADC 1 0 Init

void C_Measure(void);

void HMI_Init(void);

/* UART Variable--------------------------------------------------*/
uint8_t ReceiveData[16];         //AA 55 01 01 
uint16_t  length = 0;             //串口接受长度
uint8_t DataState = 0;		//串口判断符
/* ------------------------------------*/
typedef enum
{
    PACKET_IDLE,     // 空闲状态
    PACKET_HEADER_1, // 正在接收帧头的第一个字节
    PACKET_HEADER_2, // 正在接收帧头的第二个字节
    PACKET_LENGTH,   // 正在接收数据长度
    PACKET_DATA,     // 正在接收数据
    PACKET_TAIL_1,   // 正在接收帧尾的第一个字节
    PACKET_TAIL_2    // 正在接收帧尾的第二个字节
} PacketState;
// 数据包 | 帧头(0xAA 0x55) | 数据长度 | 数据 | 帧尾(0x55 0xAA) |
//  定义常量
#define HEADER_BYTE_1 0xAA
#define HEADER_BYTE_2 0x55
#define TAIL_BYTE_1 0x55
#define TAIL_BYTE_2 0xAA
//-------My DDS Area---------------------------
unsigned char hexArray[3];
uint32_t CH1_Freq = 1000;
uint16_t CH1_Ampl = 512;
uint32_t CH2_Freq = 1000;
uint16_t CH2_Ampl = 512;
//-------My Function-----------------------
uint8_t RxData;
//16进制 转 10 进制
long hexArrayToDecimal(unsigned char hexArray[3]) 
{
	long decimalValue = 0;
	long decimalValue0 = 0;
	long decimalValue1 = 0;
	
    decimalValue0 =(int)hexArray[0] << 16;//  
    decimalValue1 =(int)hexArray[1] << 8;//  // 左移8位
    decimalValue = decimalValue0 + decimalValue1;
    decimalValue += hexArray[2];// | (hexArray[0] << 16) | (hexArray[1] << 8) ;
    
    return decimalValue;
}
//--------------------------------------------------
/* Main ----------------------------------------------------------------------*/
int main(void)
{
//初始化
	IntPrioritySet(INT_TIMER3B, 3);
	IntPrioritySet(INT_TIMER2A, 3);
	sys_init();
	uart0_init();
	uart2_init();
	adc_init();
	CD4051_Init();
	HMI_Reset_Sys_Init();
	//ADS112_Init();
	//Init_AD9910();
	delay_ms(500);//Wait 9959 Go Power
	//Switch_Init();
	capture1_init();//T2cpp0 PM0测频率
	capture2_init();//T3cpp1 PM3测频率
	TimerSynchronize(TIMER2_BASE, TIMER_2A_SYNC);
	TimerSynchronize(TIMER3_BASE, TIMER_3B_SYNC);
	printf("\r\nBegin\r\n"); 
	HMI_Init();
	DDS_Init();
	CD4051_Select_Channel(0);
	while(0)
	{
		if(DataState == 0x0A)
		{
			for(int i = 0;i<=length;i++)
			{
			printf2f("Data%d = %d\r\n", i,ReceiveData[i]);
			 delay_ms(5);
			 
			}
		printf2f("\r\n");
		delay_ms(5) ;
		DataState =0;
		}
	}
	while(0)
	{
		//HMI_DDS_9959();
		//C_Measure();
//		printf2f("x0.val=%ld\xff\xff\xff",(uint16_t)((float)ui32SysClock/(float)freq1)*100);
//		delay_ms(5);
		
//		if(Phase > 180.0)
//		{
//			printf2f("x1.vvs1=3\xff\xff\xff");
//			delay_ms(5);
//			printf2f("x1.val=%ld\xff\xff\xff",(uint16_t)(1.0 / tanf((90.0-(Phase - 180.0))/90.0 * 1.5707)*100));
//			delay_ms(5);
//		}else{//<180
//			printf2f("x1.vvs1=3\xff\xff\xff");
//			delay_ms(5);
//			printf2f("x1.val=%ld\xff\xff\xff",(uint16_t)(1.0 / tanf((270.0 - Phase))/90.0 * 1.5707)*100);
//			delay_ms(5);
//		}
//		//tanf((90.0-(Phase - 180.0))/90.0 * 1.5707)*100)
//		
//		delay_ms(100);
		ADC_All_Init();
		Q_Vin = 1068.75/100.0; //(double)dataBufferA[0] * 3300.0 / 4095.0
		Q_Vout = Filter();
		
		Q_fz =  5.0 * Q_Vin;
		Q_fm  = 3.1415926 * sqrtf((Q_Vin-Q_Vout)*(Q_Vin+Q_Vout));//少了1000 000 F^2   1000 R         100K R
		C_Pow = Q_fz / Q_fm;
		
		//printf2f("x0.val=%d\xff\xff\xff",(uint16_t)(sqrtf(C_Pow)*1000.0));
		printf2f("x0.vvs1=1\xff\xff\xff");
		delay_ms(5);
		printf2f("x0.val=%ld\xff\xff\xff",(uint32_t)(C_Pow*100));
		delay_ms(50);
		printf2f("x1.vvs1=0\xff\xff\xff");
		delay_ms(5);
		printf2f("x1.val=%ld\xff\xff\xff",(uint16_t)(Q_Vout*100));
		delay_ms(50);
		delay_ms(100);
		
	}
	while(1)
	{
		HMI_Init();
		while(HMI_Commond == 1)
		{
			CD4051_Select_Channel(0);
			HMI_Init();
			
			C_Measure();
			
			if(HMI_Commond == 3)
			{
				HMI_Commond == 0;
				break;
			}
		}
		while(HMI_Commond == 2)
		{
			CD4051_Select_Channel(2);
			HMI_Init();
			
			ADC_All_Init();
			L_Vin = 1068.75; //(double)dataBufferA[0] * 3300.0 / 4095.0
			L_Vout = Filter1()/24;
			
			L_fz =  47.0 * L_Vout *10;
			L_fm  = 6.2831852  * sqrtf((L_Vin-L_Vout)*(L_Vin+L_Vout));//少了1000 000 F^2   1000 R  3.1415926      100K R
			L_Pow = L_fz / L_fm;
			
			//printf2f("x0.val=%d\xff\xff\xff",(uint16_t)(sqrtf(C_Pow)*1000.0));
			printf2f("x0.vvs1=1\xff\xff\xff");
			delay_ms(5);
			printf2f("x0.val=%ld\xff\xff\xff",(uint32_t)(L_Pow*100));
			delay_ms(50);
			printf2f("x1.vvs1=1\xff\xff\xff");
			delay_ms(5);
			printf2f("x1.val=%ld\xff\xff\xff",(uint16_t)(L_Vout*10));
			delay_ms(50);
			delay_ms(100);
			
			
			if(HMI_Commond == 3)
			{
				HMI_Commond == 0;
				break;
			}
		}
	}
}


void HMI_Init(void) 
{
	if(DataState == 0x0A)
		{
			if(ReceiveData[0] == 0xDD)//返回
			{
				HMI_Commond = 3;
			}else if(ReceiveData[0]  == 0xDE)//电容测量
			{
				HMI_Commond = 1;
			}else if(ReceiveData[0]  == 0XEF)//电感测量
			{
				HMI_Commond = 2;
			}
		DataState =0;
		}
}
void C_Measure(void)
{
		ADC_All_Init();
		Q_Vin = 1068.75/100.0; //(double)dataBufferA[0] * 3300.0 / 4095.0
		Q_Vout = Filter();//(double)dataBufferB[0] *  8.276 / 10  / 100;// * 3300.0 / 4095.0/100.0;
		
		Q_fz =  (Q_Vin-Q_Vout)*(Q_Vin+Q_Vout);
		Q_fm  = Q_Vout*Q_Vout*39.47841;//少了1000 000 F^2   1000 R         100K R
		C_Pow = Q_fz / Q_fm;
		
		if(Q_Vout*100 >= 990 && Q_Vout*100 <= 1050)//1 nF 
		{
			printf2f("x0.vvs1=3\xff\xff\xff");
			delay_ms(5);
			printf2f("x0.val=%ld\xff\xff\xff",(uint32_t)(1150-Q_Vout*12));
			delay_ms(5);
//			printf2f("x1.vvs1=0\xff\xff\xff");
//			delay_ms(5);
//			printf2f("x1.val=%ld\xff\xff\xff",(uint16_t)(Q_Vout*100));
//			delay_ms(5);
		}
		else if(Q_Vout*100 >= 970 && Q_Vout*100 <=990)//4.7 nF
		{
			printf2f("x0.vvs1=3\xff\xff\xff");
			delay_ms(5);
			printf2f("x0.val=%ld\xff\xff\xff",(uint32_t)(5432-Q_Vout*15));
			delay_ms(5);
//			printf2f("x1.vvs1=0\xff\xff\xff");
//			delay_ms(5);
//			printf2f("x1.val=%ld\xff\xff\xff",(uint16_t)(Q_Vout*100));
//			delay_ms(5);
		}
		else if(Q_Vout*100 >= 100 && Q_Vout*100 <=200)//100 nF
		{
			printf2f("x0.vvs1=1\xff\xff\xff");
			delay_ms(5);
			printf2f("x0.val=%ld\xff\xff\xff",(uint32_t)(900 - Q_Vout*13));
			delay_ms(5);
//			printf2f("x1.vvs1=0\xff\xff\xff");
//			delay_ms(5);
//			printf2f("x1.val=%ld\xff\xff\xff",(uint16_t)(Q_Vout*100));
//			delay_ms(5);
		}
		else if(Q_Vout*100 >= 200 && Q_Vout*100 <=970)
		{
			//printf2f("x0.val=%d\xff\xff\xff",(uint16_t)(sqrtf(C_Pow)*1000.0));
			printf2f("x0.vvs1=1\xff\xff\xff");
			delay_ms(5);
			printf2f("x0.val=%ld\xff\xff\xff",(uint32_t)(sqrtf(C_Pow)*1000 - Q_Vout));
			delay_ms(5);
//			printf2f("x1.vvs1=0\xff\xff\xff");
//			delay_ms(5);
//			printf2f("x1.val=%ld\xff\xff\xff",(uint16_t)(Q_Vout*100));
//			delay_ms(5);
			//delay_ms(200);
		}else{
			printf2f("x0.vvs1=1\xff\xff\xff");
			delay_ms(5);
			printf2f("x0.val=%ld\xff\xff\xff",(uint32_t)(0));
			delay_ms(5);
		}
		
		if(Phase > 180.0)
		{
			printf2f("x1.vvs1=3\xff\xff\xff");
			delay_ms(5);
			printf2f("x1.val=%ld\xff\xff\xff",(uint16_t)(1.0 / tanf((90.0-(Phase - 180.0))/90.0 * 1.5707)*100));
			delay_ms(5);
		}else{//<180
			printf2f("x1.vvs1=3\xff\xff\xff");
			delay_ms(5);
			printf2f("x1.val=%ld\xff\xff\xff",(uint16_t)(1.0 / tanf((270.0 - Phase))/90.0 * 1.5707)*100);
			delay_ms(5);
		}
		//tanf((90.0-(Phase - 180.0))/90.0 * 1.5707)*100)
}
void TIMER2A_IRQHandler(void)
{
    flag = 2;
//printf("1\r\n");
    uint32_t getTimerIntStatus;
	getTimerIntStatus = MAP_TimerIntStatus(TIMER2_BASE, true);
	MAP_TimerIntClear(TIMER2_BASE, getTimerIntStatus);
//代码区
    if (getTimerIntStatus & TIMER_CAPA_EVENT){
//        printf("C2:%d\r\n",loc2);
        Count1 = TimerValueGet(TIMER2_BASE, TIMER_A);
        loc2 = Count1 - Count2;
        Phase = (float)loc2*360/(float)freq1-2*((float)ui32SysClock/(float)freq1)/1000;//1k差2，7k差14，10k差25.8，50k差129，70k差280     -2*((float)ui32SysClock/(float)freq1)/1000
    }
}


void TIMER3B_IRQHandler(void)
{
    flag = 3;
	uint32_t getTimerIntStatus;
	getTimerIntStatus = MAP_TimerIntStatus(TIMER3_BASE, true);
	MAP_TimerIntClear(TIMER3_BASE, getTimerIntStatus);
//代码区
    if (getTimerIntStatus & TIMER_CAPB_EVENT) 
    {
        freq1 = TimerValueGet(TIMER3_BASE, TIMER_B) - Count2;
        Count2 = TimerValueGet(TIMER3_BASE, TIMER_B);
    }
    
}


void DDS_Init(void)
{
	//	DDS 9959 1KHz  200mV 产生--------------------------------------------------------------------
	AD9959_Init();//初始化控制AD9959需要用到的IO口,及寄存器
	//AD9959_Set_Fre(CH0, 100000);	//设置通道0频率100000Hz
	//AD9959_Set_Fre(CH1, 100000);	//设置通道1频率100000Hz
	AD9959_Set_Fre(CH2, CH1_Freq);	//设置通道2频率100000Hz
	AD9959_Set_Fre(CH3, CH2_Freq);	//设置通道3频率100000Hz

	//AD9959_Set_Amp(CH0, 1023); 		//设置通道0幅度控制值1023，范围0~1023
	//AD9959_Set_Amp(CH1, 1023); 		//设置通道1幅度控制值1023，范围0~1023
	AD9959_Set_Amp(CH2, 935); 		//设置通道2幅度控制值1023，范围0~1023
	AD9959_Set_Amp(CH3, 935); 		//设置通道3幅度控制值1023，范围0~1023

	//AD9959_Set_Phase(CH0, 0);			//设置通道0相位控制值0(0度)，范围0~16383
	//AD9959_Set_Phase(CH1, 4096);	//设置通道1相位控制值4096(90度)，范围0~16383
	AD9959_Set_Phase(CH2 ,4096);	//设置通道2相位控制值8192(180度)，范围0~16383.
	AD9959_Set_Phase(CH3, 0);	//设置通道3相位控制值12288(270度)，范围0~16383
	IO_Update();	//AD9959更新数据,调用此函数后，上述操作生效！！！！     
}
void HMI_Reset_Sys_Init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOQ);
	GPIOPinTypeGPIOOutput(GPIO_PORTQ_BASE, GPIO_PIN_2);
}
void HMI_Reset_Sys(void)
{
	GPIOPinWrite(GPIO_PORTQ_BASE, GPIO_PIN_2, 0);
	//J2 与 RST 短接   当J2为低电平  系统复位
}
void ADC_All_Init(void)//waiting ADC 1 0 Init
{
	MAP_ADCProcessorTrigger(ADC1_BASE, (ADC_TRIGGER_WAIT | 3));
	MAP_ADCProcessorTrigger(ADC0_BASE, (ADC_TRIGGER_SIGNAL | 3));

	/* Wait for the conversion to complete */
	while(!bgetConvStatus);
	bgetConvStatus = false;
}
void HMI_DDS_9959(void)
{
	if(DataState == 0x0A)
		{
			if(ReceiveData[0] == 0xAB)//0xAA CH1 Freq
			{
				unsigned char hexArrayy[3]={ReceiveData[3],ReceiveData[2],ReceiveData[1]};
				long decimalValue1 = hexArrayToDecimal(hexArrayy);
				
				CH1_Freq = decimalValue1;
				
				printf2f("Data1 = %d\r\n",ReceiveData[0]);
				delay_ms(5);
				AD9959_Set_Fre(CH2, CH1_Freq);	//设置通道2频率100000Hz
				IO_Update();
				
			}else if(ReceiveData[0]  == 0xBC)//0xBB CH1 Ampl
			{
				unsigned char hexArrayy[3]={ReceiveData[3],ReceiveData[2],ReceiveData[1]};
				long decimalValue1 = hexArrayToDecimal(hexArrayy);
				CH1_Ampl = (uint16_t)((float)decimalValue1 * 2.048);
				
				AD9959_Set_Amp(CH2, CH1_Ampl); 
				IO_Update();
				
			}else if(ReceiveData[0]  == 0XCD)//0xCC CH2 Freq
			{
				unsigned char hexArrayy[3]={ReceiveData[3],ReceiveData[2],ReceiveData[1]};
				long decimalValue1 = hexArrayToDecimal(hexArrayy);
				CH2_Freq = decimalValue1;
				
				AD9959_Set_Fre(CH3, CH2_Freq);
				IO_Update();
				
			}else if(ReceiveData[0]  == 0xDD)//0xDD CH2 Ampl
			{
				unsigned char hexArrayy[3]={ReceiveData[3],ReceiveData[2],ReceiveData[1]};
				long decimalValue1 = hexArrayToDecimal(hexArrayy);
				CH2_Ampl = (uint16_t)((float)decimalValue1 * 2.048);
				
				AD9959_Set_Amp(CH3, CH2_Ampl);
				IO_Update();
			}
		DataState =0;
		}
}

//串口屏接受中断
void UART2_IRQHandler(void)
{
	uint32_t ui32Status = 0;
	uint16_t  j = 0;
	uint16_t  flag = 0;
	
	ui32Status = MAP_UARTIntStatus(UART2_BASE, true);
	MAP_UARTIntClear(UART2_BASE, ui32Status);
	
	while(MAP_UARTCharsAvail(UART2_BASE))
	{
		DataState = MAP_UARTCharGetNonBlocking(UART2_BASE);//HWREG(UART2_BASE + 0x00000000);
		//printf2f("Data0 = %d\r\n", ReceiveData[0]);
		delay_ms(5);
		//MAP_UARTCharPutNonBlocking(UART2_BASE, MAP_UARTCharGetNonBlocking(UART2_BASE));
//代码区        
		if(DataState == 0xAA)
		{
			//printf2f("DataState1 = %d\r\n", DataState);
			delay_ms(5) ;
			DataState = MAP_UARTCharGetNonBlocking(UART2_BASE);
			while(DataState == 0x55)
			{
				delay_ms(5) ;
				ReceiveData[j] = MAP_UARTCharGetNonBlocking(UART2_BASE);
				 if(ReceiveData[j] == 0x0D)
				 {
					flag =1;
				 }
				 if(ReceiveData[j] == 0x0A && flag ==1)
				 {
					DataState =  0x0A;
					flag =0;
					length = j-2;
					j=0;
					break;
				}
				if(j == 15)
				 {
					DataState == 0x09;
					break;
				 }
				 j++;
			}
		}
		else
		{
			DataState = 0;
		}
	}
}
void Correct_Vrms(void)
{
//	ADS112_WriteReg0(ADS122C04_MUX_AIN1_AVSS,ADS122C04_GAIN_1,ADS122C04_PGA_DISABLED);
//	for(i=0;i<Num;i++)
//	{
//		ADS112_Send_Command(ADS122C04_START_CMD);
//		ADC1_Value[i] = ADS112_GetADC_Vol();	
//		delay_ms(10);
//	}
//	ADC1_Value_Filter = Filter(ADC1_Value);
//	Vrms_Change = 0.1 - (0.2196*(double)ADC1_Value_Filter - 0.0036);
//	printf("Vrms_Change:%0.2f\r\n",Vrms_Change);	
}

void Correct_Phase(void)
{
//	ADS112_WriteReg0(ADS122C04_MUX_AIN1_AVSS,ADS122C04_GAIN_1,ADS122C04_PGA_DISABLED);
//	for(i=0;i<Num;i++)
//	{
//		ADS112_Send_Command(ADS122C04_START_CMD);
//		ADC1_Value[i] = ADS112_GetADC_Vol();	
////			printf("1:%0.3f\r\n",ADC1_Value[i]);
//		delay_ms(10);
//	}		
//	ADC1_Value_Filter = Filter(ADC1_Value);
////		printf("%0.5f\r\n",ADC1_Value_Filter);
//	Phase_Change = 90 - (-91.289*ADC1_Value_Filter + 174.98);
//	printf("Phase_Change:%0.2f\r\n",Phase_Change);	
}

double Filter1(void) 
{
//	float a = 0;
//	bubble_sort(ADC_Value);
////	for(i=3;i<Num-3;i++)
////	{
////		printf("%d:%0.3f\r\n",i,ADC_Value[i]);
////		delay_ms(10);
////	}	
//	for(i=3;i<Num-3;i++) a += ADC_Value[i]/4;
////	printf("a:%0.3f\r\n",a);
	double  filter_sum = 0;
	// 算术平均滤波法
	int i;
	for(i = 0; i < 20; i++)
	{
	filter_sum += (double)dataBufferB[0]*  8.776 / 10;//(double)dataBufferB[0] *  8.276 / 10 / 25.510 / 10;/// 25.510;// *  8.276 / 10 / 25.510 / 10;//  Get_AD()
	delay_ms(1);
	}
	return (double)(filter_sum / 20);

//	return a;
}
double Filter(void) 
{
//	float a = 0;
//	bubble_sort(ADC_Value);
////	for(i=3;i<Num-3;i++)
////	{
////		printf("%d:%0.3f\r\n",i,ADC_Value[i]);
////		delay_ms(10);
////	}	
//	for(i=3;i<Num-3;i++) a += ADC_Value[i]/4;
////	printf("a:%0.3f\r\n",a);
	double  filter_sum = 0;
	// 算术平均滤波法
	int i;
	for(i = 0; i < 50; i++)
	{
	filter_sum += (double)dataBufferB[0] * 8.276 / 10 / 100;;/// 25.510;// *  8.276 / 10 / 25.510 / 10;//  Get_AD()
	delay_ms(2);
	}
	return (double)(filter_sum / 50);

//	return a;
}

void bubble_sort(float ADC_Value[],uint16_t Num) 
{
	int a,b;
	float temp;
	for(a=0;a<Num;a++)
	{   
		for(b=0;b<Num-a-1;b++)
		{   
			if(ADC_Value[b] < ADC_Value[b+1])
			{   
				temp = ADC_Value[b];
				ADC_Value[b] = ADC_Value[b+1];
				ADC_Value[b+1] = temp;
			}   
		}       
	}   
}
