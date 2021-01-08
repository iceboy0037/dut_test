/**
 * @file yx.c
 * @brief YX APIs
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2021-01-08
 * @copyright Copyright (c) 2020 - 2021 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-01-08 <td>1.0     <td>rock     <td>Create
 * </table>
 */
#include "dtu.h"
#include "yx.h"
#include "dbs.h"
#include "tables.h"

int yx_sdb_to_rdb(void)
{
	return 0;
}
/**
 * @brief Save a YX value by Point ID
 * @param  value YX value
 * @param  ptid	YX point ID
 * @return int 0 - success
 */
int yx_save_by_id(int value, int ptid)
{
	return 0;
}

/**
 * @brief Read YX value by value
 * @param  value Return value
 * @param  ptid	YX point id
 * @return int 0 - success
 */
int yx_read_single(char *value, int ptid)
{
	char buf[RDB_VAL_LEN] = { 0 };
	char key[STR_LEN] = { 0 };
	struct yx_desc_t desc;

	if (yx_read_desc_single(&desc, ptid) != 0) {
		dbg("Not Exists\n");
		return -1;
	}

	sprintf(key, "yx:%s:%d", desc.alias, desc.ptid);
	if (rdb_get_str(key, buf) != TRUE) {
		return -1;
	}
	*(float *)value = atof(buf);

	return 0;
}

/**
 * @brief Read YX desc structure single
 * @param  desc	Return value
 * @param  ptid	Point ID
 * @return int 0 - success
 */
int yx_read_desc_single(struct yx_desc_t *desc, int ptid)
{
	char cmd[STR_LEN] = { 0 };

	sprintf(cmd, "select * from tbl_yx where ptid=%d", ptid);
	if (sdb_select_single(cmd, &sdb_map_yx_desc, desc) != 0) {
		dbg("read desc failed\n");
		return -1;
	}

	return 0;
}