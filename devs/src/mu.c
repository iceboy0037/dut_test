/**
 * @file mu.c
 * @brief mu
 * @author jiashipeng (1060728573@qq.com)
 * @version 1.0
 * @date 2020-12-16
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-16 <td>1.0     <td>jiashipeng     <td>mu
 * </table>
 */
#ifndef SIMULATOR

#include "mu.h"
#include "share_memory.h"
#include "msg.h"
#include "dio.h"

#ifdef M4FIRMWARE
#include "board.h"
#include "mu_imx.h"
#include "relay_isr.h"

void m4_mu_handler(void)
{
	uint32_t msg = 0;
	uint16_t mu_cmd = 0;

	if (MU_TryReceiveMsg(MUB, MU_CH, &msg) == kStatus_MU_Success) {
		mu_cmd = (msg & CMD_MASK) >> CMD_POS;

		switch (mu_cmd) {
		case ADC_DATA:
			relay_isr();
			break;

		default:
			break;
		}
	}
}

#else

#endif
#endif
