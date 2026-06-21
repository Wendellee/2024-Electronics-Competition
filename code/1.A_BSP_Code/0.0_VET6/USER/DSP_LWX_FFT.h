#ifndef __DSP_LWX_FFT
#define __DSP_LWX_FFT

//#include "stm32f4xx.h"                  // Device header

//#include "arm_math.h"
//#include "core_cm4.h"

//#include "FFTInc.h"
//#include "table_fft.h"
//--------------------------

void cfft_f32_mag(uint16_t *InputArray);
void PowerPhaseRadians_f32(uint16_t _usFFTPoints, float _uiCmpValue);
static void cfft_f32_phase(void);

//--------------------------

#endif


