/**
 * @file relay_isr.c
 * @brief Relay
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2020-12-13
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-13 <td>1.0     <td>rock     <td>Modify Content
 * </table>
 */

#include "dtu.h"
#include "adc.h"
#ifdef SIMULATOR
#else
#include "debug_console_imx.h"
#include "lock.h"
#endif

#include "relay_fft.h"
#include "relay_yc.h"

extern void reverse_array(short *des, short *src, short row_len, short col_len);

short adc_buf[ADC_BUF_COUNT_DEFAULT][CONFIG_ADC_CHANNEL_NUMBER];
short adc_buf_t[CONFIG_ADC_CHANNEL_NUMBER][ADC_BUF_COUNT_DEFAULT];
float adc_data_orig[CONFIG_ADC_CHANNEL_NUMBER][ADC_BUF_COUNT_DEFAULT];

float yc_adc_getbuf[CONFIG_ADC_CHANNEL_NUMBER][ADC_WAVE_SAMPLE_POINT];
float yc_adc_result[CONFIG_ADC_CHANNEL_NUMBER];

float yc_zero_buf[ZERO_NUM][ADC_WAVE_SAMPLE_POINT];
float yc_zero_result[ZERO_NUM];

float yc_line_vol_buf[LINE_VOL_NUM][ADC_WAVE_SAMPLE_POINT];
float yc_line_vol_result[LINE_VOL_NUM];

float fft_getbuf[CONFIG_ADC_CHANNEL_NUMBER][FFT_POINT];
float fft_buf[CONFIG_ADC_CHANNEL_NUMBER][FFT_POINT];

struct harm harm1;
struct harm harm2;

short flip_cnt = 0;
short int_cnt = 0;
short yc_get_cnt = 0;
short rmscal_start = 0;
extern float coff_adjust[CONFIG_ADC_CHANNEL_NUMBER];

/**
 * @brief m4主中断
 */
void relay_isr(void)
{
	short i, j;
#ifdef SIMULATOR
	adc_get((short *)adc_buf);
	// printf("%d\n", adc_buf[0][0]);
	// printf("%d\n", adc_buf[1][0]);
	// printf("%d\n", adc_buf[2][0]);
	// printf("%d\n", adc_buf[3][0]);
#else
	PRINTF("=================================\r\n");
	mem_mutex_lock();
	adc_get((short *)adc_buf);
	mem_mutex_unlock();

	for (int i = 0; i < 80; i++) {
		PRINTF("%d\t", adc_buf[0][i]);
		PRINTF("%d\t", adc_buf[1][i]);
		PRINTF("%d\t", adc_buf[2][i]);
		PRINTF("%d\t", adc_buf[3][i]);
		PRINTF("\r\n");
	}

#endif
	reverse_array((short *)adc_buf_t, (short *)adc_buf, CONFIG_ADC_CHANNEL_NUMBER, ADC_BUF_COUNT_DEFAULT);
	cal_adjust((short *)adc_buf_t, (float *)adc_data_orig, CONFIG_ADC_CHANNEL_NUMBER, ADC_BUF_COUNT_DEFAULT, coff_adjust);

	if (rmscal_start == 0) {
		for (i = 0; i < CONFIG_ADC_CHANNEL_NUMBER; i++) {
			for (j = 0; j < ADC_BUF_COUNT_DEFAULT; j++) {
				yc_adc_getbuf[i][yc_get_cnt * ADC_BUF_COUNT_DEFAULT + j] = adc_data_orig[i][j];
			}
		}
		yc_get_cnt ++;
		if (yc_get_cnt >= FFT_POINT) {
			rmscal_start = 1;
			yc_get_cnt = 0;
		}
	}
	for (i = 0; i < CONFIG_ADC_CHANNEL_NUMBER; i++) {
		fft_buf[i][int_cnt] = adc_data_orig[i][ADC_BUF_COUNT_DEFAULT - 1];
	}
	int_cnt++;
	if (int_cnt >= FFT_POINT) {
		fft_cal_harm1(&harm1, CONFIG_ADC_CHANNEL_NUMBER);
		fft_cal_harm2(&harm2, CONFIG_ADC_CHANNEL_NUMBER);
		int_cnt = 0;
	}
}