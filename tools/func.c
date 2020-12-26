/**
 * @file func.c
 * @brief 杰me
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2020-12-22
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-22 <td>1.0     <td>rock     <td>
 * </table>
 */
#include <stdio.h>
#include <stddef.h>
#include <hiredis/hiredis.h>

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
#define PT_MAP_START(name)				struct pt_map_t name##_pt_map_entry[] = {
#define	PT_ITEM(name, type, base, value)		{(name), (type), sizeof(base), offsetof(base, value)},
#define	PT_MAP_END(name)				{NULL, PT_TYPE_INVALID, 0, 0}};\
							struct pt_map_array_t name##_pt_array = {#name, \
								(sizeof(name##_pt_map_entry) / sizeof(struct pt_map_t) - 1), name##_pt_map_entry};\
							static struct pt_map_array_t *get_map_entry_##name(void) { return &name##_pt_array;}

/**
 * @brief 实时遥测存储结构
 */
struct yc_value_t {
	float	rating;		// 额定值
	float	raw;		// 原始值
	float	output;		// 原始值1次值
	int	q;		// 品质
};
struct yc_bus_t {
	struct yc_value_t ua;
	struct yc_value_t ub;
	struct yc_value_t uc;
	struct yc_value_t uab;
	struct yc_value_t ubc;
	struct yc_value_t u0;
	struct yc_value_t f;
};
#define PT_TYPE_INVALID -1
#define PT_TYPE_FLOAT 0
PT_MAP_START(yc)
	PT_ITEM("ua1",		PT_TYPE_FLOAT,	struct yc_bus_t, ua.rating)
	PT_ITEM("ub1",		PT_TYPE_FLOAT,	struct yc_bus_t, ua.raw)
	PT_ITEM("uc1",		PT_TYPE_FLOAT,	struct yc_bus_t, ua.output)
	PT_ITEM("uab1",		PT_TYPE_FLOAT,	struct yc_bus_t, ua.q)
PT_MAP_END(yc)


static redisContext *m_ctx = NULL;
/**
 * @brief Connect to RDB
 * @return int
 */
int rdb_connect(void)
{
#define RDB_HOST			"127.0.0.1"
#define RDB_PORT			6379
	struct timeval timeout = { 1, 500000 }; 	// 1.5 seconds

	m_ctx = redisConnectWithTimeout(RDB_HOST, RDB_PORT, timeout);
	if (m_ctx == NULL || m_ctx->err) {
		if (m_ctx) {
			printf("Connection error: %s\n", m_ctx->errstr);
			redisFree(m_ctx);
		} else {
			printf("Connection error: can't allocate redis m_ctx\n");
		}

		return -1;
	}

	return 0;
}
/*
#define REDIS_REPLY_STRING 1
#define REDIS_REPLY_ARRAY 2
#define REDIS_REPLY_INTEGER 3
#define REDIS_REPLY_NIL 4
#define REDIS_REPLY_STATUS 5
#define REDIS_REPLY_ERROR 6
#define REDIS_REPLY_DOUBLE 7
#define REDIS_REPLY_BOOL 8
#define REDIS_REPLY_MAP 9
#define REDIS_REPLY_SET 10
#define REDIS_REPLY_ATTR 11
#define REDIS_REPLY_PUSH 12
#define REDIS_REPLY_BIGNUM 13
#define REDIS_REPLY_VERB 14
*/
int main(int argc, char *argv[])
{
	rdb_connect();
	redisReply *reply = (redisReply *)redisCommand(m_ctx, "keys di299*");
	printf("Type = %d\n", reply->type);
	if (reply && reply->type == REDIS_REPLY_ARRAY) {
		printf("len = %d, str = %s, elements = %d\n", reply->len, (char *)(reply->str + reply->len), reply->elements);
		if (reply->elements > 0) {
			for (int i = 0; i < reply->elements; i++) {
				redisReply *tmp = reply->element[i];
				printf("ReplyType = %d\n", tmp->type);
				printf("%d: len = %d, str = %s, elements = %d\n", i, tmp->len, tmp->str, tmp->elements);
			}
		}
	}
	return 0;
}
