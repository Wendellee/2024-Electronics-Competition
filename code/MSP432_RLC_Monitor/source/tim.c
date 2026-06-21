//#include "tim.h"
//extern uint32_t ui32SysClock;

//void capture_init()         // GPIO PA7-----  Timer-3 CCP1 pin           
//{
//   MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
//    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)))
//    {
//    }

//    /* Configure the GPIO PA7 as Timer-3 CCP1 pin */
//    MAP_GPIOPinConfigure(GPIO_PA7_T3CCP1);
//    MAP_GPIOPinTypeTimer(GPIO_PORTA_BASE, GPIO_PIN_7);

//    /* Enable the Timer-3 in 16-bit Edge Time mode */
//    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);
//    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER3)))
//    {
//    }

//    MAP_TimerConfigure(TIMER3_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_CAP_TIME_UP);
//    MAP_TimerLoadSet(TIMER3_BASE, TIMER_B, ui32SysClock);   //?????60000
//    
//		MAP_TimerIntEnable(TIMER3_BASE, TIMER_CAPB_EVENT);
//    MAP_IntEnable(INT_TIMER3B);

//    MAP_TimerControlEvent(TIMER3_BASE, TIMER_B, TIMER_EVENT_NEG_EDGE);
//    MAP_TimerConfigure(TIMER3_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_CAP_TIME_UP);

////    MAP_TimerEnable(TIMER3_BASE, TIMER_B);
//    /* Enable the timer interrupt */
//}

//void enable_cap()   //when we are using,put this function in while(1)
//{
//	MAP_TimerIntEnable(TIMER3_BASE, TIMER_CAPB_EVENT);
//	MAP_TimerEnable(TIMER3_BASE, TIMER_B);
//}

//void tim0_init()
//{
//    /* 使能定时器0的时钟并且设置频率为1KHz，使能ADC触发方式为定时器0 */
//    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
//    while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)))
//    {
//    }
// 
//    MAP_TimerConfigure(TIMER0_BASE, TIMER_CFG_A_PERIODIC);
//    MAP_TimerLoadSet(TIMER0_BASE, TIMER_A, (ui32SysClock));
//		
//    MAP_TimerADCEventSet(TIMER0_BASE, TIMER_ADC_TIMEOUT_A);
//    MAP_TimerControlTrigger(TIMER0_BASE, TIMER_A, true);
//		
////    MAP_TimerEnable(TIMER0_BASE, TIMER_A);
//}

//void tim1_init()
//{
//   // Enable the GPIO port that is used for the on-board LEDs.
//    //
//    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
//    // Enable the peripherals used by this example.
//    //
//    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);	
//    // Enable processor interrupts.
//    //
//    MAP_IntMasterEnable();

//    //
//    // Configure the two 32-bit periodic timers.
//    //
//    MAP_TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
//    MAP_TimerLoadSet(TIMER1_BASE, TIMER_A, 120000000/300);
//    //
//    // Setup the interrupts for the timer timeouts.
//    //
//    MAP_IntEnable(INT_TIMER1A);
//    MAP_TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

//    //
//    // Enable the timers.
//    //
//    MAP_TimerEnable(TIMER1_BASE, TIMER_A);
//}

#include "tim.h"

extern uint32_t ui32SysClock;

void capture1_init()         // GPIO PM0-----  Timer-2 CCP0 pin           
{
   MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOM)))
    {
    }

    /* Configure the GPIO PM0 as Timer-2 CCP0 pin */
    MAP_GPIOPinConfigure(GPIO_PM0_T2CCP0);
    MAP_GPIOPinTypeTimer(GPIO_PORTM_BASE, GPIO_PIN_0);

    /* Enable the Timer-2 in 16-bit Edge Time mode */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER2)))
    {
    }

		MAP_TimerConfigure(TIMER2_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_CAP_TIME_UP);
    MAP_TimerLoadSet(TIMER2_BASE, TIMER_A, 0xFFFF);  
    TimerPrescaleSet(TIMER2_BASE, TIMER_A,120-1);
    MAP_TimerControlEvent(TIMER2_BASE, TIMER_A, TIMER_EVENT_POS_EDGE);
		
		MAP_TimerIntEnable(TIMER2_BASE, TIMER_CAPA_EVENT);
    MAP_IntEnable(INT_TIMER2A);

    MAP_TimerEnable(TIMER2_BASE, TIMER_A);
    /* Enable the timer interrupt */
}
void capture2_init()         // GPIO PM3-----  Timer-3 CCP1 pin           
{
   MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOM)))
    {
    }

    /* Configure the GPIO PM3 as Timer-3 CCP1 pin */
    MAP_GPIOPinConfigure(GPIO_PM3_T3CCP1);
    MAP_GPIOPinTypeTimer(GPIO_PORTM_BASE, GPIO_PIN_3);

    /* Enable the Timer-3 in 16-bit Edge Time mode */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);
    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER3)))
    {
    }

		MAP_TimerConfigure(TIMER3_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_CAP_TIME_UP);
    MAP_TimerLoadSet(TIMER3_BASE, TIMER_B, 0xFFFF);  
    TimerPrescaleSet(TIMER3_BASE, TIMER_B,120-1);
    MAP_TimerControlEvent(TIMER3_BASE, TIMER_B, TIMER_EVENT_POS_EDGE);
		
		MAP_TimerIntEnable(TIMER3_BASE, TIMER_CAPB_EVENT);
    MAP_IntEnable(INT_TIMER3B);

    MAP_TimerEnable(TIMER3_BASE, TIMER_B);
    /* Enable the timer interrupt */
}

void tim1_init()
{
   // Enable the GPIO port that is used for the on-board LEDs.
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    // Enable the peripherals used by this example.
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);	
    // Enable processor interrupts.
    //
    MAP_IntMasterEnable();
    
    //
    // Configure the two 32-bit periodic timers.
    //
    MAP_TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
    MAP_TimerLoadSet(TIMER1_BASE, TIMER_A, 0xFFFF);//此处分频，相隔1s的定时器，打印下来的值即为频率
    //
    // Setup the interrupts for the timer timeouts.
    //
    MAP_IntEnable(INT_TIMER1A);
    MAP_TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

    //
    // Enable the timers.
    //
    MAP_TimerEnable(TIMER1_BASE, TIMER_A);
}






