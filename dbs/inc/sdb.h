/**
 * @file sdb.h
 * @brief Sqlite interface header
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
#ifndef __SDB_H__
#define __SDB_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "dtu_types.h"

#define SDB_DEFAULT_PATH 	"../config/dtu_list.db"

struct sdb_map_item_t {
	char *name;
	int type;
	int offset;
};
struct sdb_map_t {
	struct sdb_map_item_t *array;
	int count;
};

#define SDB_MAP_START(name) static struct sdb_map_item_t name##_sdb_map_array[] = {
#define	SDB_MAP_ITEM(name, type, base, member)	{name, type, offsetof(base, member)},
#define	SDB_MAP_END(name) }; struct sdb_map_t sdb_map_##name = {name##_sdb_map_array, \
				sizeof(name##_sdb_map_array) / sizeof(struct sdb_map_item_t)};
#define	SDB_MAP_ADDR(name) &sdb_map_##name



/**
 * @brief Execuate Select command, and fill associated structure
 * @param  cmd	SQL Command
 * @param  map	SDB structure map
 * @param  base	Associate structure base address
 * @return int 0 - success
 */
int sdb_select_single(char *cmd, struct sdb_map_t *map, void *base);

#ifdef __cplusplus
}
#endif

#endif