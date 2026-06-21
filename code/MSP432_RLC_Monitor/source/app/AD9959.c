#include "AD9959.h"
//--------------------------------
uint8_t FR1_DATA[3] = {0xD0,0x00,0x00};//VCO gain control[23]=1系统时钟高于255Mhz; PLL[22:18]=10100,20倍频,20*25M=500MHZ; Charge pump control = 75uA 


uint8_t FR2_DATA[2] = {0x00,0x00};	// 双方向扫描，即从起始值扫到结束值后，又从结束值扫到起始值
//uint8_t FR2_DATA[2] = {0x80,0x00};// 单方向扫描，即从起始值扫到结束值后，又从起始值扫到结束值，以此类推


double ACC_FRE_FACTOR = 8.589934592;	//频率因子8.589934592=(2^32)/500000000 其中500M=25M*20(倍频数可编程)

uint8_t CFR_DATA[3] = {0x00,0x03,0x02};//default Value = 0x000302	   //通道功能寄存器


//---------SYSTEM FUNCTION-------------------
//延时
void delay1 (uint32_t length)
{
	length = length*12;
   while(length--);
}
/************************************************************
** 函数名称 ：void Intserve(void)		   
** 函数功能 ：IO口电平状态初始化
**************************************************************/
void Intserve(void)		   
{   
    PWR_L;
    CS_H;
    SCLK_L;
    UPDATE_L;
    PS0_L;
    PS1_L;
    PS2_L;
    PS3_L;
    SDIO0_L;
    SDIO1_L;
    SDIO2_L;
    SDIO3_L;
}
/************************************************************
** 函数名称 void IO_Update(void)  
** 函数功能 ： AD9959更新数据
**************************************************************/
void IO_Update(void)  
{
	UPDATE_L;
	delay1(2);
	UPDATE_H;
	delay1(4);
	UPDATE_L;
}
/************************************************************
** 函数名称 ：void IntReset(void)		   
** 函数功能 ：AD9959复位
**************************************************************/
void IntReset(void)	  
{
	RST_L;
	delay1(1);
	RST_H;
	delay1(30);
	RST_L;
}

void AD9959_IOInit(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
	while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOL));
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
	while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOK));
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
	while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOH));
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
	while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOM));
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
	while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOG));
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE));
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC));
	
	GPIOPinTypeGPIOOutput(RST_GPIO_Port , RST_PIN );
	GPIOPinTypeGPIOOutput(PWR_GPIO_Port , PWR_PIN );
	
	GPIOPinTypeGPIOOutput(PS0_GPIO_Port , PS0_PIN );
	GPIOPinTypeGPIOOutput(PS1_GPIO_Port , PS1_PIN );
	GPIOPinTypeGPIOOutput(PS2_GPIO_Port , PS2_PIN );
	GPIOPinTypeGPIOOutput(PS3_GPIO_Port , PS3_PIN );
	
	GPIOPinTypeGPIOOutput(SDIO0_GPIO_Port , SDIO0_PIN );
	GPIOPinTypeGPIOOutput(SDIO1_GPIO_Port , SDIO1_PIN );
	GPIOPinTypeGPIOOutput(SDIO2_GPIO_Port , SDIO2_PIN );
	GPIOPinTypeGPIOOutput(SDIO3_GPIO_Port , SDIO3_PIN );
	
	GPIOPinTypeGPIOOutput(UPDATE_GPIO_Port, UPDATE_PIN);//GPIOPinTypeGPIOOutput(SDO_GPIO_Port , SDO_PIN );
	GPIOPinTypeGPIOOutput(SCLK_GPIO_Port , SCLK_PIN );
	GPIOPinTypeGPIOOutput(CS_GPIO_Port , CS_PIN );
}



/************************************************************
** 函数名称 ：void AD9959_Init(void)  
** 函数功能 ：初始化控制AD9959需要用到的IO口,及寄存器
** 入口参数 ：无
** 出口参数 ：无
** 函数说明 ：无
**************************************************************/
void AD9959_Init(void)  
{ 
	AD9959_IOInit();
	Intserve();  //IO口电平状态初始化
	IntReset();  //AD9959复位
	
	//初始化功能寄存器
  AD9959_WriteData(FR1_ADD,3,FR1_DATA);//写功能寄存器1
  AD9959_WriteData(FR2_ADD,2,FR2_DATA);//
}
/***********************AD9959基本寄存器操作函数*****************************************/
/************************************************************
** 函数名称 ：void AD9959_WriteData(u8 RegisterAddress, u8 NumberofRegisters, u8 *RegisterData)
** 函数功能 ：使用模拟SPI向AD9959写数据
** 入口参数 ：RegisterAddress: 寄存器地址
						NumberofRegisters: 要写入的字节数
						*RegisterData: 数据起始地址
** 出口参数 ：无
** 函数说明 ：无
**************************************************************/
void AD9959_WriteData(uint8_t RegisterAddress, uint8_t NumberofRegisters, uint8_t *RegisterData)
{
	uint8_t	ControlValue = 0;
	uint8_t	ValueToWrite = 0;
	uint8_t	RegisterIndex = 0;
	uint8_t	i = 0;

	ControlValue = RegisterAddress;
//写入地址
	SCLK_L;
	CS_L;	 
	for(i=0; i<8; i++)
	{
		SCLK_L;
		if(0x80 == (ControlValue & 0x80))
		SDIO0_H;	  
		else
		SDIO0_L;	  
		SCLK_H;
		ControlValue <<= 1;
	}
	SCLK_L;
//写入数据
	for (RegisterIndex=0; RegisterIndex<NumberofRegisters; RegisterIndex++)
	{
		ValueToWrite = RegisterData[RegisterIndex];
		for (i=0; i<8; i++)
		{
			SCLK_L;
			if(0x80 == (ValueToWrite & 0x80))
			SDIO0_H;	  
			else
			SDIO0_L;	  
			SCLK_H;
			ValueToWrite <<= 1;
		}
		SCLK_L;		
	}	
  CS_H;
}
/************************************************************
** 函数名称 ：void Write_CFTW0(uint32_t fre)
** 函数功能 ：写CFTW0通道频率转换字寄存器
** 入口参数 ： Freq:	写入频率，范围0~200 000 000 Hz
** 出口参数 ：无
** 函数说明 ：无
**************************************************************/
void Write_CFTW0(uint32_t fre)
{
		uint8_t CFTW0_DATA[4] ={0x00,0x00,0x00,0x00};	//中间变量
	  uint32_t Temp;            
	  Temp=(uint32_t)fre*ACC_FRE_FACTOR;	 
	  CFTW0_DATA[3]=(uint8_t)Temp;
	  CFTW0_DATA[2]=(uint8_t)(Temp>>8);
	  CFTW0_DATA[1]=(uint8_t)(Temp>>16);
	  CFTW0_DATA[0]=(uint8_t)(Temp>>24);		
		AD9959_WriteData(CFTW0_ADD,4,CFTW0_DATA);//CTW0 address 0x04
}
/************************************************************
** 函数名称 ：void Write_ACR(uint16_t Ampli)
** 函数功能 ：写ACR通道幅度转换字寄存器
** 入口参数 ：Ampli:    输出幅度,范围0~1023，控制值0~1023对应输出幅度0~500mVpp左右
** 出口参数 ：无
** 函数说明 ：无
**************************************************************/
void Write_ACR(uint16_t Ampli)
{ 
	uint32_t A_temp=0;
	uint8_t ACR_DATA[3] = {0x00,0x00,0x00};//default Value = 0x--0000 Rest = 18.91/Iout 
  A_temp=Ampli|0x1000;
	
	ACR_DATA[1] = (uint8_t)(A_temp>>8); //高位数据
	ACR_DATA[2] = (uint8_t)A_temp;  //低位数据
  AD9959_WriteData(ACR_ADD,3,ACR_DATA); //ACR address 0x06.CHn设定幅度
}
/************************************************************
** 函数名称 ：void Write_CPOW0(uint16_t Phase)
** 函数功能 ：写CPOW0通道相位转换字寄存器
** 入口参数 ：Phase:		输出相位,范围：0~16383(对应角度：0°~360°)
** 出口参数 ：无
** 函数说明 ：无
**************************************************************/
void Write_CPOW0(uint16_t Phase)
{
	uint8_t CPOW0_data[2] = {0x00,0x00};
	CPOW0_data[1]=(uint8_t)Phase;
	CPOW0_data[0]=(uint8_t)(Phase>>8);

	AD9959_WriteData(CPOW0_ADD,2,CPOW0_data);//CPOW0 address 0x05.CHn设定相位
}



/************************************************************
** 函数名称 ：void Write_LSRR(uint8_t rsrr,uint8_t fsrr)
** 函数功能 ：写LSRR线性扫描斜率寄存器
** 入口参数 ：	rsrr:	上升斜率,范围：0~255
							fsrr:	下降斜率,范围：0~255
** 出口参数 ：无
** 函数说明 ：无
**************************************************************/
void Write_LSRR(uint8_t rsrr,uint8_t fsrr)
{
	uint8_t LSRR_data[2]={0x00,0x00};

	LSRR_data[1]=rsrr;	
	LSRR_data[0]=fsrr;//高8位下降斜率

	AD9959_WriteData(LSRR_ADD,2,LSRR_data);
}
/************************************************************
** 函数名称 ：void Write_RDW(uint32_t r_delta)
** 函数功能 ：写RDW上升增量寄存器
** 入口参数 ：r_delta:上升增量,0-4294967295
** 出口参数 ：无
** 函数说明 ：无
**************************************************************/
void Write_RDW(uint32_t r_delta)
{
		uint8_t RDW_data[4] ={0x00,0x00,0x00,0x00};	//中间变量          
 
	  RDW_data[3]=(uint8_t)r_delta;
	  RDW_data[2]=(uint8_t)(r_delta>>8);
	  RDW_data[1]=(uint8_t)(r_delta>>16);
	  RDW_data[0]=(uint8_t)(r_delta>>24);		
		AD9959_WriteData(RDW_ADD,4,RDW_data);
}
/************************************************************
** 函数名称 ：void Write_FDW(uint32_t f_delta)
** 函数功能 ：写FDW下降增量寄存器
** 入口参数 ：f_delta:下降增量,0-4294967295
** 出口参数 ：无
** 函数说明 ：无
**************************************************************/
void Write_FDW(uint32_t f_delta)
{
		uint8_t FDW_data[4] ={0x00,0x00,0x00,0x00};	//中间变量          
 
	  FDW_data[3]=(uint8_t)f_delta;
	  FDW_data[2]=(uint8_t)(f_delta>>8);
	  FDW_data[1]=(uint8_t)(f_delta>>16);
	  FDW_data[0]=(uint8_t)(f_delta>>24);		
		AD9959_WriteData(FDW_ADD,4,FDW_data);
}



/************************************************************
** 函数名称 ：void Write_Profile_Fre(uint8_t profile,uint32_t data)
** 函数功能 ：写Profile寄存器
** 入口参数 ：profile:	profile号(0~14)
							data:	写入频率，范围0~200 000 000 Hz
** 出口参数 ：无
** 函数说明 ：无
**************************************************************/
void Write_Profile_Fre(uint8_t profile,uint32_t data)
{
		uint8_t profileAddr;
		uint8_t Profile_data[4] ={0x00,0x00,0x00,0x00};	//中间变量
	  uint32_t Temp;            
	  Temp=(uint32_t)data*ACC_FRE_FACTOR;	   //将输入频率因子分为四个字节  4.294967296=(2^32)/500000000
	  Profile_data[3]=(uint8_t)Temp;
	  Profile_data[2]=(uint8_t)(Temp>>8);
	  Profile_data[1]=(uint8_t)(Temp>>16);
	  Profile_data[0]=(uint8_t)(Temp>>24);
		profileAddr = PROFILE_ADDR_BASE + profile;
		
		AD9959_WriteData(profileAddr,4,Profile_data);
}
/************************************************************
** 函数名称 ：void Write_Profile_Ampli(uint8_t profile,uint16_t data)
** 函数功能 ：写Profile寄存器
** 入口参数 ：profile:	profile号(0~14)
							data:	 写入幅度,范围0~1023，
** 出口参数 ：无
** 函数说明 ：无
**************************************************************/
void Write_Profile_Ampli(uint8_t profile,uint16_t data)
{
		uint8_t profileAddr;
		uint8_t Profile_data[4] ={0x00,0x00,0x00,0x00};	//中间变量

		//为幅度调制时幅度数据为[31:22]位
	  Profile_data[1]=(uint8_t)(data<<6);//[23:22]
	  Profile_data[0]=(uint8_t)(data>>2);//[31:24]
		
		profileAddr = PROFILE_ADDR_BASE + profile;
		
		AD9959_WriteData(profileAddr,4,Profile_data);//写入32位数据
}
/************************************************************
** 函数名称 ：void Write_Profile_Phase(uint8_t profile,uint16_t data)
** 函数功能 ：写Profile寄存器
** 入口参数 ：profile:	profile号(0~14)
							data:	 写入相位,范围：0~16383
** 出口参数 ：无
** 函数说明 ：无
**************************************************************/
void Write_Profile_Phase(uint8_t profile,uint16_t data)
{
		uint8_t profileAddr;
		uint8_t Profile_data[4] ={0x00,0x00,0x00,0x00};	//中间变量

		//为相位调制时相位数据为[31:18]位
	  Profile_data[1]=(uint8_t)(data<<2);//[23:18]
	  Profile_data[0]=(uint8_t)(data>>6);//[31:24]
		
		profileAddr = PROFILE_ADDR_BASE + profile;
		
		AD9959_WriteData(profileAddr,4,Profile_data);//写入32位数据
}


//--------
/************************************************************
** 函数名称 ：void AD9959_Set_Fre(uint8_t Channel,uint32_t Freq)
** 函数功能 ：设置通道的输出频率
** 入口参数 ：Channel:  输出通道  CH0-CH3
						 Freq:     输出频率，范围0~200 000 000 Hz
** 出口参数 ：无
** 函数说明 ：无
**************************************************************/
void AD9959_Set_Fre(uint8_t Channel,uint32_t Freq)
{	 
		uint8_t CHANNEL[1] = {0x00};
		
		CHANNEL[0]=Channel;
		AD9959_WriteData(CSR_ADD,1,CHANNEL);//控制寄存器写入CHn通道，选择CHn
    Write_CFTW0(Freq);//输出CHn设定频率																																			 
}
/************************************************************
** 函数名称 ：void AD9959_Set_Amp(uint8_t Channel, uint16_t Ampli)
** 函数功能 ：设置通道的输出幅度
** 入口参数 ：Channel:  输出通道 CH0-CH3
							Ampli:    输出幅度,范围0~1023，控制值0~1023对应输出幅度0~500mVpp左右
** 出口参数 ：无
** 函数说明 ：无
**************************************************************/
void AD9959_Set_Amp(uint8_t Channel, uint16_t Ampli)
{ 
	uint8_t CHANNEL[1] = {0x00};

	CHANNEL[0]=Channel;
	AD9959_WriteData(CSR_ADD,1,CHANNEL); //控制寄存器写入CHn通道，选择CHn
	Write_ACR(Ampli);							//	CHn设定幅度
}
/************************************************************
** 函数名称 ：void AD9959_Set_Phase(uint8_t Channel,uint16_t Phase)
** 函数功能 ：设置通道的输出相位
** 入口参数 ：Channel:  输出通道 CH0-CH3
							Phase:		输出相位,范围：0~16383(对应角度：0°~360°)
** 出口参数 ：无
** 函数说明 ：无
**************************************************************/
void AD9959_Set_Phase(uint8_t Channel,uint16_t Phase)
{
	uint8_t CHANNEL[1] = {0x00};
	CHANNEL[0]=Channel;

	AD9959_WriteData(CSR_ADD,1,CHANNEL); //控制寄存器写入CHn通道，选择CHn
	Write_CPOW0(Phase);//CHn设定相位
}