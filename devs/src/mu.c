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
#include "lock.h"
#include "dio.h"

#ifdef M4FIRMWARE
#include "lmem.h"
#include "board.h"
#include "mu_imx.h"
#include "debug_console_imx.h"
#include "relay_isr.h"


int retry(int (*func)(void))
{
	int time = 3;
	int ret = 0;

	do {
		ret = func();

		if (ret == 0)
			return 0;
	} while (time--);

	return ret;
}

int feed_dog(void)
{
	int ret = 0;
	ret = MU_TrySendMsg(MUB, MU_CH, M4 | (FEED_DOG << CMD_POS));

	if (ret != kStatus_MU_Success) {
		return ret;
	}

	return ret;
}

void m4_mu_handler(void)
{
	uint32_t msg = 0;
	uint16_t mu_cmd = 0;
	uint16_t mu_data = 0;
	struct msg_t *curr_msg;

	if (MU_TryReceiveMsg(MUB, MU_CH, &msg) == kStatus_MU_Success) {
		mu_cmd = (msg & CMD_MASK) >> CMD_POS;
		mu_data = (msg & CMD_DATA_MASK);

		switch (mu_cmd) {
		case ADC_DATA:
			relay_isr();
			break;

		case MSG:
			if (mu_data == M4_SEND_OK) {
				curr_msg = (struct msg_t *)mq_curr_msg();

				if (curr_msg != NULL && curr_msg->cb != NULL) {
					curr_msg->cb(curr_msg->param);
					mq_free_msg(1);
				}
			}

			break;

		default:
			break;
		}
	}
}

#else

#endif
#endif
