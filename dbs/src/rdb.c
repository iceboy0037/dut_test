/**
 * @file rdb.c
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

#include <string.h>
#include <hiredis/hiredis.h>
#include "dbg.h"
#include "rdb.h"
#include "dtu.h"
#include "dbg.h"

static redisContext *m_ctx = NULL;
/**
 * @brief Connect to RDB
 * @return int
 */
int rdb_connect(void)
{
	struct timeval timeout = { 1, 500000 }; 	// 1.5 seconds

	m_ctx = redisConnectWithTimeout(RDB_HOST, RDB_PORT, timeout);
	if (m_ctx == NULL || m_ctx->err) {
		if (m_ctx) {
			dbg("Connection error: %s\n", m_ctx->errstr);
			redisFree(m_ctx);
		} else {
			dbg("Connection error: can't allocate redis m_ctx\n");
		}

		return FALSE;
	}

	return TRUE;
}

int rdb_init(void)
{
	return rdb_connect();
}

/**
 * @brief query key from rdb, if query multi, only return the first
 * @param  key key query pattern
 * @return int >=0 - read count, <0 - failed
 */
int rdb_key(const char *keys, char *key_value)
{
	redisReply *reply = (redisReply *)redisCommand(m_ctx, keys);
	if (reply != NULL && reply->type == REDIS_REPLY_ARRAY) {
		if (reply->elements > 0) {
			strncpy(key_value, reply->element[0]->str, reply->element[0]->len + 1);
			for (int i = 0; i < reply->elements; i++) {
				freeReplyObject(reply->element[i]);
			}
		} else {
			return 0;	// empty
		}
		freeReplyObject(reply);
		return 1;
	}
	return -1;
}
/**
 * @brief Hash value set
 * @param  key		hash key
 * @param  filed	object filed
 * @param  value	value in string format
 * @return int
 */
int rdb_hset(const char *key, const char *hkey, const char *value)
{
	redisReply *reply = (redisReply *)redisCommand(m_ctx, "HSET %s %s %s", key, hkey, value);
	freeReplyObject(reply);
	return TRUE;
}

/**
 * @brief Hash value get
 * @param  key		hash key
 * @param  filed	object filed
 * @param  value	return value in string format
 * @return int
 */
int rdb_hget(const char *key, const char *filed, char *value)
{
	const char *argv[3];
	size_t argvlen[3];
	int ret = FALSE;

	argv[0] 	= "HGET";
	argvlen[0] 	= 4;
	argv[1] 	= key;
	argvlen[1] 	= strlen(key);
	argv[2] 	= filed;
	argvlen[2] 	= strlen(filed);
	redisReply *reply = (redisReply *)redisCommandArgv(m_ctx, 3, argv, argvlen);

	if (reply->type != REDIS_REPLY_NIL) {
		strcpy(value, (char *)(reply->str + reply->len));	// Copy result
		ret = TRUE;
	} else {
		ret = FALSE;
	}

	freeReplyObject(reply);
	return ret;
}

/**
 * @brief Get Normal key value
 * @param  key
 * @param  value
 * @return int
 */
int rdb_get_str(char *key, char *value)
{
	redisReply *reply = redisCommand(m_ctx, "GET %s", key);

	if (reply && reply->type == REDIS_REPLY_STRING) {
		strcpy(value, reply->str);
		freeReplyObject(reply);
		return TRUE;
	}

	dbg("get redis fail: %s\n", key);
	return FALSE;
}

int rdb_set_str(char *key, char *value)
{
	redisReply *reply = redisCommand(m_ctx, "SET %s %s", key, value);

	if (reply) {
		freeReplyObject(reply);
		return TRUE;
	}

	dbg("Set redis fail: %s\n", key);
	return FALSE;
}

int rdb_del(const char *key)
{
	int res = FALSE;
	redisReply *reply = (redisReply *)redisCommand(m_ctx, "DEL %s", key);

	if (reply->type == REDIS_REPLY_INTEGER) {
		if (reply->integer == 1) {
			res = TRUE;
		}
	}

	freeReplyObject(reply);
	return res;
}
int rdb_exists(const char *key)
{
	redisReply *reply = (redisReply *)redisCommand(m_ctx, "exists %s", key);
	int res = FALSE;

	if (reply->type == REDIS_REPLY_INTEGER) {
		if (reply->integer == 1L) {
			res  = TRUE;
		}
	}

	freeReplyObject(reply);
	return res;
}
