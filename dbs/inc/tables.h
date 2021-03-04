/**
 * @file tables.h
 * @brief Sqlite3 tables definition
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2020-12-27
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-27 <td>1.0     <td>rock     <td>Create
 * </table>
 */
#ifndef __TABLES_H__
#define	__TABLES_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "dtu_limits.h"
#include "sdb.h"
#include "rdb.h"

struct tbl_sys_t {
	int id;					// id号
	int devid;				// 设备id
	int ptid;				// 点位ID
	int fun;				// 功能号
	int inf;				// 组内编号
	char name[NAME_LENGTH];
	char alias[NAME_LENGTH];
	char value[VALUE_LENGTH];
	char dtype[TYPE_STR_LENGTH];
	char unit[UNIT_LENGTH];
	char tm[TM_STR_LEN];
};

struct tbl_bus_cfg_t {
	int index;
	char name[NAME_LENGTH];
	char alias[NAME_LENGTH];
	int enable;
	int mode;
	int line_count;
	int ua_index;
	int ub_index;
	int uc_index;
	int uz_index;
};

struct tbl_line_cfg_t {
	int index;
	int bus;
	char name[NAME_LENGTH];
	char alias[NAME_LENGTH];
	int enable;
	int ia_index;
	int ib_index;
	int ic_index;
	int iz_index;
};

struct tbl_ac_cfg_t {
	int index;
	int bid;
	int solt;
	char name[NAME_LENGTH];
	char alias[NAME_LENGTH];
	int enable;
	int mode;
	float offset;
	float coef;
	int gain_start;
	int gain_count;
};

struct tbl_yc_t {
	int id;					// id号
	int devid;
	int ptid;				// 点位ID
	int fun;
	int inf;
	char name[NAME_LENGTH];
	char alias[NAME_LENGTH];
	char dtype[TYPE_STR_LENGTH];
	char unit[UNIT_LENGTH];
};

extern struct sdb_map_t sdb_map_yc_desc;
extern struct sdb_map_t sdb_map_yx_desc;
extern struct sdb_map_t sdb_map_param_item_desc;

#ifdef __cplusplus
}
#endif
#endif