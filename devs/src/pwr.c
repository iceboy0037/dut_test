/**
 * @file pwr.c
 * @brief Power board interface
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2020-12-12
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-12 <td>1.0     <td>rock     <td>Modify Content
 * </table>
 */
#include "pwr.h"
#if !defined SIMULATOR && defined M4FIRMWARE
#include "mu_imx.h"
#include "mu.h"
#endif

/**
 * @brief Get DI status from power board
 * @param  buf         store DI status
 * @param  start       DI index
 * @param  count       DI Count
 * @return int 0 - success
 */
int pwr_di_get(int *buf, int start, int count)
{
	return 0;
}

#ifndef SIMULATOR
/**
 * @brief power board qdj interface
 * @param  value            1 or 0
 * @return int 0 - success
 */
int pwr_qdj_set(int value)
{
#ifdef M4FIRMWARE
	MU_SendMsg(MUB, MU_CH, M4 | (PWR_QDJ << CMD_POS) | (value & 0xFF));
#else
	// todo: A9 set
#endif
	return 0;
}

/**
 * @brief power board activation interface
 * @param  index            index
 * @param  value            1 or 0
 * @return int 0 - success
 */
int pwr_activation_set(int index, int value)
{
	if (index > PWR_ACTIVATION_LIMIT) {
		return -1;
	}

#ifdef M4FIRMWARE
	int data = 0;
	data = (index & 0xFF) << 8 | (value & 0xFF);
	MU_SendMsg(MUB, MU_CH, M4 | (PWR_ACTIVATION << CMD_POS) | data);
#else
	// todo: A9 set
	// data = value ? 1 : 0;
#endif
	return 0;
}
#endif
