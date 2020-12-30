/**
 * @file timer.c
 * @brief timer
 * @author jiashipeng (1060728573@qq.com)
 * @version 1.0
 * @date 2020-12-22
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-22 <td>1.0     <td>jiashipeng     <td>timer
 * </table>
 */
#include "clock_freq.h"
#include "epit.h"
#include "board.h"

static uint32_t freqB;
/**
 * @brief  init timer
 *
 */
void timer_init(void)
{
	epit_init_config_t config = {
		.freeRun = true,
		.waitEnable = true,
		.stopEnable = true,
		.dbgEnable = true,
		.enableMode = true
	};
	/* Initialize EPIT module */
	EPIT_Init(BOARD_EPITB_BASEADDR, &config);
	/* Set EPIT clock source */
	EPIT_SetClockSource(BOARD_EPITB_BASEADDR, epitClockSourceLowFreq);
	/* Divide EPITB clock source frequency by 2 inside EPIT module */
	EPIT_SetPrescaler(BOARD_EPITB_BASEADDR, 0);
	/* Get EPITB clock frequency, 32768Hz */
	freqB = 32768;
	EPIT_SetCounterLoadValue(BOARD_EPITB_BASEADDR, freqB);
	EPIT_SetOutputCompareValue(BOARD_EPITB_BASEADDR, 0);
	/* Set EPIT interrupt priority to same value to avoid handler preemption */
	NVIC_SetPriority(BOARD_EPITB_IRQ_NUM, 3);
	/* Enable NVIC interrupt */
	NVIC_EnableIRQ(BOARD_EPITB_IRQ_NUM);
	/* Enable EPIT Output Compare interrupt */
	EPIT_SetIntCmd(BOARD_EPITB_BASEADDR, true);
}

void timer_start(void)
{
	EPIT_Enable(BOARD_EPITB_BASEADDR);
}

/**
 * @brief stop timer
 *
 */
void timer_stop(void)
{
	/* Stop EPIT */
	EPIT_Disable(BOARD_EPITB_BASEADDR);
}

void timer_set_irq_freq(unsigned int ms)
{
	float ms_freq = 32.768;// 1ms
	EPIT_SetCounterLoadValue(BOARD_EPITB_BASEADDR, ms * ms_freq);
}
