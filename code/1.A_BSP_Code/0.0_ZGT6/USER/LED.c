/* Introduce ----------------------------------------- *
	PF9	LED0
	PF10	LED1
 ----------------------------------------------------- */
/* Include ------------------------------------------- */
#include "LED.h"
/* User Temp Include --------------------------------- */
/* LWX BSP Driver Lib -------------------------------- */
/* User Define --------------------------------------- */
/* User Variable ------------------------------------- */
/* User Extern --------------------------------------- */
/* User Function ------------------------------------- */
/* Main ---------------------------------------------- */
void LED_Init(void)//PC0
{
	GPIO_InitTypeDef GPIO_Structure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	
	GPIO_Structure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Structure.GPIO_OType = GPIO_OType_PP;
	GPIO_Structure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_Structure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Structure.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOF,&GPIO_Structure);
}

void LED_Shine(uint16_t time)
{
	  GPIO_ResetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);  //PG7输出低电平
	  delay_ms(time);
	  GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);  //PG7输出低电平
	  delay_ms(time);
}


