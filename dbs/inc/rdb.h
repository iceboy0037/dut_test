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

#define RDB_HOST			"127.0.0.1"
#define RDB_PORT			6379
#define RDB_REPLY_BUF_LEN		32

#define CHECK_FREE_REDIS_REPLY(reply) \
	if (reply) {\
		freeReplyObject(reply);\
	} else {\
		dbg("freeReplyObject Fail\n");\
	}

extern int rdb_connect(void);
extern int rdb_init(void);
extern int rdb_hset(const char *key, const char *hkey, const char *value);
extern int rdb_hget(const char *key, const char *filed, char *value);
extern int rdb_get_str(char *key, char *value);
extern int rdb_set_str(char *key, char *value);
extern int rdb_del(const char *key);
extern int rdb_exists(const char *key);

#ifdef __cplusplus
}
#endif
#endif