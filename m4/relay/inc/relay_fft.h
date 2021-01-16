#ifndef __RELAY_FFT_H__
#define __RELAY_FFT_H__

#include "adc.h"
#include "dtu.h"

#define HF_COFFICIENT 0.08333333
#define FFT_POINT     24

//用作fft计算，循环80个通道做滑窗DFT
struct harm {
	float axsum[CONFIG_ADC_CHANNEL_NUMBER];
	float aysum[CONFIG_ADC_CHANNEL_NUMBER];
	float ax[CONFIG_ADC_CHANNEL_NUMBER];
	float ay[CONFIG_ADC_CHANNEL_NUMBER];
	float angel[CONFIG_ADC_CHANNEL_NUMBER];
	float result[CONFIG_ADC_CHANNEL_NUMBER];
	float fft_in[CONFIG_ADC_CHANNEL_NUMBER];
};

extern struct harm harm1;
extern struct harm harm2;//定義基波和二次諧波結構體變量
extern short flip_cnt;

extern float fft_getbuf[CONFIG_ADC_CHANNEL_NUMBER][FFT_POINT];
extern float fft_buf[CONFIG_ADC_CHANNEL_NUMBER][FFT_POINT];
extern short int_cnt;

extern void  fft_cal_harm1(struct harm *p, short channel_num);
extern void  fft_cal_harm2(struct harm *p, short channel_num);
#endif