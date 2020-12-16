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


static short adc_buf[ADC_BUF_COUNT_DEFAULT][CONFIG_ADC_CHANNEL_NUMBER];

/**
 * @brief M4 Interrupt process
 */
void relay_isr(void)
{
	adc_get((short *)adc_buf);
	printf("%d\n", adc_buf[0][0]);
	printf("%d\n", adc_buf[1][0]);
	printf("%d\n", adc_buf[2][0]);
	printf("%d\n", adc_buf[3][0]);
}