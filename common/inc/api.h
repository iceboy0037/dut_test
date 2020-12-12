/**
 * @file api.h
 * @brief General platform APIs definition
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2020-12-11
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-11 <td>1.0     <td>rock     <td>内容
 * <tr><td>2020-12-11 <td>1.0     <td>rock     <td>内容
 * </table>
 */
#ifndef __API_H__
#define __API_H__


#include "dtu_types.h"
#include "dbg.h"
#include "dbs.h"
#include "devs.h"


// ADC APIs
/**
 * @brief Init ADC peripheral
 * @param  freq             ADC sample frequency
 * @param  count            ADC Sample count per period
 * @return int              0 - success
 */
int adc_init(int freq, int count);

/**
 * @brief Get Current Grid frequency from FPGA
 * @param  freq             Store freq from FPGA
 * @return int 0 - 
 */
int adc_get_freq(float *freq);


int adc_set_buff_count(int cnt);
int adc_get_buff_count(int *cnt);
int adc_get(int *buf, int count);
int adc_start(void);
int adc_stop(void);
int adc_set_freq(int freq);


#endif