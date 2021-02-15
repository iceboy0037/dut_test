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
static int rdb_connect(void)
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

		return FAIL;
	}

	return SUCCESS;
}

/**
 * @brief Init RDB database
 * @return int
 */
int rdb_init(void)
{
	return rdb_connect();
}

/**
 * @brief Return RDB status
 * @return int
 */
int rdb_ready(void)
{
	if (m_ctx != NULL) {
		return READY;
	}
	return NOREADY;
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

int rdb_ls_key(const char *keys)
{
	char buf[RDB_VAL_LEN] = { 0 };
	redisReply *reply = (redisReply *)redisCommand(m_ctx, keys);

	if (reply != NULL && reply->type == REDIS_REPLY_ARRAY) {
		if (reply->elements > 0) {
			for (int i = 0; i < reply->elements; i++) {
				rdb_get_str(reply->element[i]->str, buf);
				println("%8d: %16s%16s\n", i, reply->element[i]->str, buf);
				freeReplyObject(reply->element[i]);
			}
		}
		freeReplyObject(reply);
		return SUCCESS;
	}
	return FAIL;
}

/**
 * @brief Get special keys count
 * @param  keys	key query pattern.
 * @return int 0 - success
 */
int rdb_key_count(const char *keys)
{
	int count = 0;
	redisReply *reply = (redisReply *)redisCommand(m_ctx, keys);

	if (reply != NULL && reply->type == REDIS_REPLY_ARRAY) {
		count = reply->elements;
		if (reply->elements > 0) {
			for (int i = 0; i < reply->elements; i++) {
				freeReplyObject(reply->element[i]);
			}
		}
		freeReplyObject(reply);
	}
	return count;
}

/**
 * @brief Hash value set
 * @param  key		hash key
 * @param  filed	object filed
 * @param  value	value in string format
 * @return int 0 - success
 */
int rdb_hset(const char *key, const char *hkey, const char *value)
{
	redisReply *reply = (redisReply *)redisCommand(m_ctx, "HSET %s %s %s", key, hkey, value);
	freeReplyObject(reply);
	return SUCCESS;
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
	int ret = FAIL;

	argv[0] 	= "HGET";
	argvlen[0] 	= 4;
	argv[1] 	= key;
	argvlen[1] 	= strlen(key);
	argv[2] 	= filed;
	argvlen[2] 	= strlen(filed);
	redisReply *reply = (redisReply *)redisCommandArgv(m_ctx, 3, argv, argvlen);

	if (reply->type != REDIS_REPLY_NIL) {
		strcpy(value, (char *)(reply->str + reply->len));	// Copy result
		ret = 0;
	} else {
		ret = FAIL;
	}

	freeReplyObject(reply);
	return ret;
}

/**
 * @brief Get Normal key value
 * @param  key RDB key string
 * @param  value RDB return value string
 * @return int 0 - success
 */
int rdb_get_str(char *key, char *value)
{
	redisReply *reply = redisCommand(m_ctx, "GET %s", key);

	if (reply && reply->type == REDIS_REPLY_STRING) {
		strcpy(value, reply->str);
		freeReplyObject(reply);
		return SUCCESS;
	}

	dbg("get redis fail: %s\n", key);
	return FAIL;
}

int rdb_set_str(char *key, char *value)
{
	redisReply *reply = redisCommand(m_ctx, "SET %s %s", key, value);

	if (reply) {
		freeReplyObject(reply);
		return SUCCESS;
	}

	dbg("Set redis fail: %s\n", key);
	return FAIL;
}

int rdb_del(const char *key)
{
	int res = FAIL;
	redisReply *reply = (redisReply *)redisCommand(m_ctx, "DEL %s", key);

	if (reply->type == REDIS_REPLY_INTEGER) {
		if (reply->integer == 1) {
			res = 0;
		}
	}

	freeReplyObject(reply);
	return res;
}
int rdb_exists(const char *key)
{
	redisReply *reply = (redisReply *)redisCommand(m_ctx, "exists %s", key);
	int res = FAIL;

	if (reply->type == REDIS_REPLY_INTEGER) {
		if (reply->integer == 1L) {
			res  = SUCCESS;
		}
	}

	freeReplyObject(reply);
	return res;
}
