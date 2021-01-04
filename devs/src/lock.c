
/**
 * @file lock.c
 * @brief mutex lock
 * @author jiashipeng (1060728573@qq.com)
 * @version 1.0
 * @date 2020-12-16
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-16 <td>1.0     <td>jiashipeng     <td>mutex lock
 * </table>
 */
#if !defined SIMULATOR && defined M4FIRMWARE

#include "share_memory.h"
#include <stddef.h>
#include "board.h"
#include "mu_imx.h"
#include "debug_console_imx.h"
#include "sema4.h"

static uint32_t recursiveDepth;
#define MEM_LOCK_GATE (2)
/**
 * @brief mutex lock share memory addr init
 * @return int
 * 		0 success
 * 		-1 error
 */
int mem_mutex_init(void)
{
	SEMA4_ResetGate(BOARD_SEMA4_BASEADDR, MEM_LOCK_GATE);
	SEMA4_ResetNotification(BOARD_SEMA4_BASEADDR, MEM_LOCK_GATE);
	return 0;
}

/**
 * @brief mutex lock share memory addr deinit
 * @return int
 */
int mem_mutex_deinit(void)
{
	return 0;
}

/**
 * @brief mutex lock
 * @return int
 * 		0 success
 * 		-1 error
 */
int mem_mutex_lock(void)
{
	int locked = 0;
	unsigned times = 0;

	/* If already locked by this processor, just add recursive depth */
	if (SEMA4_GetLockProcessor(BOARD_SEMA4_BASEADDR, MEM_LOCK_GATE) == SEMA4_PROCESSOR_SELF) {
		recursiveDepth++;
		return 0;
	}

	while (!locked) {
		/* Enable unlock interrupt of this gate */
		SEMA4_SetIntCmd(BOARD_SEMA4_BASEADDR, SEMA4_GATE_STATUS_FLAG(MEM_LOCK_GATE), true);

		if (SEMA4_TryLock(BOARD_SEMA4_BASEADDR, MEM_LOCK_GATE) == statusSema4Success) {
			recursiveDepth++;
			/* Got the SEMA4, unlock interrupt is not needed any more */
			SEMA4_SetIntCmd(BOARD_SEMA4_BASEADDR, SEMA4_GATE_STATUS_FLAG(MEM_LOCK_GATE), false);
			locked = 1;
		}

		times++;

		if (times > 10) {
			PRINTF("\n\rwaiting for the other core unlock the gate err, lock err\n\r");
			return -1;
		}
	}

	return 0;
}

/**
 * @brief mutex unlock
 * @return int
 * 		0 success
 * 		-1 error
 */
int mem_mutex_unlock(void)
{
	if ((--recursiveDepth) == 0)
		SEMA4_Unlock(BOARD_SEMA4_BASEADDR, MEM_LOCK_GATE);

	return 0;
}
#endif