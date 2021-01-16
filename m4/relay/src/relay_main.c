/**
 * @file relay_main.c
 * @brief
 * @author liuyixi (liuyixinuaa@163.com)
 * @version 1.0
 * @date 2021-01-14
 * @copyright Copyright (c) 2020 - 2021 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-01-14 <td>1.0     <td>liuyixi     <td>主进程
 * </table>
 */
#include "rdb.h"
#include "dtu.h"
#include "adc.h"
#ifndef SIMULATOR
#include "mu.h"
#endif
#include "relay_yc.h"
#include "relay_fft.h"

extern short rmscal_start;
float coff_adjust[CONFIG_ADC_CHANNEL_NUMBER];
extern void init_yc(void);
struct bus_config_t bus_array[BUS_NUMBER_MAX];
/**
 * @brief
 * @return int
 */
int relay_main(void)
{
	short i;
	for (i = 0; i < 80; i++) {
		coff_adjust[i] = 0.00003052 *14;
	}
	init_yc();
	rdb_init();
	adc_start();
	while (1) {
#ifdef SIMULATOR
		//sleep(1);
		//dbg("relay_main....\n");
#else
		m4_mu_handler();
#endif
		if (rmscal_start == 1) {
			calc_yc(bus_array, 2, ADC_WAVE_SAMPLE_POINT);
			cal_pqs_mode0(bus_array, 2, ADC_WAVE_SAMPLE_POINT);
			yc_save_table(&yc_tbl);
			rmscal_start = 0;
		}
	}

	return 0;
}
