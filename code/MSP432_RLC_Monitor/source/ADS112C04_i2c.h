//#ifndef __I2C_H
//#define __I2C_H

//#include "ti/devices/msp432e4/driverlib/driverlib.h"

//#define I2C_WR	0		/* 写控制bit */
//#define I2C_RD	1		/* 读控制bit */

//////IO方向设置
////#define SDA_IN()  {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=8<<12;}
////#define SDA_OUT() {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=3<<12;}

//////IO操作函数	 
////#define IIC_SCL    PCout(12) //SCL
////#define IIC_SDA    PCout(11) //SDA	 
////#define READ_SDA   PCin(11)  //输入SDA 

///* 定义I2C总线连接的GPIO端口, 用户只需要修改下面4行代码即可任意改变SCL和SDA的引脚 */
//#define GPIO_CLK_RESET	       SYSCTL_PERIPH_GPION			/* GPIO端口 */
//#define GPIO_CLK_SCL	         SYSCTL_PERIPH_GPIOP			/* GPIO端口 */
//#define GPIO_CLK_SDA 				   SYSCTL_PERIPH_GPIOQ

//#define GPIO_PORT_RESET	       GPIO_PORTN_BASE			/* GPIO端口 */
//#define GPIO_PORT_SCL	         GPIO_PORTP_BASE			/* GPIO端口 */
//#define GPIO_PORT_SDA          GPIO_PORTQ_BASE			/* GPIO端口 */

//#define I2C_RESET_PIN		     	 GPIO_PIN_4			              /* 连接到RESET数据线的GPIO */
//#define I2C_SCL_PIN		         GPIO_PIN_4			              /* 连接到SCL时钟线的GPIO */
//#define I2C_SDA_PIN		         GPIO_PIN_0			              /* 连接到SDA数据线的GPIO */

//#define I2C_SCL_High        GPIOPinWrite(GPIO_PORT_SCL, I2C_SCL_PIN, I2C_SCL_PIN)		/* SCL = 1 */
//#define I2C_SCL_Low         GPIOPinWrite(GPIO_PORT_SCL, I2C_SCL_PIN, 0x00)   	  /* SCL = 0 */

//#define I2C_SDA_High        GPIOPinWrite(GPIO_PORT_SDA, I2C_SDA_PIN, I2C_SDA_PIN)	/* SDA = 1 */
//#define I2C_SDA_Low         GPIOPinWrite(GPIO_PORT_SDA, I2C_SDA_PIN, 0x00)   		/* SDA = 0 */
//	                         
//#define I2C_SDA_READ        GPIOPinRead(GPIO_PORT_SDA, I2C_SDA_PIN)		//读取SDA
//	                         
//#define RESET_HIGH          GPIOPinWrite(GPIO_PORT_RESET, I2C_RESET_PIN, I2C_RESET_PIN)	
//#define RESET_LOW           GPIOPinWrite(GPIO_PORT_RESET, I2C_RESET_PIN, 0x00)   	

//void ADS112C04_i2c_Start(void);
//void ADS112C04_i2c_Stop(void);
//void ADS112C04_i2c_SendByte(uint8_t _ucByte);
//uint8_t ADS112C04_i2c_ReadByte(void);
//uint8_t ADS112C04_i2c_WaitAck(void);
//void ADS112C04_i2c_Ack(void);
//void ADS112C04_i2c_NAck(void);


//uint8_t ADS112C04_i2c_CheckDevice(uint8_t _Address);



//  
//#endif
