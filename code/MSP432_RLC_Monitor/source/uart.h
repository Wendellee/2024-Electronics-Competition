#include "ti/devices/msp432e4/driverlib/driverlib.h"
#include "stdint.h"
#include "stdbool.h"
#include "uartstdio.h"

extern uint8_t u_buf[1024];//printf需要的数组


#define printf(...)    UARTSend(UART0_BASE, (uint8_t *)u_buf, sprintf((char*)u_buf, __VA_ARGS__))
#define printf2f(...)  UARTSend(UART2_BASE, (uint8_t *)u_buf, sprintf((char*)u_buf, __VA_ARGS__))

void uart0_init(void);
void uart2_init(void);
void UART0_IRQHandler(void);//串口中断服务程序
void UARTSend(uint32_t ui32Base, const uint8_t *pui8Buffer, uint32_t ui32Count);//发送字符串函数，参数1：字符串指针  参数2：发送字符串的字符个数
void USART2_IRQHandler(void);


