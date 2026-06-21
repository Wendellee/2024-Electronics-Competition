#ifndef __CD4051_H__
#define __CD4051_H__

#include "ti/devices/msp432e4/driverlib/driverlib.h"

#define Switch1_GPIO_Port    GPIO_PORTQ_BASE
#define Switch2_GPIO_Port    GPIO_PORTQ_BASE
#define Switch3_GPIO_Port    GPIO_PORTQ_BASE
//#define Switch4_GPIO_Port    GPIO_PORTB_BASE
//#define Switch5_GPIO_Port    GPIO_PORTB_BASE

#define Switch1_PIN 	 GPIO_PIN_1
#define Switch2_PIN 	 GPIO_PIN_2
#define Switch3_PIN 	 GPIO_PIN_3
//#define Switch4_PIN 	 GPIO_PIN_2
//#define Switch5_PIN 	 GPIO_PIN_3

#define Switch1_On  GPIOPinWrite(Switch1_GPIO_Port, Switch1_PIN, Switch1_PIN)
#define Switch2_On GPIOPinWrite(Switch2_GPIO_Port, Switch2_PIN, Switch2_PIN)
#define Switch3_On  GPIOPinWrite(Switch3_GPIO_Port, Switch3_PIN, Switch3_PIN)
//#define Switch4_On  GPIOPinWrite(Switch4_GPIO_Port, Switch4_PIN, Switch4_PIN)
//#define Switch5_On  GPIOPinWrite(Switch5_GPIO_Port, Switch5_PIN, Switch5_PIN)
#define Switch1_Off GPIOPinWrite(Switch1_GPIO_Port, Switch1_PIN, 0)
#define Switch2_Off  GPIOPinWrite(Switch2_GPIO_Port, Switch2_PIN, 0)
#define Switch3_Off GPIOPinWrite(Switch3_GPIO_Port, Switch3_PIN, 0)
//#define Switch4_Off GPIOPinWrite(Switch4_GPIO_Port, Switch4_PIN, 0)
//#define Switch5_Off GPIOPinWrite(Switch5_GPIO_Port, Switch5_PIN, 0)

void CD4051_Init(void);
void CD4051_Select_Channel(uint8_t Channel);
#endif 


