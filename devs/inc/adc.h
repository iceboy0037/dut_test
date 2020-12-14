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
 * @param  grid		Grid frequency
 * @param  count	ADC Sample count per period
 * @return int		0 - success 
 */
extern int adc_init(int grid, int count);

/**
 * @brief Get Current Grid frequency from FPGA
 * @param  freq		Store freq from FPGA
 * @return int 		0 - success
 */
int adc_get_grid_freq(float *grid_freq);

/**
 * @brief Set ADC sample buffer count
 * @param  cnt	Default = 4
 * @return int 0 - success
 */
int adc_set_buff_count(int cnt);

/**
 * @brief Read ADC sample buffer count
 * @param  cnt	Return value
 * @return int 0 - success
 */
int adc_get_buff_count(int *cnt);

/**
 * @brief Read ADC Buffer
 * @param  buf	Return ADC sample buffer, point count = adc_get_buff_count()
 * @return int 
 */
int adc_get(short *buf);

/**
 * @brief Start ADC sample, M4's relay_isr() will be called every adc_get_buff_count() points
 * @return int 
 */
int adc_start(void);

/**
 * @brief Stop ADC sample, and relay_isr() will be stop
 * @return int 
 */
int adc_stop(void);

#endif