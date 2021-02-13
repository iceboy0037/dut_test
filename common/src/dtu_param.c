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

#include "dtu_param.h"

int param_item_read_ptid(struct param_item_t *item, int ptid)
{
	char cmd[SQL_CMD_LEN] = { 0 };

	snprintf(cmd, SQL_CMD_LEN, "select * from tbl_yx where ptid=%d", ptid);
	if (sdb_select_single(cmd, &sdb_map_param_item_desc, item) != 0) {
		dbg("read desc failed, ptid = %d\n", ptid);
		return -1;
	}

	return 0;
}

int param_item_read_alias(struct param_item_t *item, char *alias)
{
	char cmd[SQL_CMD_LEN] = { 0 };

	snprintf(cmd, SQL_CMD_LEN, "select * from tbl_yx where alias=%s", alias);
	if (sdb_select_single(cmd, &sdb_map_param_item_desc, item) != 0) {
		dbg("read desc failed, ptid = %s\n", alias);
		return -1;
	}

	return 0;
}

int param_item_update(struct param_item_t *item)
{
	return 0;
}