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

#include "sdb.h"
#include "rdb.h"

extern struct sdb_map_t sdb_map_yc_desc;
extern struct sdb_map_t sdb_map_yx_desc;
extern struct sdb_map_t sdb_map_param_item_desc;

#ifdef __cplusplus
}
#endif
#endif