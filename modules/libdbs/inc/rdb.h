/**
 * @file rdb.h
 * @brief
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2020-12-13
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-13 <td>1.0     <td>rock     <td>Modify Content
 * </table>
 */

#ifndef __RDB_H__
#define __RDB_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 映射结构
 */
struct pt_map_t {
	char	*name;
	int	type;
	int	size;		// base struct size
	int	offset;
};
struct pt_map_array_t {
	char 	*name;
	int	count;
	struct pt_map_t *map;
};
#define PT_MAP_START(name)				static struct pt_map_t name##_pt_map_entry[] = {
#define	PT_ITEM(name, type, base, value)		{(name), (type), sizeof(base), offsetof(base, value)},
#define	PT_MAP_END(name)				{NULL, PT_TYPE_INVALID, 0, 0}};\
							static struct pt_map_array_t name##_pt_array = {#name, \
								(sizeof(name##_pt_map_entry) / sizeof(struct pt_map_t) - 1), name##_pt_map_entry};\
							static struct pt_map_array_t *get_map_entry_##name(void) { return &name##_pt_array;}

#define RDB_HOST			"127.0.0.1"
#define RDB_PORT			6379
#define RDB_VAL_LEN			32
#define	RDB_KEY_LEN			32

#define CHECK_FREE_REDIS_REPLY(reply) \
	if (reply) {\
		freeReplyObject(reply);\
	} else {\
		dbg("freeReplyObject Fail\n");\
	}

extern int rdb_init(void);
extern int rdb_hset(const char *key, const char *hkey, const char *value);
extern int rdb_hget(const char *key, const char *filed, char *value);
extern int rdb_get_str(char *key, char *value);
extern int rdb_set_str(char *key, char *value);
extern int rdb_del(const char *key);
extern int rdb_exists(const char *key);
extern int rdb_ls_key(const char *keys);
extern int rdb_key_count(const char *keys);

/**
 * @brief query key from rdb, if query multi, only return the first
 * @param  key key query pattern
 * @return int >=0 - read count, <0 - failed
 */
extern int rdb_key(const char *keys, char *key_value);

#ifdef __cplusplus
}
#endif
#endif