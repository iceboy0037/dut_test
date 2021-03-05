/**
 * @file dtu_param.c
 * @brief dtu device parameters
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2021-02-06
 * @copyright Copyright (c) 2020 - 2021 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-02-06 <td>1.0     <td>rock     <td> Create
 * </table>
 */

#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"
#include "dtu_config.h"
#include "dtu_param.h"
#include "tables.h"
#include "sdb.h"

int sys_read_by_ptid(struct tbl_sys_t *item, int ptid)
{
	char cmd[SQL_CMD_LEN] = { 0 };

	snprintf(cmd, SQL_CMD_LEN, "select * from tbl_sys_t where ptid=%d", ptid);
	if (sdb_select_single(cmd, &TABLE(tbl_sys), item) != 0) {
		dbg("read desc failed, ptid = %d\n", ptid);
		return -1;
	}

	return 0;
}

int sys_read_by_alias(struct tbl_sys_t *item, char *alias)
{
	char cmd[SQL_CMD_LEN] = { 0 };

	snprintf(cmd, SQL_CMD_LEN, "select * from tbl_sys_t where alias=%s", alias);
	if (sdb_select_single(cmd, &TABLE(tbl_sys), item) != 0) {
		dbg("read desc failed, ptid = %s\n", alias);
		return -1;
	}

	return 0;
}

int param_item_update(struct param_item_t *item)
{
	return 0;
}

int param_gain_read(float *ary, int start, int count)
{
	int cnt;
	struct tbl_ac_gain_t *desc;
	char cmd[SQL_CMD_LEN + 1] = { 0 };

	snprintf(cmd, SQL_CMD_LEN, "select * from tbl_ac_gain limit %d offset %d", count, start);
	cnt = sdb_select_multi(cmd, &TABLE(tbl_ac_gain), (void **)&desc, sizeof(struct tbl_ac_gain_t));
	if (cnt < 0) {
		dbg("Select failed\n");
		return -1;
	}

	for (int i = 0; i < cnt; i++) {
		ary[i] = desc[i].gain;
	}
	sdb_free(desc);
	return 0;
}

int param_gain_write(float *ary, int start, int count)
{
	char cmd[SQL_CMD_LEN + 1] = { 0 };

	for (int i = 0; i < count; i++) {
		snprintf(cmd, SQL_CMD_LEN, "update tbl_ac_gain set gain=%f where channel=%d", ary[i], start + i);
		if (sdb_update(cmd) < 0) {
			dbg("Write channel %d gain failed\n", start + i);
			return -1;
		}
	}
	return 0;
}

int param_gain_sync(void)
{
	float ary[CONFIG_ADC_CHANNEL_NUMBER];

	if (param_gain_read(ary, 0, CONFIG_ADC_CHANNEL_NUMBER) < 0) {
		dbg("Read Gain failed\n");
		return -1;
	}
#ifndef SIMULATOR
	// TODO: Set gain array to M4
#else
#endif
	return 0;
}