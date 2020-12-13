/**
 * @file devs.c
 * @brief dtu simulator
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
#include "simulator.h"
#include "devs.h"
#include "rdb.h"

static int do_buf[CONFIG_DO_NUMBER];
static int di_buf[CONFIG_DI_NUMBER];
static int pwr_di_buf[CONFIG_PWR_DI_NUMBER];

struct sim_do_t sim_do = {
	.count = CONFIG_DO_NUMBER,
	.buf = do_buf
};
struct sim_di_t sim_di = {
	.count = CONFIG_DI_NUMBER,
	.buf = di_buf
};
struct sim_di_t sim_pwr_di = {
	.count = CONFIG_PWR_DI_NUMBER,
	.buf = pwr_di_buf
};


int sim_do_set(int *buf, int start, int count);
int sim_di_get(int *buf, int start, int count);