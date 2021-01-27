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
#include "notify.h"

static int notify_status = 0;
int notify_init(void)
{
	notify_status = 1;
	return 0;
}

int notify_deinit(void)
{
	notify_status = 0;
	return 0;
}

int notify_register(int group, int index, notify_callback callback, void *param)
{
	if (notify_status == 0) {
		notify_init();
	}
	return 0;
}

int notify_unregister(int group, int index)
{
	if (notify_status == 0) {
		notify_init();
	}
	return 0;
}

int notify_send(int group, int index)
{
	return 0;
}

int notify_response()
{
	return 0;
}
