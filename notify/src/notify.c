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
#include <hiredis/hiredis.h>
#include "notify.h"

static int notify_status = 0;
static struct list_head notify_list_head;
int notify_init(void)
{
	INIT_LIST_HEAD(&notify_list_head);
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

int notify_register(int group, int index, void *callback, void *param)
{
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
	struct nodify_list_t *item;

	list_for_each_entry(item, &notify_list_head, list) {
		if (item->callback != 0) {
			if ((*item->callback)(item->param) != 0) {
			}
		}
	}
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

int notify_send(int group, int index)
{
	return 0;
}

static void notify_handler(int sig, siginfo_t *info, void *ctx)
{

}
