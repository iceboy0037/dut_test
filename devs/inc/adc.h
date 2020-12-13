/**
 * @file adc.h
 * @brief 
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

#ifndef __ADC_H__
#define __ADC_H__

#define ADC_BUF_COUNT_DEFAULT		4
#define ADC_GRID_FREQ_DEFAULT		50
#define ADC_WAVE_SAMPLE_POINT		96
#define ADC_SAMPLE_FREQ_DEFAULT		(ADC_GRID_FREQ_DEFAULT * ADC_WAVE_SAMPLE_POINT)

/**
 * @brief Init ADC peripheral
 * @param  freq		Grid frequency
 * @param  count	ADC Sample count per period
 * @return int		0 - success 
 */
extern int adc_init(int freq, int count);

/**
 * @brief Get Current Grid frequency from FPGA
 * @param  freq		Store freq from FPGA
 * @return int 		0 - success
 */
int adc_get_freq(float *freq);


#endif