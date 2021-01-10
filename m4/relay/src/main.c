/**
 * @file main.c
 * @brief M4 firmware main entry
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

#include <stdio.h>
#include "adc.h"

#ifndef SIMULATOR
#include "board.h"
#include "debug_console_imx.h"
#include "lock.h"
#include "msg.h"
#include "dio.h"
#include "epit.h"
#include "timer.h"
#include "share_memory.h"
#include "mu.h"
#include "dbg.h"
#include "common.h"
#endif

/**
 * @brief m4 firmware main entry
 * @param  argc
 * @param  argv
 * @return int
 */
int main(int argc, char *argv[])
{
	extern int relay_main(void);
#ifdef SIMULATOR
	printf("Relay Entry...\n");
#else
	hardware_init();
	timer_init();
	timer_start();
	mq_init((unsigned int)MSG_QUEUE_STRUCT_ADDR);
	mem_mutex_init();
	hw_dio_init((unsigned int)DI_ADDR);
	PRINTF("Relay Entry...\r\n");
#endif
	adc_init(ADC_GRID_FREQ_DEFAULT, ADC_WAVE_SAMPLE_POINT);
	relay_main();
	return 0;
}

#ifndef SIMULATOR
// 1s
volatile unsigned int time = 1;
void BOARD_EPITB_HANDLER(void)
{
	EPIT_ClearStatusFlag(BOARD_EPITB_BASEADDR);
	time++;

	if (time % 10 == 0) {
		dbg("now time %d\n", time);
		PRINTF("send now time %d\r\n", time);
	}

	if (time % 10 == 5) {
		do_set(12, 1);
	}

	if (time % 10 == 6) {
		event(2, 3);
	}

	if (time % 10 == 8) {
		kick_dog();
	}
}
#endif