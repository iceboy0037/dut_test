/**
 * @file sdb.c
 * @brief sqlite interface implementation
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#include "dbs.h"
#include "sdb.h"
#include "dbg.h"
#include "dtu_limits.h"

static sqlite3 *sdb = NULL;

/**
 * @brief Init sdb system
 * @return int 0 - success
 */
int sdb_init(void)
{
	return 0;
}

/**
 * @brief Open a Sqlite3 Database
 * @param  path DB path
 * @return sqlite3* NULL if failed
 */
sqlite3 *sdb_open(char *path)
{
	int  rc;

	rc = sqlite3_open(path, &sdb);
	if (rc) {
		dbg("Can't open database: %s\n", sqlite3_errmsg(sdb));
		return NULL;
	}
	return sdb;
}

/**
 * @brief close a sqlite3 database
 * @param  db	DB pointer
 */
void sdb_close(sqlite3 *db)
{
	sqlite3_close(db);
	db = NULL;
}

/**
 * @brief Execuate Select command, malloc list memory and fill associated structure list
 * @param  cmd	SQL Command
 * @param  map	SDB structure map
 * @param  base	Associate structure base address pointer, will use sdb_malloc to allocate table memory
 * @param  size Base structure size in bytes
 * @return int <0 on failure, >0 return table count
 */
int sdb_select_multi(char *cmd, struct sdb_map_t *map, void **base, int size)
{
	char **result;
	char *errmsg;
	int rows;
	int cols;
	int index;
	ssize_t addr;
	ssize_t item_base;

	sqlite3 *db = sdb_open(SDB_DEFAULT_PATH);
	if (db == NULL) {
		dbg("Open DB file %s failed\n", SDB_DEFAULT_PATH);
		return -1;
	}

	if (sqlite3_get_table(db, cmd, &result, &rows, &cols, &errmsg) != SQLITE_OK) {
		sqlite3_free(errmsg);
		sdb_close(db);
		return -1;
	}

	if (cols != map->count || rows == 0) {
		dbg("Table struct dismatched, count = %d, cols = %d, rows = %d\n", map->count, cols, rows);
		sqlite3_free_table(result);
		sdb_close(db);
		return -1;
	}

	*base = (void *)sdb_malloc(rows * size);
	if (*base == NULL) {
		dbg("Malloc table structure list failed\n");
		sqlite3_free_table(result);
		sdb_close(db);
		return -1;
	}

	index = cols;
	for (int i = 0; i < rows; i++) {
		item_base = (ssize_t)(*base) + size * i;
		for (int j = 0; j < cols; j++) {
			addr = item_base + map->array[j].offset;
			switch (map->array[j].type) {
			case PT_TYPE_CHAR:
				*(char *)addr = (char)atoi(result[index]);
				break;
			case PT_TYPE_INT:
				*(int *)addr = atoi(result[index]);
				break;
			case PT_TYPE_FLOAT:
				*(float *)addr = atof(result[index]);
				break;
			case PT_TYPE_STRING:
				strcpy((char *)addr, result[index]);
				break;
			default:
				dbg("NOT Support\n");
				break;
			}
			index++;
		}
	}
	sqlite3_free_table(result);
	sdb_close(db);

	return rows;
}

/**
 * @brief Execuate Select command, and fill associated structure
 * @param  cmd	SQL Command
 * @param  map	SDB structure map
 * @param  base	Associate structure base address
 * @return int 0 - success
 */
int sdb_select_single(char *cmd, struct sdb_map_t *map, void *base)
{
	char **result;
	char *errmsg;
	int rows;
	int cols;
	int i;
	int index;
	ssize_t addr;

	sqlite3 *db = sdb_open(SDB_DEFAULT_PATH);
	if (db == NULL) {
		return -1;
	}

	if (sqlite3_get_table(db, cmd, &result, &rows, &cols, &errmsg) != 0) {
		dbg("error : %s\n", errmsg);
		sqlite3_free(errmsg);
		sdb_close(db);
		return -1;
	}

	if (cols != map->count || rows > 1 || rows == 0) {
		dbg("Table struct dismatched, count = %d, cols = %d, rows = %d\n", map->count, cols, rows);
		sqlite3_free_table(result);
		sdb_close(db);
		return -1;
	}

	index = cols;
	for (i = 0; i < cols; i++) {
		addr = (ssize_t)base + map->array[i].offset;
		switch (map->array[i].type) {
		case PT_TYPE_INT:
			*(int *)addr = atoi(result[index]);
			break;
		case PT_TYPE_FLOAT:
			*(float *)addr = atof(result[index]);
			break;
		case PT_TYPE_STRING:
			strcpy((char *)addr, result[index]);
			break;
		default:
			break;
		}
		println("%-8s : %-8s\n", result[i], result[index]);
		index++;
	}
	sqlite3_free_table(result);
	sdb_close(db);

	return 0;
}