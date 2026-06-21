/**********************************************************
                       康威电子
功能：stm32f103rct6控制AD9854模块输出RFSK调制信号
接口：控制引脚接口请参照AD9854.h
时间：
版本：0.6
作者：康威电子
其他：

更多电子需求，请到淘宝店，康威电子竭诚为您服务 ^_^
https://kvdz.taobao.com/ 
**********************************************************/

#include "stm32_config.h"
#include "stdio.h"
#include "AD9854.h" 

int main(void)
{
	MY_NVIC_PriorityGroup_Config(NVIC_PriorityGroup_2);	//设置中断分组
	delay_init(72);	//初始化延时函数
	delay_ms(500);//延时一会儿，等待上电稳定,确保AD9854比控制板先上电。
	
	//代码移植建议
	//1.修改头文件AD9854.h中，自己控制板实际需要使用哪些控制引脚。如AD9854_RD脚改成PA3控制，则定义"#define AD9854_RD PAout(3)" 
	//2.修改C文件AD9854.c中，AD9854_IO_Init函数，所有用到管脚的GPIO输出功能初始化
	//3.完成

	AD9854_IO_Init();//AD9854控制脚初始化
	AD9854_FSK_BPSK_HOLD = 0;
	AD9854_InitRFSK(AUTO);									//AUTO,自动扫频，无需外加控制脚控制；MANUAL,手动扫频，由AD9854_FSK_BPSK_HOLD引脚控制扫频
	AD9854_SetRFSK(1000,60000,100,1048575);	//扫频下限1Khz，上限60Khz，步进100hz，扫频时间约2S，扫频时间计算参考函数注解
	while(1);
}



