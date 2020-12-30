
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
#ifndef SIMULATOR

#include "share_memory.h"
#include <stddef.h>
#ifdef M4FIRMWARE
#include <string.h>
#include "board.h"
#include "mu_imx.h"
#include "debug_console_imx.h"
#include "lmem.h"
#else
#include <sys/mman.h>
#include <stdio.h>
#endif

static volatile int *mem_mutex_lock_base;

/**
 * @brief mutex lock share memory addr init
 * @return int
 * 		0 success
 * 		-1 error
 */
int mem_mutex_init(unsigned int addr_base)
{
	if (addr_base == 0)
		return -1;

	mem_mutex_lock_base = (volatile int *)addr_base;
	*mem_mutex_lock_base = 0;
	*(mem_mutex_lock_base + 1) = 0;
#ifdef M4FIRMWARE
	LMEM_CleanSystemCache(LMEM);
#endif
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
	if (mem_mutex_lock_base == NULL)
		return -1;

#ifdef M4FIRMWARE
	LMEM_CleanSystemCache(LMEM);

	if (*mem_mutex_lock_base == 0) {
		*(mem_mutex_lock_base + 1) += 1;
		LMEM_CleanSystemCache(LMEM);
		return 0;
	} else {
		return -1;
	}

#else

	if (*(mem_mutex_lock_base + 1) == 0) {
		*mem_mutex_lock_base += 1;
		return 0;
	} else {
		return -1;
	}

#endif
}

/**
 * @brief mutex unlock
 * @return int
 * 		0 success
 * 		-1 error
 */
int mem_mutex_unlock(void)
{
	if (mem_mutex_lock_base == NULL)
		return -1;

#ifdef M4FIRMWARE
	LMEM_CleanSystemCache(LMEM);

	if (*(mem_mutex_lock_base + 1) != 0) {
		*(mem_mutex_lock_base + 1) -= 1;
		LMEM_CleanSystemCache(LMEM);
	}

#else

	if (*mem_mutex_lock_base != 0)
		*mem_mutex_lock_base -= 1;

#endif
	return 0;
}
#endif