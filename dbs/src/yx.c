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
 * @param  ts YX time stamp, if not need, set it to NULL
 * @return int 0 - success
 */
int yx_save_by_id(int value, int ptid, struct time_stamp *ts)
{
	char cmd[SQL_CMD_LEN] = { 0 };
	char buf[TIME_STRING_LEN + 1] = { 0 };
	sqlite3 *db;
	char *errmsg;
	int ret;

	if (ts != NULL) {
		stamp_to_string(ts, buf);
		snprintf(cmd, SQL_CMD_LEN, "update tbl_yx set value=%d, tm='%s' where ptid=%d;", value, buf, ptid);
	} else {
		snprintf(cmd, SQL_CMD_LEN, "update tbl_yx set value=%d where ptid=%d;", value, ptid);
	}

	db = sdb_open(SDB_DEFAULT_PATH);
	if (db == NULL) {
		return -1;
	}
	ret = sqlite3_exec(db, cmd, NULL, NULL, &errmsg);
	if (ret != SQLITE_OK) {
		dbg("Exec failed : %s\n", cmd);
		sqlite3_free(errmsg);
		sdb_close(db);
		return -1;
	}
	sqlite3_free(errmsg);
	sdb_close(db);

	return 0;
}

/**
 * @brief Read YX value by value
 * @param  value Return value
 * @param  ptid	YX point id
 * @param  ts	YX time stamp, if not need, set it to NULL
 * @return int 0 - success
 */
int yx_read_single(char *value, int ptid, struct time_stamp *ts)
{
	struct tbl_yx_t desc;

	if (yx_read_desc_single(&desc, ptid) != 0) {
		dbg("YX: %d Not Exists\n", ptid);
		return -1;
	}
	if (ts != NULL) {
		if (string_to_stamp(ts, desc.tm) != 0) {
			dbg("Convert YX time stamp failed, string = %s\n", desc.tm);
			return -1;
		}
	}
	*value = (char)desc.value;
	return 0;
}

/**
 * @brief Read YX desc structure single
 * @param  desc	Return value
 * @param  ptid	Point ID
 * @return int 0 - success
 */
int yx_read_desc_single(struct tbl_yx_t *desc, int ptid)
{
	char cmd[SQL_CMD_LEN] = { 0 };

	snprintf(cmd, SQL_CMD_LEN, "select * from tbl_yx where ptid=%d", ptid);
	if (sdb_select_single(cmd, &sdb_map_tbl_yx, desc) != 0) {
		dbg("read desc failed\n");
		return -1;
	}

	return 0;
}