//-----------------------------------------------------------------
//     程序延时程序头文件
// 头文件名: Delay.h
// 作    者: 凌智电子
// 开始日期: 2014-01-28
// 完成日期: 2014-01-28
// 修改日期: 2014-04-13
// 当前版本: V2.0.5
// 历史版本: 
//	 -V2.0: 基于STM32的延时:ns,10us,250us,1ms,5ms,50ms
//  -2.0.1: (2014-02-07)整理格式
//	-2.0.2: (2014-02-10)实际测试延时长度，修改部分延时参数
//  -2.0.3: (2014-02-15)时钟滴答和手工计算延时分开
//  -2.0.4: (2014-02-16)头文件中不包含其他头文件
//	-2.0.5: (2014-04-13)添加2us延时函数
//-----------------------------------------------------------------

#ifndef _USART_H
#define _USART_H

//-----------------------------------------------------------------
// 外部函数声明
//-----------------------------------------------------------------
#include <stdio.h>

//-----------------------------------------------------------------
// 外部函数声明
//-----------------------------------------------------------------
#define	CLK			(GPIOE,GPIO_Pin_6)
#define	D11			(GPIOE,GPIO_Pin_7)
#define	D10			(GPIOE,GPIO_Pin_4)
#define	D9			(GPIOE,GPIO_Pin_5)
#define	D8			(GPIOE,GPIO_Pin_2)
#define	D7			(GPIOE,GPIO_Pin_3)
#define	D6			(GPIOE,GPIO_Pin_0)
#define	D5			(GPIOE,GPIO_Pin_1)
#define	D4			(GPIOB,GPIO_Pin_6)
#define	D3			(GPIOB,GPIO_Pin_7)
#define	D2			(GPIOB,GPIO_Pin_4)
#define	D1			(GPIOB,GPIO_Pin_5)
#define	D0			(GPIOB,GPIO_Pin_2)
#define	ORT			(GPIOB,GPIO_Pin_3)

#define D11_IS_H (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)==Bit_RESET)
#define D10_IS_H (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)==Bit_RESET)
#define D9_IS_H  (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)==Bit_RESET)
#define D8_IS_H  (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)==Bit_RESET)
#define D7_IS_H  (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)==Bit_RESET)
#define D6_IS_H  (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)==Bit_RESET)
#define D5_IS_H  (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10)==Bit_RESET)
#define D4_IS_H  (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11)==Bit_RESET)
#define D3_IS_H  (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_12)==Bit_RESET)
#define D2_IS_H  (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)==Bit_RESET)
#define D1_IS_H  (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14)==Bit_RESET)
#define D0_IS_H  (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15)==Bit_RESET)

#define CLK_L			GPIO_ResetBits(GPIOC,GPIO_Pin_3)
#define CLK_H			GPIO_SetBits(GPIOC,GPIO_Pin_3)

// #define	D11_L		GPIO_ResetBits(GPIOC,GPIO_Pin_4)
// #define	D11_H		GPIO_SetBits(GPIOC,GPIO_Pin_4)

// #define	D10_L		GPIO_ResetBits(GPIOC,GPIO_Pin_5)
// #define	D10_H		GPIO_SetBits(GPIOC,GPIO_Pin_5)

// #define	D9_L		GPIO_ResetBits(GPIOC,GPIO_Pin_6)
// #define	D9_H		GPIO_SetBits(GPIOC,GPIO_Pin_6)

// #define	D8_L		GPIO_ResetBits(GPIOC,GPIO_Pin_7)
// #define	D8_H		GPIO_SetBits(GPIOC,GPIO_Pin_7)

// #define	D7_L		GPIO_ResetBits(GPIOC,GPIO_Pin_8)
// #define	D7_H		GPIO_SetBits(GPIOC,GPIO_Pin_8)

// #define	D6_L		GPIO_ResetBits(GPIOC,GPIO_Pin_9)
// #define	D6_H		GPIO_SetBits(GPIOC,GPIO_Pin_9)

// #define	D5_L		GPIO_ResetBits(GPIOC,GPIO_Pin_10)
// #define	D5_H		GPIO_SetBits(GPIOC,GPIO_Pin_10)

// #define	D4_L		GPIO_ResetBits(GPIOC,GPIO_Pin_11)
// #define	D4_H		GPIO_SetBits(GPIOC,GPIO_Pin_11)

// #define	D3_L		GPIO_ResetBits(GPIOC,GPIO_Pin_12)
// #define	D3_H		GPIO_SetBits(GPIOC,GPIO_Pin_12)

// #define	D2_L		GPIO_ResetBits(GPIOC,GPIO_Pin_13)
// #define	D2_H		GPIO_SetBits(GPIOC,GPIO_Pin_13)

// #define	D1_L		GPIO_ResetBits(GPIOC,GPIO_Pin_14)
// #define	D1_H		GPIO_SetBits(GPIOC,GPIO_Pin_14)

// #define	D0_L		GPIO_ResetBits(GPIOC,GPIO_Pin_15)
// #define	D0_H		GPIO_SetBits(GPIOC,GPIO_Pin_15)

// #define	ORT_L		GPIO_ResetBits(GPIOC,GPIO_Pin_2)
// #define	ORT_H		GPIO_SetBits(GPIOC,GPIO_Pin_2)

//-----------------------------------------------------------------
// 外部函数声明
//-----------------------------------------------------------------
extern u16 AD9226_GetAdc(void);

#endif

//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------
