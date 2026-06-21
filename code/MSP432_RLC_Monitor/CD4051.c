#include "CD4051.h"

void CD4051_Init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOQ);
	while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOQ))
	{
	}
	GPIOPinTypeGPIOOutput(GPIO_PORTQ_BASE, GPIO_PIN_1);
	GPIOPinTypeGPIOOutput(GPIO_PORTQ_BASE, GPIO_PIN_2);
	GPIOPinTypeGPIOOutput(GPIO_PORTQ_BASE, GPIO_PIN_3);
}

void CD4051_Select_Channel(uint8_t Channel)
{ 	//     C     B     A
	if(Channel == 1)//001
	{
		Switch1_On;
		Switch2_Off;
		Switch3_Off;
	}
	else if(Channel == 2)//010
	{
		Switch1_Off;
		Switch2_On;
		Switch3_Off;
	}
	else if(Channel == 3)//011
	{
		Switch1_On;
		Switch2_On;
		Switch3_Off;
	}
	else if(Channel == 4)//100
	{
		Switch1_Off;
		Switch2_Off;
		Switch3_On;
	}
	else if(Channel == 5)//101
	{
		Switch1_On;
		Switch2_Off;
		Switch3_On;
	}
	else if(Channel == 6)//110
	{
		Switch1_Off;
		Switch2_On;
		Switch3_On;
	}
	else if(Channel == 7)//111
	{
		Switch1_On;
		Switch2_On;
		Switch3_On;
	}
	else if(Channel == 0)//000
	{
		Switch1_Off;
		Switch2_Off;
		Switch3_Off;
	}
}