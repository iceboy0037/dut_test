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

struct tbl_ac_gain_t {
	int channel;
	int index;
	float gain;
	int low;
	int high;
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

/**
 * @brief 遥信点位描述结构，对应于数据库中的表结构
 */
struct tbl_yx_t {
	int id;					// id号
	int devid;				// 设备ID号
	int ptid;				// 点位ID
	int fun;				// 功能号
	int inf;				// 信息编号
	char name[NAME_LENGTH];			// 显示名，可中文
	char alias[NAME_LENGTH];		// 别名
	int value;				// 遥信值都是0或1
	char tm[TM_STR_LEN];			// 设置时间
	int count;				// 计数
	char cdesc[STR_LEN];			// 类别描述
	char category[STR_LEN];			// 类别
	char adesc[STR_LEN];			// 属性描述
	char attr[STR_LEN];			// 属性
};

DECLARE_TABLE(tbl_sys)
DECLARE_TABLE(tbl_bus_cfg)
DECLARE_TABLE(tbl_line_cfg)
DECLARE_TABLE(tbl_ac_cfg)
DECLARE_TABLE(tbl_ac_gain)
DECLARE_TABLE(tbl_yc)
DECLARE_TABLE(tbl_yx)

#ifdef __cplusplus
}
#endif
#endif