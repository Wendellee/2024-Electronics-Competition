#ifndef __DSP_LWX_FFT
#define __DSP_LWX_FFT

//#include "stm32f4xx.h"                  // Device header

//#include "arm_math.h"
//#include "core_cm4.h"

//#include "FFTInc.h"
//#include "table_fft.h"
//--------------------------

#define MAX_FFT_N 2048

extern struct  compx s0[MAX_FFT_N]; 
extern struct  compx s1[MAX_FFT_N];
extern struct  compx s2[MAX_FFT_N];

void cfft_f32_mag0(void);  //ADC1
void cfft_f32_mag1(void); //ADC2
void cfft_f32_mag2(void); //ADC3

void PowerPhaseRadians_f32(uint16_t _usFFTPoints, float _uiCmpValue);
void cfft_f32_phase(void);

//--------------------------

#endif


