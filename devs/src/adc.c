/**
 * @file adc.c
 * @brief ADC hw interface
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

/**
 * @brief Init ADC peripheral
 * @param  freq		ADC sample frequency
 * @param  count	ADC Sample count per period
 * @return int		0 - success 
 */
int adc_init(int freq, int count)
{
	return 0;
}

/**
 * @brief Get Current Grid frequency from FPGA
 * @param  freq		Store freq from FPGA
 * @return int 		0 - success
 */
int adc_get_freq(float *freq)
{
	return 0;
}