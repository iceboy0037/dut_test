/**
 * @file relay_usr.c
 * @brief
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
#ifndef SIMULATOR
#include "mu.h"
#endif
/**
 * @brief relay main entry
 * @return int 0 - success
 */
int relay_main(void)
{
	adc_start();

	while (1) {
#ifdef SIMULATOR
		sleep(1);
		dbg("relay_main....\n");
#else
		m4_mu_handler();
#endif
	}

	return 0;
}
