/**
 * @file notify.c
 * @brief
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2021-01-27
 * @copyright Copyright (c) 2020 - 2021 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-01-27 <td>1.0     <td>rock     <td>Create
 * </table>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <hiredis/hiredis.h>
#include "rdb.h"
#include "notify.h"

static int notify_status = 0;
static struct list_head notify_list_head;
#ifdef NOTIFY_CLIENT
static struct sigaction notify_action;
static void notify_handler(int sig, siginfo_t *info, void *ctx)
{
	notify_exec_list();
	printf("recv a sid=%d data=%d data=%d\n", sig, info->si_value.sival_int, info->si_int);
}
#endif
int notify_init(void)
{
	INIT_LIST_HEAD(&notify_list_head);

#ifdef NOTIFY_CLIENT
	notify_action.handler = notify_handler;
	sigemptyset(&notify_action.sa_mask);
	notify_action.sa_flags = SA_SIGINFO;
#endif
	notify_status = 1;
	return 0;
}

int notify_deinit(void)
{
	struct list_head *pos;
	struct list_head *n;
	struct notify_list_t *item;

	// Clear the list
	list_for_each_safe(pos, n, &notify_list_head) {
		item = list_entry(pos, struct notify_list_t, list);
		list_del(pos);
		free(item);
	}
	notify_status = 0;
	return 0;
}

static redisContext *rdb_connect(void)
{
	redisContext *ctx;
	struct timeval timeout = { 1, 500000 };

	ctx = redisConnectWithTimeout(RDB_HOST, RDB_PORT, timeout);
	if (ctx == NULL || ctx->err) {
		if (ctx) {
			printf("Connection error: %s\n", ctx->errstr);
			redisFree(ctx);
		} else {
			printf("Connection error: can't allocate redis context\n");
		}

		return NULL;
	}
	return ctx;
}
static int rdb_disconnect(redisContext *ctx)
{
	//redisClose(ctx);
	return 0;
}
int notify_set_rdb(pid_t pid, int key)
{
	redisReply *reply;
	redisContext *ctx = rdb_connect();

	if (ctx == NULL) {
		printf("failed\n");
		return -1;
	}

	reply = (redisReply *)redisCommand(ctx, "exists notify:%08d:%08d", key, (int)pid);
	if (reply->type == REDIS_REPLY_INTEGER) {
		if (reply->integer == 1) {
			printf("Already exists\n");
			freeReplyObject(reply);
			rdb_disconnect(ctx);
			return -1;
		}
	}

	reply = redisCommand(ctx,"SET notify:%08d:%08d", key, (int)pid);
	if (reply) {
		freeReplyObject(reply);
		rdb_disconnect(ctx);
		return 0;
	}

	rdb_disconnect(ctx);
	return -1;
}

int notify_send(int key)
{
	char key_buf[RDB_KEY_LEN] = { 0 };
	redisReply *reply;
	int pid;
	union sigval v;
	redisContext *ctx = rdb_connect();

	if (ctx == NULL) {
		printf("failed\n");
		return -1;
	}

	sprintf(key_buf, "notify:%08d:*", key);
	reply = (redisReply *)redisCommand(ctx, "keys notify:%08d:*", key);
	if (reply != NULL && reply->type == REDIS_REPLY_ARRAY) {
		for (int i = 0; i < reply->elements; i++) {
			memcpy(key_buf, &reply->element[i]->str[7], 8);
			key = atoi(key_buf);
			pid = atoi(&reply->element[i]->str[16]);
			printf("pid: %08d, key = %d\n", pid, key);
			v.sival_int = key;
			sigqueue(pid, SIGINT, v);
			freeReplyObject(reply->element[i]);
		}
		freeReplyObject(reply);
	}
	return 0;
}

int notify_register(int group, int index, void *callback, void *param)
{
	pid_t pid = getpid();
	int key = MKNID(group, index);
	struct notify_list_t *item = NULL;

	if (notify_status == 0) {
		notify_init();
	}

	list_for_each_entry(item, &notify_list_head, list) {
		if (item->key == key) {	// Update callback
			item->callback = callback;
			return 0;
		}
	}

	if (notify_set_rdb(pid, key) != 0) {
		printf("Register failed\n");
	}

	item = (struct notify_list_t *)malloc(sizeof(struct notify_list_t));
	if (item == NULL) {
		return -1;
	}
	item->key = key;
	item->callback = callback;

	// Insert to list
	list_add_tail(&item->list, &notify_list_head);

	return 0;
}

int notify_exec_key(int group, int index)
{
	int key = MKNID(group, index);
	struct notify_list_t *item;

	list_for_each_entry(item, &notify_list_head, list) {
		if (item->key != key) {
			continue;
		}
		if (item->callback != 0) {
			if ((*item->callback)(item->param) != 0) {
			}
		}
	}
	return 0;
}

int notify_exec_list(void)
{
	struct notify_list_t *item;

	list_for_each_entry(item, &notify_list_head, list) {
		if (item->callback != 0) {
			if ((*item->callback)(item->param) != 0) {
			}
		}
	}
	return 0;
}

int notify_unregister(int group, int index)
{
	int key = MKNID(group, index);
	struct list_head *pos;
	struct list_head *n;
	struct notify_list_t *item;

	if (notify_status == 0) {
		notify_init();
	}

	list_for_each_safe(pos, n, &notify_list_head) {
		item = list_entry(pos, struct notify_list_t, list);
		if (item->key == key) {
			list_del(pos);
			free(item);
			return 0;
		}
	}

	return 0;
}
