#include "button.h"
#include <stdint.h>
#include "stdbool.h"
void buttons_init(void)
{
    // ?? GPIO_PORTJ ??
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);

    // ?? GPIO_PORTJ ????
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ))
    {
    }

    // ?? BUTTON1_PIN ? BUTTON2_PIN ???,?????????
    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, BUTTON1_PIN | BUTTON2_PIN);
    GPIOPadConfigSet(GPIO_PORTJ_BASE, BUTTON1_PIN | BUTTON2_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}


uint8_t buttons_read(void)
{    // ??????,????????,?????????
    uint8_t button1_status = !(GPIOPinRead(GPIO_PORTJ_BASE, BUTTON1_PIN) & BUTTON1_PIN);
    uint8_t button2_status = !(GPIOPinRead(GPIO_PORTJ_BASE, BUTTON2_PIN) & BUTTON2_PIN);    // ??????????????,button1_status ?????,button2_status ?????
    return (button2_status << 1) | button1_status;
}

void Switch_Init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));
	GPIOPinTypeGPIOOutput(Switch1_GPIO_Port, Switch1_PIN);
}

