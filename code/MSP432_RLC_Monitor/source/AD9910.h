//////#ifndef __AD9910_H
//////#define	__AD9910_H

//////#include "ti/devices/msp432e4/driverlib/driverlib.h"
//////#include "delay.h"

//////#define RST_PIN    GPIO_PIN_3
//////#define PWR_PIN    GPIO_PIN_7
//////#define PF0_PIN    GPIO_PIN_5
//////#define PF1_PIN    GPIO_PIN_0
//////#define PF2_PIN    GPIO_PIN_0
//////#define IOUP_PIN   GPIO_PIN_4
//////#define OSK_PIN    GPIO_PIN_1
//////#define DRO_PIN  	 GPIO_PIN_0
//////#define DRC_PIN  	 GPIO_PIN_0
//////#define DRH_PIN  	 GPIO_PIN_3
//////#define SDIO_PIN 	 GPIO_PIN_5
//////#define SDO_PIN 	 GPIO_PIN_2
//////#define SCK_PIN 	 GPIO_PIN_1
//////#define CSB_PIN 	 GPIO_PIN_0

//////#define RST_GPIO_Port    GPIO_PORTL_BASE     //L3   MRT
//////#define PWR_GPIO_Port  	 GPIO_PORTK_BASE
//////#define PF0_GPIO_Port  	 GPIO_PORTL_BASE     //PF0   L5
//////#define PF1_GPIO_Port  	 GPIO_PORTH_BASE     //PF1   H0
//////#define PF2_GPIO_Port  	 GPIO_PORTL_BASE     //PF2   L0
//////#define IOUP_GPIO_Port 	 GPIO_PORTL_BASE     //IUP   L4
//////#define OSK_GPIO_Port  	 GPIO_PORTM_BASE     //OSK   M1
//////#define DRO_GPIO_Port  	 GPIO_PORTG_BASE
//////#define DRC_GPIO_Port  	 GPIO_PORTM_BASE     //DRC   M0
//////#define DRH_GPIO_Port    GPIO_PORTF_BASE     //DRH   F3
//////#define SDIO_GPIO_Port   GPIO_PORTK_BASE     //SDI   K5
//////#define SDO_GPIO_Port  	 GPIO_PORTE_BASE
//////#define SCK_GPIO_Port    GPIO_PORTE_BASE     //SCK   E1
//////#define CSB_GPIO_Port    GPIO_PORTE_BASE     //CSN   E0
//////SYC TEN RSO DPH PD PLL
//////#define RST_H    GPIOPinWrite(RST_GPIO_Port , RST_PIN , RST_PIN)
//////#define PWR_H    GPIOPinWrite(PWR_GPIO_Port , PWR_PIN , PWR_PIN)
//////#define PF0_H    GPIOPinWrite(PF0_GPIO_Port , PF0_PIN , PF0_PIN)
//////#define PF1_H    GPIOPinWrite(PF1_GPIO_Port , PF1_PIN , PF1_PIN)
//////#define PF2_H    GPIOPinWrite(PF2_GPIO_Port , PF2_PIN , PF2_PIN)
//////#define IOUP_H   GPIOPinWrite(IOUP_GPIO_Port, IOUP_PIN, IOUP_PIN)
//////#define OSK_H    GPIOPinWrite(OSK_GPIO_Port , OSK_PIN , OSK_PIN)
//////#define DRO_H  	 GPIOPinWrite(DRO_GPIO_Port , DRO_PIN , DRO_PIN)
//////#define DRC_H  	 GPIOPinWrite(DRC_GPIO_Port , DRC_PIN , DRC_PIN)
//////#define DRH_H  	 GPIOPinWrite(DRH_GPIO_Port , DRH_PIN , DRH_PIN)
//////#define SDIO_H 	 GPIOPinWrite(SDIO_GPIO_Port, SDIO_PIN, SDIO_PIN)
//////#define SDO_H 	 GPIOPinWrite(SDO_GPIO_Port , SDO_PIN , SDO_PIN)
//////#define SCK_H 	 GPIOPinWrite(SCK_GPIO_Port , SCK_PIN , SCK_PIN)
//////#define CSB_H 	 GPIOPinWrite(CSB_GPIO_Port , CSB_PIN , CSB_PIN)

//////#define RST_L    GPIOPinWrite(RST_GPIO_Port , RST_PIN , 0x00)
//////#define PWR_L    GPIOPinWrite(PWR_GPIO_Port , PWR_PIN , 0x00)
//////#define PF0_L    GPIOPinWrite(PF0_GPIO_Port , PF0_PIN , 0x00)
//////#define PF1_L    GPIOPinWrite(PF1_GPIO_Port , PF1_PIN , 0x00)
//////#define PF2_L    GPIOPinWrite(PF2_GPIO_Port , PF2_PIN , 0x00)
//////#define IOUP_L   GPIOPinWrite(IOUP_GPIO_Port, IOUP_PIN, 0x00)
//////#define OSK_L    GPIOPinWrite(OSK_GPIO_Port , OSK_PIN , 0x00)
//////#define DRO_L  	 GPIOPinWrite(DRO_GPIO_Port , DRO_PIN , 0x00)
//////#define DRC_L  	 GPIOPinWrite(DRC_GPIO_Port , DRC_PIN , 0x00)
//////#define DRH_L  	 GPIOPinWrite(DRH_GPIO_Port , DRH_PIN , 0x00)
//////#define SDIO_L 	 GPIOPinWrite(SDIO_GPIO_Port, SDIO_PIN, 0x00)
//////#define SDO_L 	 GPIOPinWrite(SDO_GPIO_Port , SDO_PIN , 0x00)
//////#define SCK_L 	 GPIOPinWrite(SCK_GPIO_Port , SCK_PIN , 0x00)
//////#define CSB_L 	 GPIOPinWrite(CSB_GPIO_Port , CSB_PIN , 0x00)

//////typedef enum 
//////{
//////	TRIG_WAVE = 0,
//////	SQUARE_WAVE,
//////	SINC_WAVE,
//////} AD9910_WAVE_ENUM;

//////void txd_8bit(uint8_t data);
//////void AD9110_IOInit(void);
//////void Init_AD9910(void);//AD9910寄存器初始化

//////void AD9910_FreWrite(uint32_t Freq);//写输出频率1KHz。范围：0~420000000，对应频率0Hz~420MHz
//////void AD9910_AmpWrite(uint16_t Amp);//写输出幅度最大。范围：0~16383对应峰峰值0mv~800mv(左右)
//////void AD9910_VrmsWrite(uint16_t Vrms);

//////void AD9910_RAM_WAVE_Set(AD9910_WAVE_ENUM wave);//设置模块输出三角波TRIG_WAVE：三角波，SQUARE_WAVE：方波，SINC_WAVE：SINC波)
//////void AD9910_DRG_FreInit_AutoSet(bool autoSweepEn);
//////void AD9910_DRG_FrePara_Set(uint32_t lowFre, uint32_t upFre, uint32_t posStep, uint32_t negStep, uint16_t posRate, uint16_t negRate);

//////#endif
