#include "uart.h"

uint8_t u_buf[1024];//printf需要的数组
extern uint32_t ui32SysClock;

//*****************************************************************************
//
// The UART interrupt handler.
//
//*****************************************************************************
void UART0_IRQHandler(void)
{
    uint32_t ui32Status;
    // Get the interrrupt status.
    ui32Status = MAP_UARTIntStatus(UART0_BASE, true);
    // Clear the asserted interrupts.
    MAP_UARTIntClear(UART0_BASE, ui32Status);
    // Loop while there are characters in the receive FIFO.
    //如果接收FIFO中有数据，则返回true;如果接收FIFO 中没有数据，则返回false
    while(MAP_UARTCharsAvail(UART0_BASE))
    {
        // Read the next character from the UART and write it back to the UART.
        MAP_UARTCharPutNonBlocking(UART0_BASE,MAP_UARTCharGetNonBlocking(UART0_BASE));//调用此函数要先调用MAP_UARTCharsAvail函数
																		//*检查有没有可用的接收数据，接收字符串函数返回字符指针,接收的数据要有“\n”结束
        // Blink the LED to show a character transfer is occuring.
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
        // Delay for 1 millisecond.  Each SysCtlDelay is about 3 clocks.
        SysCtlDelay(ui32SysClock / (1000 * 3));
        // Turn off the LED
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
    }
}

void USART2_IRQHandler(void)
{
	uint32_t ui32Status;
    // Get the interrrupt status.
    ui32Status = MAP_UARTIntStatus(UART2_BASE, true);
    // Clear the asserted interrupts.
    MAP_UARTIntClear(UART2_BASE, ui32Status);
    // Loop while there are characters in the receive FIFO.
    //如果接收FIFO中有数据，则返回true;如果接收FIFO 中没有数据，则返回false
//    while(MAP_UARTCharsAvail(UART2_BASE))
//    {
        // Read the next character from the UART and write it back to the UART.
        MAP_UARTCharPutNonBlocking(UART2_BASE,MAP_UARTCharGetNonBlocking(UART2_BASE));//调用此函数要先调用MAP_UARTCharsAvail函数
																		//*检查有没有可用的接收数据，接收字符串函数返回字符指针,接收的数据要有“\n”结束
        // Blink the LED to show a character transfer is occuring.
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_4, GPIO_PIN_5);
        // Delay for 1 millisecond.  Each SysCtlDelay is about 3 clocks.
        SysCtlDelay(ui32SysClock / (1000 * 3));
        // Turn off the LED
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0);
    //}
//	uint32_t re_buf;
//	//读取中断状态
//	uint32_t status = UARTIntStatus( UART2_BASE,  true);
//	//清除中断标志位
//	UARTIntClear( UART2_BASE,  status);
//	//判断UART0有没有字符未读取
//	while(UARTCharsAvail( UART2_BASE))
//	{
//		//如果有字符为读取就取出，使用UARTCharGetNonBlocking防止等待
//		re_buf = UARTCharGetNonBlocking( UART2_BASE);
//		//将读取出的字符再发送
//		UARTCharPutNonBlocking( UART2_BASE, re_buf);
//	}
}
//*****************************************************************************
//
// Send a string to the UART.
//
//*****************************************************************************
void UARTSend(uint32_t ui32Base, const uint8_t *pui8Buffer, uint32_t ui32Count)
{
    //
    // Loop while there are more characters to send.
    //
    while(ui32Count--)
    {
        //
        // Write the next character to the UART.
        //
        MAP_UARTCharPutNonBlocking(ui32Base, *pui8Buffer++);//发送字符串的函数
    }
}


void uart0_init(void)
{
    /* Enable the clock to GPIO port A and UART 0 */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    /* Configure the GPIO Port A for UART 0 */
    MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
    MAP_GPIOPinConfigure(GPIO_PA1_U0TX);
    MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    /* Configure the UART for 115200 bps 8-N-1 format */
    MAP_UARTConfigSetExpClk(UART0_BASE, ui32SysClock, 115200,
                            (UART_CONFIG_WLEN_7 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_EVEN));
	
//    /* Enable the clock to GPIO port A and UART 0 */
//    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
//    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

//    /* Configure the GPIO Port A for UART 0 */
//    MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
//    MAP_GPIOPinConfigure(GPIO_PA1_U0TX);
//    MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

//    /* Configure the UART for 115200 bps 8-N-1 format */
//    UARTStdioConfig(0, 115200, ui32SysClock);
}

void uart2_init(void)
{
/* Enable the clock to GPIO port A and UART 0 */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);

    //
    // Enable processor interrupts.
    //
    MAP_IntMasterEnable();

    /* Configure the GPIO Port A for UART 0 */
    MAP_GPIOPinConfigure(GPIO_PD4_U2RX);
    MAP_GPIOPinConfigure(GPIO_PD5_U2TX);
    MAP_GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_4 | GPIO_PIN_5);

    /* Configure the UART for 115200 bps 8-N-1 format */
    UARTStdioConfig(2, 115200, ui32SysClock);

    //
    // Enable the UART interrupt.
    //
    MAP_IntEnable(INT_UART2);
    MAP_UARTIntEnable(UART2_BASE, UART_INT_RX | UART_INT_RT);
		/*UART 可用的中断类型：
													UART_INT_9BIT - 9位地址匹配中断
													UART_INT_OE - 溢出错误中断
													UART_INT_BE - 中断错误中断
													UART_INT_PE - 奇偶校验错误中断
													UART_INT_FE - 帧错误中断
													UART_INT_RT - 接收超时中断
													UART_INT_TX - 发送中断
													UART_INT_RX - 接收中断
													UART_INT_DSR - DSR中断
													UART_INT_DCD - DCD中断
													UART_INT_CTS - CTS中断
													UART_INT_RI - RI中断
		****************************************************************/
}










