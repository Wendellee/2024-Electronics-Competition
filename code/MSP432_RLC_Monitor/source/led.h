#include "ti/devices/msp432e4/driverlib/driverlib.h"

#define LED1_PIN GPIO_PIN_1 
#define LED2_PIN GPIO_PIN_0
#define LED3_PIN GPIO_PIN_4
#define LED4_PIN GPIO_PIN_0

void led_init(void);

void led_control(int num);
