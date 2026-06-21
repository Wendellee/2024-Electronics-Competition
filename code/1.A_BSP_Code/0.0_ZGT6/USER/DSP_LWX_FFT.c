/* Introduce ----------------------------------------- *
	
 ----------------------------------------------------- */
/* Include ------------------------------------------- */
#include "stm32f4xx.h"                  // Device header
#include "usart.h"
#include "sram.h"

#include "FFTInc.h"
#include "table_fft.h"

#include "arm_math.h"
#include "core_cm4.h"
/* User Temp Include --------------------------------- */
/* LWX BSP Driver Lib -------------------------------- */
#include "DSP_LWX_FFT.h"
/* User Define --------------------------------------- */
/* User Variable ------------------------------------- */
struct  compx s0[MAX_FFT_N];
struct  compx s1[MAX_FFT_N];
struct  compx s2[MAX_FFT_N];
/* User Extern --------------------------------------- */
extern  uint16_t BSP_G_AD_A[MAX_FFT_N];
extern  uint16_t BSP_G_AD_B[MAX_FFT_N];
extern  uint16_t BSP_G_AD_C[MAX_FFT_N];
/* User Function ------------------------------------- */
/*
*********************************************************************************************************
* 函 数 名: cfft_f32_mag
* 功能说明: 计算幅频
* 形 参：无
* 返 回 值: 无
*********************************************************************************************************
*/
void cfft_f32_mag0(void)
{
	uint32_t i;
		/* 计算一批sin，cos系数 */
#if (MAX_FFT_N != 8192) && (MAX_FFT_N != 16384)
			InitTableFFT(MAX_FFT_N);
#endif
			for(i=0; i<MAX_FFT_N; i++)
			{
			/* 波形是由直流分量，500Hz正弦波组成，波形采样率MAX_FFT_N，初始相位60° */
				s0[i].real = BSP_G_AD_A[i];//1 + cos(2*3.1415926f*500*i/MAX_FFT_N + 3.1415926f/3);
				s0[i].imag = 0;
			}
			/* MAX_FFT_N点快速FFT */ 
			cfft(s0, MAX_FFT_N);
			/* 计算幅频 */ 
			for(i=0; i<MAX_FFT_N; i++)
			{
				arm_sqrt_f32((float32_t)(s0[i].real *s0[i].real+ s0[i].imag*s0[i].imag ), &s0[i].real); 
			}
//			/* 串口打印求解的幅频 */
//			for(i=0; i<MAX_FFT_N/2; i+=15)
//			{			
//					//printf("%d\r,%f\r\n",i, s[i].real/4095);
//				//向曲线s0的通道0传输1个数据,add指令不支持跨页面
//				//printf("add s1.id,0,%d\xff\xff\xff",(int)(s[i].real/4095));
//				Serial_Printf(USART3,"add s1.id,0,%d\xff\xff\xff",(int)(s[i].real/4095));
//			}
}

/*
*********************************************************************************************************
* 函 数 名: cfft_f32_mag1
* 功能说明: 计算幅频
* 形 参：无
* 返 回 值: 无
*********************************************************************************************************
*/
void cfft_f32_mag1(void)
{
	uint32_t i;
		/* 计算一批sin，cos系数 */
#if (MAX_FFT_N != 8192) && (MAX_FFT_N != 16384)
			InitTableFFT(MAX_FFT_N);
#endif
			for(i=0; i<MAX_FFT_N; i++)
			{
			/* 波形是由直流分量，500Hz正弦波组成，波形采样率MAX_FFT_N，初始相位60° */
				s1[i].real = BSP_G_AD_B[i];//1 + cos(2*3.1415926f*500*i/MAX_FFT_N + 3.1415926f/3);
				s1[i].imag = 0;
			}
			/* MAX_FFT_N点快速FFT */ 
			cfft(s1, MAX_FFT_N);
			/* 计算幅频 */ 
			for(i=0; i<MAX_FFT_N; i++)
			{
				arm_sqrt_f32((float32_t)(s1[i].real *s1[i].real+ s1[i].imag*s1[i].imag ), &s1[i].real); 
			}
//			/* 串口打印求解的幅频 */
//			for(i=0; i<MAX_FFT_N/2; i+=15)
//			{			
//					//printf("%d\r,%f\r\n",i, s[i].real/4095);
//				//向曲线s0的通道0传输1个数据,add指令不支持跨页面
//				//printf("add s1.id,0,%d\xff\xff\xff",(int)(s[i].real/4095));
//				Serial_Printf(USART3,"add s1.id,1,%d\xff\xff\xff",(int)(s1[i].real/4095));
//			}
}
/*
*********************************************************************************************************
* 函 数 名: cfft_f32_mag2
* 功能说明: 计算幅频
* 形 参：无
* 返 回 值: 无
*********************************************************************************************************
*/
void cfft_f32_mag2(void)
{
	uint32_t i;
		/* 计算一批sin，cos系数 */
#if (MAX_FFT_N != 8192) && (MAX_FFT_N != 16384)
			InitTableFFT(MAX_FFT_N);
#endif
			for(i=0; i<MAX_FFT_N; i++)
			{
			/* 波形是由直流分量，500Hz正弦波组成，波形采样率MAX_FFT_N，初始相位60° */
				s2[i].real = BSP_G_AD_C[i];//1 + cos(2*3.1415926f*500*i/MAX_FFT_N + 3.1415926f/3);
				s2[i].imag = 0;
			}
			/* MAX_FFT_N点快速FFT */ 
			cfft(s2, MAX_FFT_N);
			/* 计算幅频 */ 
			for(i=0; i<MAX_FFT_N; i++)
			{
				arm_sqrt_f32((float32_t)(s2[i].real *s2[i].real+ s2[i].imag*s2[i].imag ), &s2[i].real); 
			}
			/* 串口打印求解的幅频 */
			for(i=0; i<MAX_FFT_N/2; i+=15)
			{			
					//printf("%d\r,%f\r\n",i, s[i].real/4095);
				//向曲线s0的通道0传输1个数据,add指令不支持跨页面
				//printf("add s1.id,0,%d\xff\xff\xff",(int)(s[i].real/4095));
				Serial_Printf(USART3,"add s1.id,1,%d\xff\xff\xff",(int)(s2[i].real/4095));
			}
}
/*
*********************************************************************************************************
* 函 数 名: PowerPhaseRadians_f32
* 功能说明: 求相位
* 形 参：_usFFTPoints 复数个数，每个复数是两个float32_t数值
* _uiCmpValue 比较值，需要求出相位的数值
* 返 回 值: 无
*********************************************************************************************************
*/
void PowerPhaseRadians_f32(uint16_t _usFFTPoints, float32_t _uiCmpValue)
{
		float32_t lX, lY;
		uint32_t i;
		float32_t phase;
		float32_t mag;
		for (i=0; i <_usFFTPoints; i++)
		{
				lX= s0[i].real; /* 实部 */
				lY= s0[i].imag; /* 虚部 */ 
				phase = atan2f(lY, lX); /* atan2求解的结果范围是(-pi, pi], 弧度制 */
				arm_sqrt_f32((float32_t)(lX*lX+ lY*lY), &mag); /* 求模 */
				if(_uiCmpValue > mag)
				{
					s0[i].real = 0;
				}
				else
				{
					s0[i].real= phase* 180.0f/3.1415926f; /* 将求解的结果由弧度转换为角度 */
				}
		}
}
/*
*********************************************************************************************************
* 函 数 名: cfft_f32_phase
* 功能说明: 计算相频
* 形 参：无
* 返 回 值: 无
*********************************************************************************************************
*/
void cfft_f32_phase(void)
{
			uint32_t i;
			/* 计算一批sin，cos系数 */
#if (MAX_FFT_N != 8192) && (MAX_FFT_N != 16384)
InitTableFFT(MAX_FFT_N);
#endif
		for(i=0; i<MAX_FFT_N; i++)
		{
			/* 波形是由直流分量，500Hz正弦波组成，波形采样率MAX_FFT_N，初始相位60° */
			s0[i].real = 1 + cos(2*3.1415926f*500*i/MAX_FFT_N + 3.1415926f/3);
			s0[i].imag = 0;
		}
		/* MAX_FFT_N点快速FFT */ 
		cfft(s0, MAX_FFT_N);
		/* 求相频 */
		PowerPhaseRadians_f32(MAX_FFT_N, 0.5f);
		/* 串口打印求解相频 */
		for(i=0; i<MAX_FFT_N; i++)
		{
		printf("%f\r\n", s0[i].real);
		}
}
