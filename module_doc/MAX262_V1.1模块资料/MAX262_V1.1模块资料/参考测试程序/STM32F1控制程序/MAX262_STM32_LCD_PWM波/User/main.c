//-----------------------------------------------------------------
// 程序描述: 
//		在Keil uVision4开发平台下基于STM32的程序模板
// 作    者: 凌智电子
// 开始日期: 2019-05-20
// 完成日期: 2014-05-24
// 修改日期:
// 版    本: V1.0
//   - V1.0: 初步模板
// 调试工具: 凌智STM32核心板板、LZE_ST LINK2、MAX262模块
// 连 接 说 明:
//    MAX262模块     STM32核心板
// 				WR    <--    PE15
// 				LE    <--    PE14
// 				D0    <--    PB8
// 				D1    <--    PB9
// 				A0    <--    PB10
// 				A1    <--    PB11
// 				A2    <--    PB12
// 				A3    <--    PB13
// 				GND   <-->   GND

// 				CLK端口<--   PA0

// 按键控制说明:
// 		PWM波提供时钟信号时，需要用按键进行设置中心/截止频率，
// 		K1键用于选择修改的位置，
// 		K2键用于中心/截止频率的加，
//		K3键用于中心/截止频率的减，
//		数据设置好之后K4键确定，
//		根据设置的频率计算出时钟频率，并设置重装载值和预分频值，输出PWM波，
//		由于预分频值和重装载值都是整数，因此得出的时钟频率存在一定的误差。
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// 头文件包含 
//-----------------------------------------------------------------
#include <stm32f10x.h>
#include "delay.h"
#include "PeripheralInit.h"
#include "MAX262.h"
#include "CharLCD.h"
#include "key.h"
#include "PWMOutput.h"
#include "stdio.h"

extern u32 counterf;             // 重装载值
extern u16 divf;                 // 预分频数
extern u16 radio_num;
u8 Fn;

//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
int main(void)
{
	u8 i;
	int date_bufl[6] = {00};
	u8 key1_flag;                  // 按键设置
	u8 buf[6];
	u8 key;
	s32 fre1,fre0;              // fre0为标准的值, fre1为更改后的值
	double fclk;								  // CLK时钟, 单位为Hz
	key1_flag = 0;
	fre0 = 0;
	fre1 = 1;                             // 截止频率, 单位为Hz
	PeripheralInit();                     // 外设初始化
	WriteString (1, 3, "MAX262 test!");   
	WriteString (2, 1, "Freq: ");
	WriteString (2, 14, " Hz ");
	MAX262_GPIO_Init();                  // IO口初始化配置
// 	Filter1(0, 3);                       // (mode)控制方式mode, 中心频率f, 品质因数q
// 	Filter2(0, 3);                       // (mode)控制方式mode, 中心频率f, 品质因数q
// 	Delay_1ms(100);		   
// 	GPIOB->ODR =0;

	while(1)
	{	
	  date_bufl[0] = ((fre1 % 1000000) / 100000);	 
		date_bufl[1] = ((fre1 % 100000) / 10000);		 
		date_bufl[2] = ((fre1 % 10000) / 1000);			 
		date_bufl[3] = ((fre1 % 1000) / 100);			 
		date_bufl[4] = ((fre1 % 100) / 10);				 
		date_bufl[5] = ((fre1 % 10) / 1);		
		key = Key_Scan();                   // 按键扫描
		if(key == 1)     // 判断KEY1键是否按下
		{
			key1_flag++;  
			if(key1_flag == 7)
				key1_flag = 1;
  
		}
		else if(key == 2)     // 判断KEY2键是否按下, 若按下则对频率进行相应的加
		{
			switch (key1_flag)       // 由位置确定修改步进
			{			
				case 1:			                      // 截止频率个位加1
					date_bufl[5] ++;
				  if(date_bufl[5]>9) date_bufl[5]=0;
					break;
				case 2:			                      // 截止频率十位加1
					date_bufl[4] ++;
				  if(date_bufl[4]>9) date_bufl[4]=0;
					break;
				case 3:                           // 截止频率百位加1
					date_bufl[3] ++;
				  if(date_bufl[3]>9) date_bufl[3]=0;
					break;
				case 4:			                      // 截止频率千位加1
					date_bufl[2] ++;
				  if(date_bufl[2]>9) date_bufl[2]=0;
					break;
				case 5:                           // 截止频率万位加1
					date_bufl[1] ++;
				  if(date_bufl[1]>9) date_bufl[1]=0;
					break;
				case 6:                           // 截止频率十万位加1
					date_bufl[0] ++;
				  if(date_bufl[0]==2) date_bufl[0]=0;
 				default: break;
			}	
      fre1 = date_bufl[0]*100000+date_bufl[1]*10000+date_bufl[2]*1000+date_bufl[3]*100+date_bufl[4]*10+date_bufl[5];			
		}
		else if(key == 3)     // 判断KEY3键是否按下, 若按下则对频率进行相应的减
		{
			switch (key1_flag)
			{			
				case 1:			                      // 截止频率个位减1
					date_bufl[5] --;
				  if(date_bufl[5]<0) date_bufl[5]=9;
					break;
				case 2:			                      // 截止频率十位减1
					date_bufl[4] --;
				  if(date_bufl[4]<0) date_bufl[4]=9;
					break;
				case 3:                           // 截止频率百位减1
					date_bufl[3] --;
				  if(date_bufl[3]<0) date_bufl[3]=9;
					break;
				case 4:			                      // 截止频率千位减1
					date_bufl[2] --;
				  if(date_bufl[2]<0) date_bufl[2]=9;
					break;
				case 5:                           // 截止频率万位减1
					date_bufl[1] --;
				  if(date_bufl[1]<0) date_bufl[1]=9;
					break;
				case 6:                           // 截止频率十万位减1
					date_bufl[0] --;
				  if(date_bufl[0]<0) date_bufl[0]=1;
 				default: break;
			}	
			fre1 = date_bufl[0]*100000+date_bufl[1]*10000+date_bufl[2]*1000+date_bufl[3]*100+date_bufl[4]*10+date_bufl[5];			
		}
		else if(key == 4)      // 判断KEY4键是否按下, 若按下则确定截止频率
		{
			key1_flag = 0;
			if(fre1 > 100000)  fre1=100000;     // 截止频率最大为100000Hz
			else if(fre1 == 0) fre1=1;          // 截至频率最小为1Hz
			if (fre0!=fre1)                     // 判断截止频率是否被修改
			{
				if(fre1 <= 28000)                 // 判断频率大于28k, 大于则选择40.48, 否则为139.8
				{
					fclk = (double)(fre1 * NF1);                    // 求出CLK时钟, 芯片手册p11
					Fn = 63;
				}
				else 
				{
					fclk = (double)(fre1 * NF2);                    // 求出CLK时钟, 芯片手册p11
					Fn = 0;					
				}
				divf = ((72000000/fclk)/65535)+1;    // 求出预分频数
				counterf = ((720000000/fclk)/divf);  // 重装载值
				if(counterf%10>=5)                   // 重装载值四舍五入
				{
					counterf = (counterf/10)+1;
				}
				else
				{
					counterf = counterf/10;
				}
				radio_num = counterf/2;            // 求出占空比
				TIM2_PWMOutput_Init();             // 重新产生PWM波
				fre0 =fre1;
				Filter1(0, 0.842);                     // (mode)控制方式mode, 品质因数q 
				Filter2(0, 0.842);                     // (mode)控制方式mode, 品质因数q 
				Delay_1ms(50);		   
				GPIOB->ODR =0;
			}
		}
		sprintf((char*)buf, "%6d", fre1);   // 将整数转到字符串中
		WriteString (2, 7, buf);            // 在1602上面显示截止频率的值
		
		if(key1_flag)                       //判断是否需要修改截至频率的值
		{
			 					 
			 i=key1_flag-1; 
		 	 while(date_bufl[5-i]==0)         //在修改的位置上填充零
			 {
			 	 WrCLcdC(0x80+0x40+11-i);  
				 WrCLcdD(0x30);
				 i--;
				 if(i == 0)  break;
			}
			Delay_50ms(2);                  
			switch(key1_flag)	 
			{
				case 1:	  WrCLcdC(0x80+0x40+11);  WrCLcdD(0x5f);	break;   // 显示频率修改的位置
				case 2:	  WrCLcdC(0x80+0x40+10);	WrCLcdD(0x5f);  break;
				case 3:	  WrCLcdC(0x80+0x40+9);   WrCLcdD(0x5f);  break;
				case 4:	  WrCLcdC(0x80+0x40+8);	  WrCLcdD(0x5f);  break;
				case 5:	  WrCLcdC(0x80+0x40+7);	  WrCLcdD(0x5f);  break;
// 				case 6:	  WrCLcdC(0x80+0x40+6);	  WrCLcdD(0x5f);  break;
			}
		}			
	}
}

//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------
