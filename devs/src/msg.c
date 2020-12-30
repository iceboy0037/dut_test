
/**
 * @file msg.c
 * @brief message queue
 * @author jiashipeng (1060728573@qq.com)
 * @version 1.0
 * @date 2020-12-16
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-16 <td>1.0     <td>jiashipeng     <td>message queue
 * </table>
 */
#ifndef SIMULATOR

#include "msg.h"
#include "share_memory.h"
#include "mu.h"
#include <stddef.h>
#include <string.h>
#ifdef M4FIRMWARE
#include "board.h"
#include "mu_imx.h"
#include "debug_console_imx.h"
#include "lmem.h"
#else
#include <sys/mman.h>
#include <stdio.h>
#endif

static struct mq_queue_t *mq;
#define mqbuf ((char *)((char *)mq + MSG_QUEUE_STRUCT_SIZE))

/**
 * @brief Malloc a message memory
 * @return void*
 * 	The message address of the malloc
 */
void *mq_malloc_msg(void)
{
	unsigned int now = 0;
#ifdef M4FIRMWARE
	LMEM_CleanSystemCache(LMEM);
#endif

	if (mq == NULL || mq->count == MSG_QUEUE_LENGTH) {
		return NULL;
	}

	now = mq->in;
	mq->in += 1;
	mq->in %= MSG_QUEUE_LENGTH;
	mq->count++;
#ifdef M4FIRMWARE
	LMEM_CleanSystemCache(LMEM);
#endif
	return (void *)((mqbuf) + (now * MSG_QUEUE_ITEM_SIZE));
}

/**
 * @brief free message memory
 * @param  count            message count
 * @return int
 * 		0 success
 * 		-1 error
 */
int mq_free_msg(int count)
{
	int i;

	if (mq == NULL) {
		return -1;
	}

	for (i = 0; i < count; i++) {
#ifdef M4FIRMWARE
		LMEM_CleanSystemCache(LMEM);
#endif

		if (mq->count == 0) {
			return i;
		}

		memset((mqbuf) + (mq->out * MSG_QUEUE_ITEM_SIZE), 0, MSG_QUEUE_ITEM_SIZE);
		mq->out += 1;
		mq->out %= MSG_QUEUE_LENGTH;
		mq->count--;
#ifdef M4FIRMWARE
		LMEM_CleanSystemCache(LMEM);
#endif
	}

	return i;
}

/**
 * @brief Message queue current message addr
 * @return void* message addr
 */
void *mq_curr_msg(void)
{
#ifdef M4FIRMWARE
	LMEM_CleanSystemCache(LMEM);
#endif

	if (mq->count && mq != NULL) {
		return (void *)((mqbuf) + (mq->out * MSG_QUEUE_ITEM_SIZE));
	} else
		return NULL;
}

/**
 * @brief Message queue share memory init
 * @return int
 * 		0 success
 * 		-1 error
 */
int mq_init(unsigned int addr_base)
{
	if (addr_base == 0) {
		return -1;
	}

	mq = (struct mq_queue_t *)addr_base;
	mq->count = 0;
	mq->in = 0;
	mq->out = 0;
#ifdef M4FIRMWARE
	LMEM_CleanSystemCache(LMEM);
#endif
	return 0;
}

/**
 * @brief Message queue share memory deinit
 * @return int
 * 		0 success
 * 		-1 error
 */
int mq_deinit(void)
{
	return 0;
}
#ifdef M4FIRMWARE
/**
 * @brief log callback
 * @param  arg              Callback param
 * @return int
 */
int log_cb(void *arg)
{
	PRINTF("send log ok\r\n");
	return 0;
}

/**
 * @brief send a log to A9
 * @param  level            log level
 * @param  buf              log buffer
 * @param  size             log buffer size
 * @return int
 * 		0 success
 * 		-1 error
 */
int plog(int level, char *buf, int size)
{
	int ret = 0;
	struct msg_t *msg;
	msg = (struct msg_t *)mq_malloc_msg();

	if (msg == NULL || buf == NULL)
		return -1;

	if (size > LOG_BUF_SIZE_MAX)
		size = LOG_BUF_SIZE_MAX;

	memset(msg, 0, sizeof(struct msg_t));
	msg->type = LOG;
	msg->data.log.level = level;
	msg->cb = log_cb;
	memcpy(msg->data.log.buf, buf, size);
	LMEM_CleanSystemCache(LMEM);
	ret = MU_TrySendMsg(MUB, MU_CH, M4 | (MSG << CMD_POS) | M4_SEND);

	if (ret != kStatus_MU_Success) {
		return ret;
	}

	return ret;
}

int event_cb(void *arg)
{
	PRINTF("send event ok\r\n");
	return 0;
}
int event(int type, int value)
{
	int ret = 0;
	struct msg_t *msg;
	msg = (struct msg_t *)mq_malloc_msg();

	if (msg == NULL)
		return -1;

	memset(msg, 0, sizeof(struct msg_t));
	msg->type = EVENT;
	msg->data.event.type = type;
	msg->data.event.value = value;
	msg->cb = event_cb;
	LMEM_CleanSystemCache(LMEM);
	ret = MU_TrySendMsg(MUB, MU_CH, M4 | (MSG << CMD_POS) | M4_SEND);

	if (ret != kStatus_MU_Success) {
		return ret;
	}

	return ret;
}

#else
#endif
#endif