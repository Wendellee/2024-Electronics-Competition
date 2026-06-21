#ifndef __BSP_LWX_UART1_3_H
#define __BSP_LWX_UART1_3_H
/* Introduce ----------------------------------------- *
	
 ----------------------------------------------------- */
/* Include ------------------------------------------- */
#include "stm32f4xx.h"
#include <stdio.h>
#include <stdarg.h>
/* User Temp Include --------------------------------- */
/* LWX BSP Driver Lib -------------------------------- */
/* User Define --------------------------------------- */
/* User Variable ------------------------------------- */
/* User Extern --------------------------------------- */
/* User Function ------------------------------------- */
void uart3_init(uint32_t bound);
/**
  * 函    数：串口发送一个字节
  * 参    数：Byte 要发送的一个字节
  * 返 回 值：无
  */
void Serial_SendByte(USART_TypeDef* usart_adr,uint8_t Byte);
/**
  * 函    数：串口发送一个数组
  * 参    数：Array 要发送数组的首地址
  * 参    数：Length 要发送数组的长度
  * 返 回 值：无
  */
void Serial_SendArray(USART_TypeDef*  usart_adr,uint8_t *Array, uint16_t Length);
/**
  * 函    数：串口发送一个字符串
  * 参    数：String 要发送字符串的首地址
  * 返 回 值：无
  */
void Serial_SendString(USART_TypeDef* usart_adr,char *String);
/**
  * 函    数：次方函数（内部使用）
  * 返 回 值：返回值等于X的Y次方
  */
uint32_t Serial_Pow(uint32_t X, uint32_t Y);
/**
  * 函    数：串口发送数字
  * 参    数：Number 要发送的数字，范围：0~4294967295
  * 参    数：Length 要发送数字的长度，范围：0~10
  * 返 回 值：无
  */
void Serial_SendNumber(USART_TypeDef* usart_adr,uint32_t Number, uint8_t Length);
/**
  * 函    数：使用printf需要重定向的底层函数
  * 参    数：保持原始格式即可，无需变动
  * 返 回 值：保持原始格式即可，无需变动
  */
int my_fputc(USART_TypeDef* usart_adr,int ch, FILE *f);
/**
  * 函    数：自己封装的prinf函数
  * 参    数：format 格式化字符串
  * 参    数：... 可变的参数列表
  * 返 回 值：无
  */
void Serial_Printf(USART_TypeDef* usart_adr,char *format, ...);
/* Main ---------------------------------------------- */
void BSP_UART1_Init(uint32_t Bound1);
void BSP_UART3_Init(uint32_t Bound3);
void USART1_IRQHandler(void);
void USART3_IRQHandler(void);








#endif

