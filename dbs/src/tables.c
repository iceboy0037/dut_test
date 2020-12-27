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

SDB_MAP_START(yc_desc)
	SDB_MAP_ITEM("devid", 	PT_TYPE_INT, 	struct yc_desc_t, devid)
	SDB_MAP_ITEM("ptid", 	PT_TYPE_INT, 	struct yc_desc_t, ptid)
	SDB_MAP_ITEM("fun", 	PT_TYPE_INT, 	struct yc_desc_t, fun)
	SDB_MAP_ITEM("inf", 	PT_TYPE_INT, 	struct yc_desc_t, inf)
	SDB_MAP_ITEM("ratio", 	PT_TYPE_FLOAT, 	struct yc_desc_t, ratio)
	SDB_MAP_ITEM("type", 	PT_TYPE_STRING,	struct yc_desc_t, type)
	SDB_MAP_ITEM("name", 	PT_TYPE_STRING, struct yc_desc_t, name)
	SDB_MAP_ITEM("alias", 	PT_TYPE_STRING, struct yc_desc_t, alias)
SDB_MAP_END(yc_desc)