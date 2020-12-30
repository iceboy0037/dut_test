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
#endif

static short adc_buf[ADC_BUF_COUNT_DEFAULT][CONFIG_ADC_CHANNEL_NUMBER];

/**
 * @brief M4 Interrupt process
 */
void relay_isr(void)
{
	adc_get((short *)adc_buf);
#ifdef SIMULATOR
	printf("%d\n", adc_buf[0][0]);
	printf("%d\n", adc_buf[1][0]);
	printf("%d\n", adc_buf[2][0]);
	printf("%d\n", adc_buf[3][0]);
#else
	PRINTF("=================================\r\n");
	for (int i = 0; i < 80; i++) {
		PRINTF("%d\t", adc_buf[0][i]);
		PRINTF("%d\t", adc_buf[1][i]);
		PRINTF("%d\t", adc_buf[2][i]);
		PRINTF("%d\t", adc_buf[3][i]);
		PRINTF("\r\n");
	}
#endif
}