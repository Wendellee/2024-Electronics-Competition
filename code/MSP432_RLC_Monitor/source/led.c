#include "led.h"
#include <stdint.h>
#include "stdbool.h"


void led_init()
{   SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))
    {
    }
		  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, LED1_PIN);
	  GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, LED2_PIN);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED3_PIN);
	  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED4_PIN);
}
// use Hex to control LEDs on MSP431e401 for example,input 0xf(1111),then light all the leds,input 0x3,light the led1 and led2(0011)
void led_control(int num)
{
    if(num & 0x8) {
        GPIOPinWrite(GPIO_PORTN_BASE, LED1_PIN, LED1_PIN);
    } else {
        GPIOPinWrite(GPIO_PORTN_BASE, LED1_PIN, 0x00);
    }

    if(num & 0x4) {
        GPIOPinWrite(GPIO_PORTF_BASE, LED3_PIN, LED3_PIN);
    } else {
        GPIOPinWrite(GPIO_PORTF_BASE, LED3_PIN, 0x00);
    }

    if(num & 0x2) {
        GPIOPinWrite(GPIO_PORTN_BASE, LED2_PIN, LED2_PIN);
    } else {
        GPIOPinWrite(GPIO_PORTN_BASE, LED2_PIN, 0x00);
    }

    if(num & 0x1) {
        GPIOPinWrite(GPIO_PORTF_BASE, LED4_PIN, LED4_PIN);
    } else {
        GPIOPinWrite(GPIO_PORTF_BASE, LED4_PIN, 0x00);
    }
}
