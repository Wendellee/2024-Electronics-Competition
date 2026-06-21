/* Introduce ----------------------------------------- *
	PC0->LED0
 ----------------------------------------------------- */
/* Include ------------------------------------------- */
#include "LED.h"
/* User Function ------------------------------------- */
void LED_Init(void)//PC0
{
	GPIO_InitTypeDef GPIO_Structure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	
	GPIO_Structure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Structure.GPIO_OType = GPIO_OType_PP;
	GPIO_Structure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Structure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Structure.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOC,&GPIO_Structure);
}

void LED_Shine(uint16_t time)
{
	 GPIO_ResetBits(GPIOC,GPIO_Pin_0);  //PG7输出低电平
	  delay_ms(time);
	  GPIO_SetBits(GPIOC,GPIO_Pin_0);  //PG7输出低电平
	  delay_ms(time);
}


