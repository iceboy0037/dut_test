/**
 * @file common.c
 * @brief Some common functions
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2020-12-16
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-16 <td>1.0     <td>rock     <td>
 * </table>
 */
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

#if !defined SIMULATOR && defined M4FIRMWARE
#include "board.h"
#include "mu_imx.h"
#include "mu.h"
#endif
/**
 * @brief Init watchdog
 * @return int 0 - success
 */
int init_dog(void)
{
	return 0;
}

/**
 * @brief kick watchdog
 * @return int 0 - success
 */
int kick_dog(void)
{
#if !defined SIMULATOR && defined M4FIRMWARE
	int ret = 0;
	ret = MU_TrySendMsg(MUB, MU_CH, M4 | (KICK_DOG << CMD_POS));

	if (ret != kStatus_MU_Success) {
		return ret;
	}

	return ret;
#endif
	return 0;
}

/**
 * @brief Enable watchdog
 * @return int 0 - success
 */
int enable_dog(void)
{
	return 0;
}

/**
 * @brief Disable watchdog
 * @return int 0 - success
 */
int disable_dog(void)
{
	return 0;
}