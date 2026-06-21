


//#ifndef __ADS112C04_HAL_H
//#define	__ADS112C04_HAL_H

//#include "ti/devices/msp432e4/driverlib/driverlib.h"
//#include "ADS112C04_i2c.h"


//#define ADS112_DEV_ADDR  0X80

//// Single Conversion Timeout (millis)
//// The maximum time we will wait for DRDY to go valid for a single conversion
//#define ADS122C04_CONVERSION_TIMEOUT 75

//// Define 2/3/4-Wire, Temperature and Raw modes
//#define ADS122C04_4WIRE_MODE         0x0
//#define ADS122C04_3WIRE_MODE         0x1
//#define ADS122C04_2WIRE_MODE         0x2
//#define ADS122C04_TEMPERATURE_MODE   0x3
//#define ADS122C04_RAW_MODE           0x4
//#define ADS122C04_4WIRE_HI_TEMP      0x5
//#define ADS122C04_3WIRE_HI_TEMP      0x6
//#define ADS122C04_2WIRE_HI_TEMP      0x7

//// ADS122C04 Table 16 in Datasheet
//#define ADS122C04_RESET_CMD          0x06     //0000 011x      Reset
//#define ADS122C04_START_CMD          0x08     //0000 100x      Start/Sync
//#define ADS122C04_POWERDOWN_CMD      0x02     //0000 001x      PowerDown
//#define ADS122C04_RDATA_CMD          0x10     //0001 xxxx      RDATA
//#define ADS122C04_RREG_CMD           0x20     //0010 rrxx      Read REG rr= register address 00 to 11
//#define ADS122C04_WREG_CMD           0x40     //0100 rrxx      Write REG rr= register address 00 to 11

//#define ADS122C04_WRITE_CMD(reg)     (ADS122C04_WREG_CMD | (reg << 2))    //Shift is 2-bit in ADS122C04
//#define ADS122C04_READ_CMD(reg)      (ADS122C04_RREG_CMD | (reg << 2))    //Shift is 2-bit in ADS122C04

//// ADS112C04 Registor Addr
//#define ADS112_Wreg_0	          ((uint8_t)0x43)//00 11
//#define ADS112_Wreg_1	          ((uint8_t)0x47)//01 11
//#define ADS112_Wreg_2	          ((uint8_t)0x4b)//10 11
//#define ADS112_Wreg_3			      ((uint8_t)0x4f)//11 11

//#define ADS112_Rreg_0	          ((uint8_t)0x23)
//#define ADS112_Rreg_1	          ((uint8_t)0x27)
//#define ADS112_Rreg_2	          ((uint8_t)0x2b)
//#define ADS112_Rreg_3			      ((uint8_t)0x2f)

//// ADS122C04 Table 16 in Datasheet
//#define ADS122C04_CONFIG_0_REG      0 // Configuration Register 0
//#define ADS122C04_CONFIG_1_REG      1 // Configuration Register 1
//#define ADS122C04_CONFIG_2_REG      2 // Configuration Register 2
//#define ADS122C04_CONFIG_3_REG      3 // Configuration Register 3

//// Unshifted register definitions
//// The bit field register definitions will do the bit shifting

//// Configuration Register 0
//// ADS122C04 Table 19 in Datasheet

//// Input Multiplexer Configuration
//#define ADS122C04_MUX_AIN0_AIN1    	0x0
//#define ADS122C04_MUX_AIN0_AIN2     0x1
//#define ADS122C04_MUX_AIN0_AIN3     0x2
//#define ADS122C04_MUX_AIN1_AIN0     0x3
//#define ADS122C04_MUX_AIN1_AIN2     0x4
//#define ADS122C04_MUX_AIN1_AIN3     0x5
//#define ADS122C04_MUX_AIN2_AIN3     0x6
//#define ADS122C04_MUX_AIN3_AIN2     0x7
//#define ADS122C04_MUX_AIN0_AVSS     0x8
//#define ADS122C04_MUX_AIN1_AVSS     0x9
//#define ADS122C04_MUX_AIN2_AVSS     0xa
//#define ADS122C04_MUX_AIN3_AVSS     0xb
//#define ADS122C04_MUX_REFPmREFN     0xc
//#define ADS122C04_MUX_AVDDmAVSS     0xd
//#define ADS122C04_MUX_SHORTED       0xe

//// Gain Configuration
//#define ADS122C04_GAIN_1            0x0
//#define ADS122C04_GAIN_2            0x1
//#define ADS122C04_GAIN_4            0x2
//#define ADS122C04_GAIN_8            0x3
//#define ADS122C04_GAIN_16           0x4
//#define ADS122C04_GAIN_32           0x5
//#define ADS122C04_GAIN_64           0x6
//#define ADS122C04_GAIN_128          0x7

//// PGA Bypass (PGA is disabled when the PGA_BYPASS bit is set)
//#define ADS122C04_PGA_DISABLED      0x1
//#define ADS122C04_PGA_ENABLED       0x0

//// Configuration Register 1
//// ADS122C04 Table 19 in Datasheet

//// Data Rate
//// Turbo mode = Normal mode * 2 (Samples per Second)
//// Normal mode
//#define ADS122C04_DATA_RATE_20SPS   0x0
//#define ADS122C04_DATA_RATE_45SPS   0x1
//#define ADS122C04_DATA_RATE_90SPS   0x2
//#define ADS122C04_DATA_RATE_175SPS  0x3
//#define ADS122C04_DATA_RATE_330SPS  0x4
//#define ADS122C04_DATA_RATE_600SPS  0x5
//#define ADS122C04_DATA_RATE_1000SPS 0x6

//// Operating Mode
//#define ADS122C04_OP_MODE_NORMAL    0x0
//#define ADS122C04_OP_MODE_TURBO     0x1

//// Conversion Mode
//#define ADS122C04_CONVERSION_MODE_SINGLE_SHOT   0x0
//#define ADS122C04_CONVERSION_MODE_CONTINUOUS    0x1

//// Voltage Reference Selection
//#define ADS122C04_VREF_INTERNAL            0x0 //2.048V internal
//#define ADS122C04_VREF_EXT_REF_PINS        0x1 //REFp and REFn external
//#define ADS122C04_VREF_AVDD                0x2 //Analog Supply AVDD and AVSS

//// Temperature Sensor Mode
//#define ADS122C04_TEMP_SENSOR_OFF          0x0
//#define ADS122C04_TEMP_SENSOR_ON           0x1

//// Configuration Register 2
//// ADS122C04 Table 22 in Datasheet

//// Conversion Result Ready Flag (READ ONLY)

//// Conversion result ready flag
//#define ADS122C04_DRDY_DISABLE						0x0
//#define ADS122C04_DRDY_ENABLE							0x1

//// Data Counter Enable
//#define ADS122C04_DCNT_DISABLE             0x0
//#define ADS122C04_DCNT_ENABLE              0x1

//// Data Integrity Check Enable
//#define ADS122C04_CRC_DISABLED             0x0
//#define ADS122C04_CRC_INVERTED             0x1
//#define ADS122C04_CRC_CRC16_ENABLED        0x2

//// Burn-Out Current Source
//#define ADS122C04_BURN_OUT_CURRENT_OFF     0x0
//#define ADS122C04_BURN_OUT_CURRENT_ON      0x1

//// IDAC Current Setting
//#define ADS122C04_IDAC_CURRENT_OFF         0x0
//#define ADS122C04_IDAC_CURRENT_10_UA       0x1
//#define ADS122C04_IDAC_CURRENT_50_UA       0x2
//#define ADS122C04_IDAC_CURRENT_100_UA      0x3
//#define ADS122C04_IDAC_CURRENT_250_UA      0x4
//#define ADS122C04_IDAC_CURRENT_500_UA      0x5
//#define ADS122C04_IDAC_CURRENT_1000_UA     0x6
//#define ADS122C04_IDAC_CURRENT_1500_UA     0x7

//// Configuration Register 3
//// ADS122C04 Table 23 in Datasheet

//// IDAC1 Routing Configuration
//#define ADS122C04_IDAC1_DISABLED           0x0
//#define ADS122C04_IDAC1_AIN0               0x1
//#define ADS122C04_IDAC1_AIN1               0x2
//#define ADS122C04_IDAC1_AIN2               0x3
//#define ADS122C04_IDAC1_AIN3               0x4
//#define ADS122C04_IDAC1_REFP               0x5
//#define ADS122C04_IDAC1_REFN               0x6

//// IDAC2 Routing Configuration
//#define ADS122C04_IDAC2_DISABLED           0x0
//#define ADS122C04_IDAC2_AIN0               0x1
//#define ADS122C04_IDAC2_AIN1               0x2
//#define ADS122C04_IDAC2_AIN2               0x3
//#define ADS122C04_IDAC2_AIN3               0x4
//#define ADS122C04_IDAC2_REFP               0x5
//#define ADS122C04_IDAC2_REFN               0x6

//void ADS112_Init(void);
//uint8_t ADS112_WriteReg0(unsigned char arg1, unsigned char arg2, unsigned char arg3);
//uint8_t ADS112_WriteReg1(unsigned char arg1, unsigned char arg2, unsigned char arg3, unsigned char arg4, unsigned char arg5);
//uint8_t ADS112_WriteReg2(unsigned char arg1, unsigned char arg2, unsigned char arg3, unsigned char arg4, unsigned char arg5);
//uint8_t ADS112_WriteReg3(unsigned char arg1, unsigned char arg2);
//unsigned char ADS112_ReadReg(unsigned char adds);
//uint16_t ADS112_GetADC(void);	
//float ADS112_GetADC_Vol(void);															 
//void ADS112_Send_Command(uint8_t  Command);
//int ADS112_ReadData(void);

//#endif
