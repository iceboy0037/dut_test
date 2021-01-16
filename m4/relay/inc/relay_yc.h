

#ifndef __RELAY_YC_H__
#define __RELAY_YC_H__

#include "adc.h"
#include "dtu.h"

#define COFF_SQUARE         0.010417
#define HF_COFFICIENT_YC    0.0208333

#define ZERO_NUM            BUS_NUMBER_MAX
#define LINE_VOL_NUM        (3 * BUS_NUMBER_MAX)

extern float yc_adc_getbuf[CONFIG_ADC_CHANNEL_NUMBER][ADC_WAVE_SAMPLE_POINT];
extern float yc_adc_result[CONFIG_ADC_CHANNEL_NUMBER];

extern float yc_zero_buf[ZERO_NUM][ADC_WAVE_SAMPLE_POINT];
extern float yc_zero_result[ZERO_NUM];

extern float yc_line_vol_buf[LINE_VOL_NUM][ADC_WAVE_SAMPLE_POINT];
extern float yc_line_vol_result[LINE_VOL_NUM];

extern void cal_adjust(short *in, float *out, short row_len, short col_len, float coff[]);

extern void cal_pqs_mode0(struct bus_config_t *config, short bus_num, short len);
extern void cal_pqs_mode1(struct bus_config_t *config, short bus_num, short len);
extern void calc_yc(struct bus_config_t *config, short bun_num, short len);

#endif