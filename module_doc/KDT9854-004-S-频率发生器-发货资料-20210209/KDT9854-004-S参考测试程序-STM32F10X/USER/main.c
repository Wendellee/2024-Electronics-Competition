#include "stm32_config.h"
#include "stdio.h"
#include "led.h"
#include "key.h"
#include "timer.h"
#include "AD9854.h"

int main(void)
{
	MY_NVIC_PriorityGroup_Config(NVIC_PriorityGroup_2);	//设置中断分组
	delay_init(72);	//初始化延时函数
	LED_Init();	//初始化LED接口
//	key_init();
	AD9854_Init();
	delay_ms(100);
	AD9854_SetSine_double(10000000,4095);

//	AD9854_InitFSK();
//	AD9854_SetFSK(10000,600000);
	while(1)
	{
		AD9854_FDATA = 1;
		delay_ms(5);
		AD9854_FDATA = 0;
		delay_ms(5);

//		LED1=~LED1;
//		delay_ms(500);
//		LED2=~LED2;
//		delay_ms(100);

	}	
}

