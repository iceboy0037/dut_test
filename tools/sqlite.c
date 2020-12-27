#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>


//#define __compiler_offsetof(a,b) __builtin_offsetof(a,b)
#ifdef __compiler_offsetof
#ifndef offsetof
#define offsetof(TYPE, MEMBER) 	__compiler_offsetof(TYPE,MEMBER)
#endif
#else
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif


#ifndef container_of
#define container_of(ptr, type, member) ({	    \
		const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
		(type *)( (char *)__mptr - offsetof(type,member) );})
#endif

#ifndef STRINGIFY
#define STRINGIFY(a) 		#a
#endif

#define TYPE_STR_LENGTH		16		// 数据类型字符串长度
#define POINT_DESC_LENGTH	32	        // 点位描述字符串长度


static int callback(void *param, int argc, char **argv, char **col)
{
	static int cnt = 0;
	int i;
	printf("param = %s\n", (const char *)param);
	printf("Cnt = %d\n", cnt++);

	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", col[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
	return 0;
}
struct yc_desc_t {
	int	ptid;				// 点位ID号
	int	devid;				// 设备ID号
	int	fun;				// 功能号
	int	inf;				// 信息编号
	float	ratio;				// 系数
	char	type[TYPE_STR_LENGTH];		// 数据类型
	char	name[POINT_DESC_LENGTH];	// 描述字符串
	char	alias[POINT_DESC_LENGTH];	// 变量名字符串
};

struct sql_map_item_t {
	char *name;	// col name
	int type;	// data type
	int col;	// col index
	int offset;	// data offset
};
struct sql_map_t {
	struct sql_map_item_t *array;
	int count;
};
#define	PT_TYPE_FLOAT		(0L)
#define	PT_TYPE_INT		(1L)
#define	PT_TYPE_UINT		(2L)
#define PT_TYPE_SHORT		(3L)
#define PT_TYPE_USHORT		(4L)
#define PT_TYPE_CHAR		(5L)
#define	PT_TYPE_UCHAR		(6L)
#define PT_TYPE_DOUBLE		(7L)
#define PT_TYPE_STRING		(8L)
#define PT_TYPE_STRUCT		(9L)
#define PT_TYPE_INVALID		(-1L)
struct sql_map_item_t yc_desc_map_array[] = {
	{"devid", 	PT_TYPE_INT, 0(int)offsetof(struct yc_desc_t, devid)},
	{"ptid", 	PT_TYPE_INT, 1, (int)offsetof(struct yc_desc_t, ptid)},
	{"fun", 	PT_TYPE_INT, 2, (int)offsetof(struct yc_desc_t, fun)},
	{"inf", 	PT_TYPE_INT, 3, (int)offsetof(struct yc_desc_t, inf)},
	{"ratio", 	PT_TYPE_FLOAT, 4, (int)offsetof(struct yc_desc_t, ratio)},
	{"type", 	PT_TYPE_STRING, 5, (int)offsetof(struct yc_desc_t, type)},
	{"name", 	PT_TYPE_STRING, 6, (int)offsetof(struct yc_desc_t, name)},
	{"alias", 	PT_TYPE_STRING, 7, (int)offsetof(struct yc_desc_t, alias)}
};
struct sql_map_t yc_desc_map = {yc_desc_map_array, sizeof(yc_desc_map_array) / sizeof(struct sql_map_item_t)};
int sdb_select_single(sqlite3 *db, char *cmd, struct sql_map_t *map, void *base)
{
	char **result;
	char *errmsg;
	int rows;
	int cols;
	int i;
	int index;
	ssize_t addr;

	if (sqlite3_get_table(db, cmd, &result, &rows, &cols, &errmsg) != 0) {
		printf("error : %s\n", errmsg);
		sqlite3_free(errmsg);
		return -1;
	}

	if (cols != map->count || rows > 1 || rows == 0) {
		printf("Table struct dismatched, count = %d, cols = %d, rows = %d\n", map->count, cols, rows);
		sqlite3_free_table(result);
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
		printf("%-8s : %-8s\n", result[i], result[index]);
		index++;
	}
	sqlite3_free_table(result);

	return 0;
}

void do_show_sample(sqlite3 *db)
{
	char **result, *errmsg;
	int nrow, ncolumn, i, j, index;

	if (sqlite3_get_table(db, "select * from student", &result, &nrow, &ncolumn, &errmsg) != 0) {
		printf("error : %s\n", errmsg);
		sqlite3_free(errmsg);
	}

	index = ncolumn;
	for (i = 0; i < nrow; i++) {
		for (j = 0; j < ncolumn; j++) {
			printf("%-8s : %-8s\n", result[j], result[index]);
			index++;
		}

		printf("************************\n");
	}

	sqlite3_free_table(result);
	return;
}
struct yc_desc_t desc;
int main(int argc, char *argv[])
{
	sqlite3 *db;
	char *zErrMsg = "error message\n";
	int  rc;
	char *sql;
	char *param = "message";
	/* Open database */
	rc = sqlite3_open("test.db", &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	} else {
		fprintf(stdout, "Opened database successfully\n");
	}

	sql = "select * from tbl_yc_desc where alias like 'cos16%';";
	sdb_select_single(db, sql, &yc_desc_map, &desc);
	return 0;
	/* Create SQL statement */
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, param, &zErrMsg);

	if (rc != SQLITE_OK) {
		printf("SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		printf("Execuate successfully\n");
	}

	sqlite3_close(db);
	return 0;
}