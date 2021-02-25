/**
 * @file nodify.h
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
#ifndef __NOTIFY_H__
#define __NOTIFY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "list.h"

#define NOTIFY_TABLE		1
#define	NOTIFY_MESSAGE		0
#define	NOTIFY_SERVER		0
#define NOTIFY_CLIENT		1

#define NOTIFY_GROUP_SHIFT 	(24)
#define NOTIFY_INDEX_MASK 	(0x00ffffff)
#define NOTIFY_GROUP_MASK 	(0xff << NOTIFY_GROUP_SHIFT)

#define MKNID(group, index)	((group << NOTIFY_GROUP_SHIFT) | (index & NOTIFY_INDEX_MASK))

struct notify_list_t {
	int key;
	int arg;
	int (*callback)(int);
	struct list_head list;
};

extern int notify_send(int key);
extern int notify_deinit(void);
extern int notify_init(int mode);
extern int notify_register(int group, int index, void *callback, int arg);
extern int notify_print_list(void);
extern int notify_unregister(int group, int index);

#ifdef __cplusplus
}
#endif
#endif