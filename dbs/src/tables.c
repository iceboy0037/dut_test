/**
 * @file tables.c
 * @brief sqlite table struct definition
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
#include "dbs.h"
#include "tables.h"
#include "dtu.h"

SDB_MAP_START(tbl_sys)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_sys_t, id)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_sys_t, devid)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_sys_t, ptid)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_sys_t, fun)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_sys_t, inf)
	SDB_MAP_ITEM(PT_TYPE_STRING,	struct tbl_sys_t, name)
	SDB_MAP_ITEM(PT_TYPE_STRING,	struct tbl_sys_t, alias)
	SDB_MAP_ITEM(PT_TYPE_STRING,	struct tbl_sys_t, value)
	SDB_MAP_ITEM(PT_TYPE_STRING, 	struct tbl_sys_t, dtype)
	SDB_MAP_ITEM(PT_TYPE_STRING, 	struct tbl_sys_t, unit)
	SDB_MAP_ITEM(PT_TYPE_STRING, 	struct tbl_sys_t, tm)
SDB_MAP_END(tbl_sys)

SDB_MAP_START(tbl_bus_cfg)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_bus_cfg_t, index)
	SDB_MAP_ITEM(PT_TYPE_STRING,	struct tbl_bus_cfg_t, name)
	SDB_MAP_ITEM(PT_TYPE_STRING,	struct tbl_bus_cfg_t, alias)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_bus_cfg_t, enable)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_bus_cfg_t, mode)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_bus_cfg_t, line_count)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_bus_cfg_t, ua_index)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_bus_cfg_t, ub_index)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_bus_cfg_t, uc_index)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_bus_cfg_t, uz_index)
SDB_MAP_END(tbl_bus_cfg)

SDB_MAP_START(tbl_line_cfg)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_line_cfg_t, index)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_line_cfg_t, bus)
	SDB_MAP_ITEM(PT_TYPE_STRING,	struct tbl_line_cfg_t, name)
	SDB_MAP_ITEM(PT_TYPE_STRING,	struct tbl_line_cfg_t, alias)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_line_cfg_t, enable)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_line_cfg_t, ia_index)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_line_cfg_t, ib_index)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_line_cfg_t, ic_index)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_line_cfg_t, iz_index)
SDB_MAP_END(tbl_line_cfg)

SDB_MAP_START(tbl_ac_cfg)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_ac_cfg_t, index)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_ac_cfg_t, bid)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_ac_cfg_t, solt)
	SDB_MAP_ITEM(PT_TYPE_STRING,	struct tbl_ac_cfg_t, name)
	SDB_MAP_ITEM(PT_TYPE_STRING,	struct tbl_ac_cfg_t, alias)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_ac_cfg_t, enable)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_ac_cfg_t, mode)
	SDB_MAP_ITEM(PT_TYPE_FLOAT, 	struct tbl_ac_cfg_t, offset)
	SDB_MAP_ITEM(PT_TYPE_FLOAT, 	struct tbl_ac_cfg_t, coef)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_ac_cfg_t, gain_start)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_ac_cfg_t, gain_count)
SDB_MAP_END(tbl_ac_cfg)

SDB_MAP_START(tbl_ac_gain)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_ac_gain_t, channel)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_ac_gain_t, index)
	SDB_MAP_ITEM(PT_TYPE_FLOAT, 	struct tbl_ac_gain_t, gain)
	SDB_MAP_ITEM(PT_TYPE_INT,	struct tbl_ac_gain_t, low)
	SDB_MAP_ITEM(PT_TYPE_INT,	struct tbl_ac_gain_t, high)
SDB_MAP_END(tbl_ac_gain)

SDB_MAP_START(tbl_yc)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_yc_t, id)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_yc_t, devid)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_yc_t, ptid)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_yc_t, fun)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_yc_t, inf)
	SDB_MAP_ITEM(PT_TYPE_FLOAT, 	struct tbl_yc_t, name)
	SDB_MAP_ITEM(PT_TYPE_STRING,	struct tbl_yc_t, alias)
	SDB_MAP_ITEM(PT_TYPE_STRING,	struct tbl_yc_t, dtype)
	SDB_MAP_ITEM(PT_TYPE_STRING, 	struct tbl_yc_t, unit)
SDB_MAP_END(tbl_yc)

SDB_MAP_START(tbl_yx)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_yx_t, id)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_yx_t, devid)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_yx_t, ptid)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_yx_t, fun)
	SDB_MAP_ITEM(PT_TYPE_INT, 	struct tbl_yx_t, inf)
	SDB_MAP_ITEM(PT_TYPE_STRING, 	struct tbl_yx_t, name)
	SDB_MAP_ITEM(PT_TYPE_STRING,	struct tbl_yx_t, alias)
	SDB_MAP_ITEM(PT_TYPE_INT,	struct tbl_yx_t, value)
	SDB_MAP_ITEM(PT_TYPE_STRING,	struct tbl_yx_t, tm)
	SDB_MAP_ITEM(PT_TYPE_INT,	struct tbl_yx_t, count)
	SDB_MAP_ITEM(PT_TYPE_STRING,	struct tbl_yx_t, cdesc)
	SDB_MAP_ITEM(PT_TYPE_STRING,	struct tbl_yx_t, category)
	SDB_MAP_ITEM(PT_TYPE_STRING,	struct tbl_yx_t, adesc)
	SDB_MAP_ITEM(PT_TYPE_STRING,	struct tbl_yx_t, attr)
SDB_MAP_END(tbl_yx)
