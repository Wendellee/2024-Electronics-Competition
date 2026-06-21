///*********************************************************************************************************
//  * @file    ads112c04_hal.c
//  * @author  
//  * @brief   ADS112C04 IIC ADC HAL module driver.
//  @verbatim
//  ==============================================================================
//                     ##### How to use this driver #####
//  ==============================================================================
//	
//	Configure GPIO in OD mode in HIGH Speed (both SDL and SCA).
//	RESET pin set 1 ( set 0 if reseting)
//	DRDY pin set 0.
//	
//	in main():
//	
//	i2c_CfgGpio();
//	ADS112_Init();
//	
//	//ADS112C04 START
//	ADS112_Send_Command(ADS122C04_START_CMD);
//	
//	//GET THE VOLTAGE FROM FUNC
//	vol = ADS112_GetADC_Vol();

//*********************************************************************************************************/
//#include "ADS112C04.h"

//void ADS112_Init(void)
//{
//	SysCtlPeripheralEnable(GPIO_CLK_RESET);
//	while (!SysCtlPeripheralReady(GPIO_CLK_RESET));
//	SysCtlPeripheralEnable(GPIO_CLK_SCL);
//	while (!SysCtlPeripheralReady(GPIO_CLK_SCL));
//	SysCtlPeripheralEnable(GPIO_CLK_SDA);
//	while (!SysCtlPeripheralReady(GPIO_CLK_SDA));
//	GPIOPinTypeGPIOOutput(GPIO_PORT_RESET, I2C_RESET_PIN	);
//	GPIOPinTypeGPIOOutput(GPIO_PORT_SCL	 , I2C_SCL_PIN		);
//	GPIOPinTypeGPIOOutput(GPIO_PORT_SDA  , I2C_SDA_PIN		);
//  RESET_HIGH;
//  ADS112_WriteReg0(ADS122C04_MUX_AIN1_AVSS,ADS122C04_GAIN_1,ADS122C04_PGA_DISABLED);
//  ADS112_WriteReg1(ADS122C04_DATA_RATE_1000SPS,ADS122C04_OP_MODE_TURBO,ADS122C04_CONVERSION_MODE_CONTINUOUS,ADS122C04_VREF_INTERNAL,ADS122C04_TEMP_SENSOR_OFF);
//  ADS112_WriteReg2(ADS122C04_DRDY_DISABLE,ADS122C04_DCNT_DISABLE,ADS122C04_CRC_DISABLED,ADS122C04_BURN_OUT_CURRENT_OFF,ADS122C04_IDAC1_DISABLED);
//  ADS112_WriteReg3(ADS122C04_IDAC1_DISABLED,ADS122C04_IDAC2_DISABLED);
//}

///*
//*********************************************************************************************************
//*	函 数 名: ADS112_WriteReg
//*	功能说明: 向ADS112中某个寄存器写入值
//*	形    参：adds：寄存器地址对应的写入指令
//						val：待写入的值
//*	返 回 值: 1：写入成功   0：写入失败
//examples(defines see ads112c04_hal.h):
//ADS112_WriteReg0(ADS122C04_MUX_AIN1_AVSS,ADS122C04_GAIN_1,ADS122C04_PGA_ENABLED);
//ADS112_WriteReg1(ADS122C04_DATA_RATE_1000SPS,ADS122C04_OP_MODE_TURBO,ADS122C04_CONVERSION_MODE_SINGLE_SHOT,ADS122C04_VREF_INTERNAL,ADS122C04_TEMP_SENSOR_OFF);
//ADS112_WriteReg2(ADS122C04_DRDY_DISABLE,ADS122C04_DCNT_DISABLE,ADS122C04_CRC_DISABLED,ADS122C04_BURN_OUT_CURRENT_OFF,ADS122C04_IDAC_CURRENT_OFF);
//ADS112_WriteReg3(ADS122C04_IDAC1_DISABLED,ADS122C04_IDAC2_DISABLED);
//*********************************************************************************************************
//*/
//uint8_t ADS112_WriteReg0(unsigned char arg1, unsigned char arg2, unsigned char arg3)
//{
//  unsigned char val = 0;
//  val = (arg1 << 4) | (arg2 << 1) | arg3;
//  ADS112C04_i2c_Start();
//  ADS112C04_i2c_SendByte(ADS112_DEV_ADDR | I2C_WR);
//  ADS112C04_i2c_WaitAck();
//  ADS112C04_i2c_SendByte(ADS112_Wreg_0);//写寄存器地址
//  ADS112C04_i2c_WaitAck();
//  ADS112C04_i2c_SendByte(val);//写数据
//  ADS112C04_i2c_WaitAck();
//  ADS112C04_i2c_Stop();
//  return 1;
//}

//uint8_t ADS112_WriteReg1(unsigned char arg1, unsigned char arg2, unsigned char arg3, unsigned char arg4, unsigned char arg5)
//{
//  unsigned char val = 0;
//  val = (arg1 << 5) | (arg2 << 4) | (arg3 << 3) | (arg4 << 1) | arg5;
//  ADS112C04_i2c_Start();
//  ADS112C04_i2c_SendByte(ADS112_DEV_ADDR | I2C_WR);
//  ADS112C04_i2c_WaitAck();
//  ADS112C04_i2c_SendByte(ADS112_Wreg_1);//写寄存器地址
//  ADS112C04_i2c_WaitAck();
//  ADS112C04_i2c_SendByte(val);//写数据
//  ADS112C04_i2c_WaitAck();
//  ADS112C04_i2c_Stop();
//  return 1;
//}
//uint8_t ADS112_WriteReg2(unsigned char arg1, unsigned char arg2, unsigned char arg3, unsigned char arg4, unsigned char arg5)
//{
//  unsigned char val = 0;
//  val = (arg1 << 7) | (arg2 << 6) | (arg3 << 4) | (arg4 << 3) | arg5;
//  ADS112C04_i2c_Start();
//  ADS112C04_i2c_SendByte(ADS112_DEV_ADDR | I2C_WR);
//  ADS112C04_i2c_WaitAck();
//  ADS112C04_i2c_SendByte(ADS112_Wreg_2);//写寄存器地址
//  ADS112C04_i2c_WaitAck();
//  ADS112C04_i2c_SendByte(val);//写数据
//  ADS112C04_i2c_WaitAck();
//  ADS112C04_i2c_Stop();
//  return 1;
//}
//uint8_t ADS112_WriteReg3(unsigned char arg1, unsigned char arg2)
//{
//  unsigned char val = 0;
//  val = (arg1 << 5) | (arg2 << 2);
//  ADS112C04_i2c_Start();
//  ADS112C04_i2c_SendByte(ADS112_DEV_ADDR | I2C_WR);
//  ADS112C04_i2c_WaitAck();
//  ADS112C04_i2c_SendByte(ADS112_Wreg_3);//写寄存器地址
//  ADS112C04_i2c_WaitAck();
//  ADS112C04_i2c_SendByte(val);//写数据
//  ADS112C04_i2c_WaitAck();
//  ADS112C04_i2c_Stop();
//  return 1;
//}

///*
//*********************************************************************************************************
//*	函 数 名: ADS112_ReadReg
//*	功能说明: 读取ADS112中某个寄存器的值
//*	形    参：adds：寄存器地址对应的读取指令
//*	返 回 值: 寄存器中的值
//*********************************************************************************************************
//*/
//unsigned char ADS112_ReadReg(unsigned char adds)
//{
//  unsigned char v;
//  ADS112C04_i2c_Start();
//  ADS112C04_i2c_SendByte(ADS112_DEV_ADDR | I2C_WR);
//  ADS112C04_i2c_WaitAck();
//  ADS112C04_i2c_SendByte(adds);
//  ADS112C04_i2c_WaitAck();
//  ADS112C04_i2c_Start();    // Repeated START condition
//  ADS112C04_i2c_SendByte(ADS112_DEV_ADDR | I2C_RD);
//  ADS112C04_i2c_WaitAck();
//  v=ADS112C04_i2c_ReadByte();
//  ADS112C04_i2c_WaitAck();
////	IIC_masterNACK();
//  ADS112C04_i2c_Stop();
//  return v;
//}

///**
//  * @brief  adc采集数值
//  * @param  none
//  * @return adcval adc读取到的数据
//	* @note		ADS112c04读取到的16位数据，即2个字节                             改过32变16
//  */
//uint16_t ADS112_GetADC(void)
//{
//  uint16_t adcVal = 0,MSB=0,LSB=0;

//  ADS112C04_i2c_Start();
//  ADS112C04_i2c_SendByte(ADS112_DEV_ADDR | I2C_WR);
//  ADS112C04_i2c_WaitAck();

//  ADS112C04_i2c_SendByte(ADS122C04_RDATA_CMD);
//  ADS112C04_i2c_WaitAck();

//  ADS112C04_i2c_Start();
//  ADS112C04_i2c_SendByte(ADS112_DEV_ADDR | I2C_RD);
//  ADS112C04_i2c_WaitAck();

//  MSB=ADS112C04_i2c_ReadByte();
//  ADS112C04_i2c_Ack();
//  LSB=ADS112C04_i2c_ReadByte();
//  ADS112C04_i2c_Stop();
//  adcVal=(MSB<<8)|LSB;
//  return adcVal;
//}

///**
//  * @brief  获取电压
//  * @param  none
//  * @return vol 转化之后的电压值
//	* @note		基准电压位2.048v
//  */
//float ADS112_GetADC_Vol(void)
//{
//  float vol = 0;
//  uint32_t temp=0;
//  temp = ADS112_GetADC();
//  vol = ((float)temp*2.048f)/32768.0f;
//  return vol;
//}

///*
//*********************************************************************************************************
//*	函 数 名: ADS112_Send_Command
//*	功能说明: 向ADS112发送指令
//*	形    参：Command：指令
//       @arg ：ADS122C04_RESET_CMD：重置
//			 @arg ：ADS122C04_START_CMD：开始或继续测量
//			 @arg ：ADS122C04_POWERDOWN_CMD：掉电
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void ADS112_Send_Command(uint8_t  Command)
//{
//  ADS112C04_i2c_Start();
//  ADS112C04_i2c_SendByte(ADS112_DEV_ADDR | I2C_WR);
//  ADS112C04_i2c_WaitAck();
//  ADS112C04_i2c_SendByte(Command);;
//  ADS112C04_i2c_WaitAck();
//  ADS112C04_i2c_Stop();
//}

///*
//*********************************************************************************************************
//*	函 数 名: ADS112_ReadData
//*	功能说明: 读取ADS112测量的电压数据
//*	形    参：无
//*	返 回 值: 电压数据
//*********************************************************************************************************
//*/
//int ADS112_ReadData(void)
//{
//  int	Date;
//  uint8_t Low=0,High=0;
//  ADS112C04_i2c_Start();
//  ADS112C04_i2c_SendByte(ADS112_DEV_ADDR | I2C_WR);
//  ADS112C04_i2c_WaitAck();
//  ADS112C04_i2c_SendByte((uint8_t)0x1f);
//  ADS112C04_i2c_WaitAck();
//  ADS112C04_i2c_Start();    // Repeated START condition
//  ADS112C04_i2c_SendByte(ADS112_DEV_ADDR | I2C_RD);
//  ADS112C04_i2c_WaitAck();
//  Low=ADS112C04_i2c_ReadByte();
//  ADS112C04_i2c_Ack();
//  High=ADS112C04_i2c_ReadByte();
//  ADS112C04_i2c_NAck();
//  ADS112C04_i2c_Stop();
//  Date=Low;
//  Date=Date<<8;
//  Date=Date|High;
//  return Date;
//}

////#define ADD_ADS112C04_write 0x80
////#define ADD_ADS112C04_read 0x81
////#define START 0x08           
////#define POWERDOWN 0x02         
////#define RDATA 0x10        
////#define RESET 0x06
////#define WREG_0 0x40
////#define WREG_1 0x44
////#define WREG_2 0x48
////#define WREG_3 0x4c
////#define RREG_0 0x20
////#define RREG_1 0x24
////#define RREG_2 0x28
////#define RREG_3 0x2c
////void WriteReg(unsigned char adds,unsigned char val)
////{	
////	IIC_start();
////	IIC_writebyte(ADD_ADS112C04_write);
////	IIC_testACK();
////	IIC_writebyte(adds);
////	IIC_testACK();
////	IIC_writebyte(val);
////	IIC_testACK();
////	IIC_stop();
////}
////unsigned char ReadReg(unsigned char adds)
////{
////	unsigned char v;
////	IIC_start();
////	IIC_writebyte(ADD_ADS112C04_write);
////	IIC_testACK();
////	IIC_writebyte(adds);
////	IIC_testACK();
////	IIC_start();    // Repeated START condition
////	IIC_writebyte(ADD_ADS112C04_read);
////	IIC_testACK();
////	v=IIC_readebyte();
////	IIC_masterNACK();
////	IIC_stop();
////	return v;
////} 
////void ADS_Start()
////{
////	IIC_start();
////	IIC_writebyte(ADD_ADS112C04_write);
////	IIC_testACK();
////	IIC_writebyte(START);
////	IIC_testACK();
////	IIC_stop();
////}
////void ADS_PowerDown()
////{
////	IIC_start();
////	IIC_writebyte(ADD_ADS112C04_write);
////	IIC_testACK();
////	IIC_writebyte(POWERDOWN);
////	IIC_testACK();
////	IIC_stop();
////}
////void ADS_Reset()
////{
////	IIC_start();
////	IIC_writebyte(ADD_ADS112C04_write);
////	IIC_testACK();
////	IIC_writebyte(RESET);
////	IIC_testACK();
////	IIC_stop();
////}

////int ReadData()
////{
////	int v;unsigned char i=0,j=0;
////	IIC_start();
////    IIC_writebyte(ADD_ADS112C04_write);
////    IIC_testACK();
////    IIC_writebyte(RDATA);
////    IIC_testACK();
////    IIC_start();    // Repeated START condition
////    IIC_writebyte(ADD_ADS112C04_read);
////    IIC_testACK();
////    i=IIC_readebyte();          
////    IIC_masterACK();
////    j=IIC_readebyte();          
////    IIC_masterNACK();
////    IIC_stop();
////	v=i;
////	v=v<<8;
////	v=v|j;
////	return v;
////} 


