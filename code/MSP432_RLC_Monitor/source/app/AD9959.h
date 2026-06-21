#ifndef _AD9959_H_
#define _AD9959_H_

#include "ti/devices/msp432e4/driverlib/driverlib.h"
#include "delay.h"
#include "stdint.h"
//-----------PIN-----------------------
#define RST_PIN  		GPIO_PIN_3
#define PWR_PIN  		GPIO_PIN_7

#define PS0_PIN  		GPIO_PIN_5
#define PS1_PIN  		GPIO_PIN_0
#define PS2_PIN  		GPIO_PIN_0
#define PS3_PIN  		GPIO_PIN_4

#define SDIO0_PIN      		GPIO_PIN_1
#define SDIO1_PIN  		GPIO_PIN_0
#define SDIO2_PIN  		GPIO_PIN_7
#define SDIO3_PIN  		GPIO_PIN_3

#define UPDATE_PIN 		GPIO_PIN_5//#define SDO_PIN 	 GPIO_PIN_2
#define SCLK_PIN 		GPIO_PIN_1
#define CS_PIN 	 		GPIO_PIN_0
//----------PORT-----------------
#define RST_GPIO_Port   	GPIO_PORTL_BASE
#define PWR_GPIO_Port  		GPIO_PORTK_BASE

#define PS0_GPIO_Port  		GPIO_PORTL_BASE
#define PS1_GPIO_Port  		GPIO_PORTH_BASE
#define PS2_GPIO_Port  		GPIO_PORTL_BASE
#define PS3_GPIO_Port 		GPIO_PORTL_BASE

#define SDIO0_GPIO_Port  	GPIO_PORTM_BASE
#define SDIO1_GPIO_Port  	GPIO_PORTG_BASE
#define SDIO2_GPIO_Port  	GPIO_PORTM_BASE
#define SDIO3_GPIO_Port  	GPIO_PORTF_BASE

#define UPDATE_GPIO_Port 	GPIO_PORTK_BASE//#define SDO_GPIO_Port  	 GPIO_PORTE_BASE
#define SCLK_GPIO_Port   	GPIO_PORTE_BASE
#define CS_GPIO_Port     	GPIO_PORTE_BASE

//SYC TEN RSO DPH PD PLL  
//-----------HIGH----------------------
#define RST_H    GPIOPinWrite(RST_GPIO_Port , RST_PIN , RST_PIN)
#define PWR_H    GPIOPinWrite(PWR_GPIO_Port , PWR_PIN , PWR_PIN)

#define PS0_H    GPIOPinWrite(PS0_GPIO_Port , PS0_PIN , PS0_PIN)
#define PS1_H    GPIOPinWrite(PS1_GPIO_Port , PS1_PIN , PS1_PIN)
#define PS2_H    GPIOPinWrite(PS2_GPIO_Port , PS2_PIN , PS2_PIN)
#define PS3_H    GPIOPinWrite(PS3_GPIO_Port , PS3_PIN , PS3_PIN)

#define SDIO0_H   	 GPIOPinWrite(SDIO0_GPIO_Port , SDIO0_PIN , SDIO0_PIN)
#define SDIO1_H  	 GPIOPinWrite(SDIO1_GPIO_Port , SDIO1_PIN , SDIO1_PIN)
#define SDIO2_H  	 GPIOPinWrite(SDIO2_GPIO_Port , SDIO2_PIN , SDIO2_PIN)
#define SDIO3_H  	 GPIOPinWrite(SDIO3_GPIO_Port , SDIO3_PIN , SDIO3_PIN)

#define UPDATE_H 	 GPIOPinWrite(UPDATE_GPIO_Port, UPDATE_PIN, UPDATE_PIN)//#define SDO_H 	 GPIOPinWrite(SDO_GPIO_Port , SDO_PIN , SDO_PIN)
#define SCLK_H 	 GPIOPinWrite(SCLK_GPIO_Port , SCLK_PIN , SCLK_PIN)
#define CS_H 	 GPIOPinWrite(CS_GPIO_Port , CS_PIN , CS_PIN)
//-----------LOW--------------------------------
#define RST_L    GPIOPinWrite(RST_GPIO_Port , RST_PIN , 0x00)
#define PWR_L    GPIOPinWrite(PWR_GPIO_Port , PWR_PIN , 0x00)

#define PS0_L    GPIOPinWrite(PS0_GPIO_Port, PS0_PIN, 0x00)
#define PS1_L    GPIOPinWrite(PS1_GPIO_Port, PS1_PIN, 0x00)
#define PS2_L    GPIOPinWrite(PS2_GPIO_Port, PS2_PIN, 0x00)
#define PS3_L    GPIOPinWrite(PS3_GPIO_Port, PS3_PIN, 0x00)

#define SDIO0_L  	 GPIOPinWrite(SDIO0_GPIO_Port ,SDIO0_PIN , 0x00)
#define SDIO1_L  	 GPIOPinWrite(SDIO1_GPIO_Port ,SDIO1_PIN , 0x00)
#define SDIO2_L  	 GPIOPinWrite(SDIO2_GPIO_Port ,SDIO2_PIN , 0x00)
#define SDIO3_L  	 GPIOPinWrite(SDIO3_GPIO_Port ,SDIO3_PIN , 0x00)

#define UPDATE_L 	GPIOPinWrite(UPDATE_GPIO_Port, UPDATE_PIN, 0x00)//#define SDO_L 	 GPIOPinWrite(SDO_GPIO_Port , SDO_PIN , 0x00)
#define SCLK_L 	 	GPIOPinWrite(SCLK_GPIO_Port , SCLK_PIN , 0x00)
#define CS_L 	 	GPIOPinWrite(CS_GPIO_Port , CS_PIN , 0x00)
//-----------------------------------------------
//AD9959寄存器地址定义
#define CSR_ADD   0x00   //CSR 通道选择寄存器
#define FR1_ADD   0x01   //FR1 功能寄存器1
#define FR2_ADD   0x02   //FR2 功能寄存器2
#define CFR_ADD   0x03   //CFR 通道功能寄存器

#define CFTW0_ADD 0x04   //CTW0 通道频率转换字寄存器
#define CPOW0_ADD 0x05   //CPW0 通道相位转换字寄存器
#define ACR_ADD   0x06   //ACR 幅度控制寄存器

#define LSRR_ADD  0x07   //LSR 线性扫描斜率寄存器
#define RDW_ADD   0x08   //RDW 上升扫描增量寄存器
#define FDW_ADD   0x09   //FDW 下降扫描增量寄存器

#define PROFILE_ADDR_BASE   0x0A   //Profile寄存器,配置文件寄存器起始地址

//CSR[7:4]通道选择启用位
#define CH0 0x10
#define CH1 0x20
#define CH2 0x40
#define CH3 0x80

//FR1[9:8] 调制电平选择位
#define LEVEL_MOD_2  	0x00//2电平调制 2阶调制
#define LEVEL_MOD_4		0x01//4电平调制	4阶调制
#define LEVEL_MOD_8		0x02//8电平调制	8阶调制
#define LEVEL_MOD_16	0x03//16电平调制	16阶调制

//CFR[23:22]  幅频相位（AFP）选择位
#define	DISABLE_Mod				0x00	//00	调制已禁用
#define	ASK 					0x40	//01	振幅调制，幅移键控
#define	FSK 					0x80	//10	频率调制，频移键控
#define	PSK 					0xc0	//11	相位调制，相移键控

//（CFR[14]）线性扫描启用 sweep enable																				
#define	SWEEP_ENABLE	0x40	//1	启用
#define	SWEEP_DISABLE	0x00	//0	不启用
		
void delay1 (uint32_t length);//延时
void IntReset(void);	 			//AD9959复位
void IO_Update(void); 		  //AD9959更新数据
void Intserve(void);				//IO口电平状态初始化
void AD9959_Init(void);			//IO口初始化
void AD9959_IOInit(void);
/***********************AD9959基本寄存器操作函数*****************************************/
void AD9959_WriteData(uint8_t RegisterAddress, uint8_t NumberofRegisters, uint8_t *RegisterData);//向AD9959写数据
void Write_CFTW0(uint32_t fre);										//写CFTW0通道频率转换字寄存器
void Write_ACR(uint16_t Ampli);										//写ACR通道幅度转换字寄存器
void Write_CPOW0(uint16_t Phase);									//写CPOW0通道相位转换字寄存器

void Write_LSRR(uint8_t rsrr,uint8_t fsrr);				//写LSRR线性扫描斜率寄存器
void Write_RDW(uint32_t r_delta);									//写RDW上升增量寄存器
void Write_FDW(uint32_t f_delta);									//写FDW下降增量寄存器

void Write_Profile_Fre(uint8_t profile,uint32_t data);//写Profile寄存器,频率
void Write_Profile_Ampli(uint8_t profile,uint16_t data);//写Profile寄存器,幅度
void Write_Profile_Phase(uint8_t profile,uint16_t data);//写Profile寄存器,相位
/********************************************************************************************/


/*****************************点频操作函数***********************************/
void AD9959_Set_Fre(uint8_t Channel,uint32_t Freq); //写频率
void AD9959_Set_Amp(uint8_t Channel, uint16_t Ampli);//写幅度
void AD9959_Set_Phase(uint8_t Channel,uint16_t Phase);//写相位
/****************************************************************************/

/*****************************调制操作函数  ***********************************/
void AD9959_Modulation_Init(uint8_t Channel,uint8_t Modulation,uint8_t Sweep_en,uint8_t Nlevel);//设置各个通道的调制模式。
void AD9959_SetFSK(uint8_t Channel, uint32_t *data,uint16_t Phase);//设置FSK调制的参数
void AD9959_SetASK(uint8_t Channel, uint16_t *data,uint32_t fre,uint16_t Phase);//设置ASK调制的参数
void AD9959_SetPSK(uint8_t Channel, uint16_t *data,uint32_t Freq);//设置PSK调制的参数

void AD9959_SetFre_Sweep(uint8_t Channel, uint32_t s_data,uint32_t e_data,uint32_t r_delta,uint32_t f_delta,uint8_t rsrr,uint8_t fsrr,uint16_t Ampli,uint16_t Phase);//设置线性扫频的参数
void AD9959_SetAmp_Sweep(uint8_t Channel, uint32_t s_Ampli,uint16_t e_Ampli,uint32_t r_delta,uint32_t f_delta,uint8_t rsrr,uint8_t fsrr,uint32_t fre,uint16_t Phase);//设置线性扫幅的参数
void AD9959_SetPhase_Sweep(uint8_t Channel, uint16_t s_data,uint16_t e_data,uint16_t r_delta,uint16_t f_delta,uint8_t rsrr,uint8_t fsrr,uint32_t fre,uint16_t Ampli);//设置线性扫相的参数
/********************************************************************************************/

#endif








