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
#include <errno.h>
#include <hiredis/hiredis.h>
#include "notify.h"
#include "dbg.h"
#include "rdb.h"

static int notify_status = 0;
static int notify_mode = NOTIFY_CLIENT;
static struct list_head notify_list_head;
static struct sigaction notify_action;
static int notify_exec_list(void);
static int is_pid_avail(int pid);

static void notify_handler(int sig, siginfo_t *info, void *arg)
{
	dbg("recv a sid=%d data=%d data=%d, arg = %p\n",
		sig, info->si_value.sival_int, info->si_int, arg);
	fflush(stdout);
	notify_exec_list();
}
int notify_init(int mode)
{
	INIT_LIST_HEAD(&notify_list_head);

	notify_mode = mode;
	if (mode == NOTIFY_CLIENT) {
		notify_action.sa_sigaction = notify_handler;
		sigemptyset(&notify_action.sa_mask);
		notify_action.sa_flags = SA_SIGINFO;
	}

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
			dbg("Connection error: %s\n", ctx->errstr);
			redisFree(ctx);
		} else {
			dbg("Connection error: can't allocate redis context\n");
		}

		return NULL;
	}

	return ctx;
}

static int rdb_disconnect(redisContext *ctx)
{
	redisFree(ctx);
	return 0;
}

int notify_set_rdb(pid_t pid, int key, int arg)
{
	redisReply *reply;
	redisContext *ctx = rdb_connect();

	if (ctx == NULL) {
		dbg("Connect RDB failed\n");
		return -1;
	}

	reply = (redisReply *)redisCommand(ctx, "exists notify:%08d:%08d", key, (int)pid);
	if (reply->type == REDIS_REPLY_INTEGER) {
		if (reply->integer == 1) {
			dbg("Already exists\n");
			freeReplyObject(reply);
			rdb_disconnect(ctx);
			return -1;
		}
	}

	dbg("SET notify:%08d:%08d %d", key, (int)pid, arg);
	reply = redisCommand(ctx,"SET notify:%08d:%08d %08d", key, (int)pid, arg);
	if (reply) {
		println(" Successed\n");
		freeReplyObject(reply);
		rdb_disconnect(ctx);
		return 0;
	}
	println("Failed\n");
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
		dbg("failed\n");
		return -1;
	}

	reply = (redisReply *)redisCommand(ctx, "keys notify:%08d:*", key);
	if (reply != NULL && reply->type == REDIS_REPLY_ARRAY) {
		dbg("Event for %d counts = %d\n", key, (int)reply->elements);
		for (int i = 0; i < reply->elements; i++) {
			memcpy(key_buf, &reply->element[i]->str[7], 8);
			key = atoi(key_buf);
			pid = atoi(&reply->element[i]->str[16]);
			dbg("Send signal to pid: %08d, key = %d\n", pid, key);
			if (is_pid_avail(pid)) {
				v.sival_int = key;
				sigqueue(pid, SIGINT, v);
			} else {
				redisCommand(ctx, "del %s", reply->element[i]->str);
			}
		}
		freeReplyObject(reply);
	}
	return 0;
}

int notify_register(int group, int index, void *callback, int arg)
{
	pid_t pid = getpid();
	int key = MKNID(group, index);
	struct notify_list_t *item = NULL;

	if (notify_status == 0) {
		println("Nofity module NOT initialized!\n");
		return -1;
	}

	list_for_each_entry(item, &notify_list_head, list) {
		if (item->key == key) {	// Update callback
			item->callback = callback;
			return 0;
		}
	}

	if (notify_set_rdb(pid, key, arg) != 0) {
		dbg("Register failed\n");
		return -1;
	}

	item = (struct notify_list_t *)malloc(sizeof(struct notify_list_t));
	if (item == NULL) {
		return -1;
	}
	item->key = key;
	item->callback = callback;
	item->arg = arg;

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
			if ((*item->callback)(item->arg) != 0) {
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
			if ((*item->callback)(item->arg) != 0) {
			}
		}
	}
	return 0;
}

static int is_pid_avail(int pid)
{
	 if (kill(pid, 0) && errno == ESRCH) {
		 return 0;
	 }
	 return 1;
}

int notify_print_list(void)
{
	int i = 0;
	int key;
	int pid;
	struct notify_list_t *item;
	char key_buf[RDB_KEY_LEN] = { 0 };
	redisReply *reply;
	redisContext *ctx = rdb_connect();

	if (notify_mode == NOTIFY_SERVER) {
		reply = (redisReply *)redisCommand(ctx, "keys notify*");
		if (reply == NULL || reply->type != REDIS_REPLY_ARRAY || reply->elements == 0) {
			println("Empty\n");
			return 0;
		}

		for (i = 0; i < reply->elements; i++) {
			println("%3d: %s, ", i, reply->element[i]->str);
			memcpy(key_buf, &reply->element[i]->str[7], 8);
			key = atoi(key_buf);
			pid = atoi(&reply->element[i]->str[16]);
			println("key = %-8d, pid = %-8d, ", key, pid);
			if (is_pid_avail(pid)) {
				println("available\n");
			} else {
				redisCommand(ctx, "del %s", reply->element[i]->str);
				println("invalid\n");
			}
		}
		freeReplyObject(reply);

		return 0;
	}

	list_for_each_entry(item, &notify_list_head, list) {
		println("%03d: key = %08x, arg = %08x\n", i, item->key, item->arg);
		i++;
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
		println("Nofity module NOT initialized!\n");
		return -1;
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
