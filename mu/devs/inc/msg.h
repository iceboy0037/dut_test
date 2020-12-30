/**
 * @file msg.h
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
#ifndef __MSG_H__
#define __MSG_H__

#ifndef SIMULATOR
#define QUEUE_FULL -1
#define QUEUE_EMPTY -2
#define QUEUE_SUCCESS 0

#define MSG_QUEUE_LENGTH 10
#define MSG_QUEUE_ITEM_SIZE (2048)
#define LOG_BUF_SIZE_MAX (512)

struct mq_queue_t {
	int in;
	int out;
	int count;
};

enum msg_type {
	LOG,
	EVENT,
	ERROR_TYPE,
};


struct LOG_T {
	char level;
	char buf[LOG_BUF_SIZE_MAX];
};

struct EVENT_T {
	int type;
	int value;
};

typedef int (*msg_callback)(void *);
struct msg_t {
	int version;
	enum msg_type type;
	msg_callback cb;
	void *param;
	union data {
		struct LOG_T log;
		struct EVENT_T event;
	} data;
};

/**
 * @brief Message queue current message addr
 * @return void* message addr
 */
extern void *mq_curr_msg(void);

/**
 * @brief Message queue share memory init
 * @return int
 * 		0 success
 * 		-1 error
 */
extern int mq_init(unsigned int addr_base);

/**
 * @brief Message queue share memory deinit
 * @return int
 * 		0 success
 * 		-1 error
 */
extern int mq_deinit(void);

extern int mq_free_msg(int count);
#ifdef M4FIRMWARE
#include <stdio.h>

/**
 * @brief send a log to A9
 * @param  level            log level
 * @param  buf              log buffer
 * @param  size             log buffer size
 * @return int
 * 		0 success
 * 		-1 error
 */
extern int plog(int level, char *buf, int size);

extern int event(int type, int value);

#define LOGD(fmt, args...)       do {\
		char s[LOG_BUF_SIZE_MAX];				\
		snprintf(s, sizeof(s), "[Line:%d]Func-%s:"fmt,		\
			 __LINE__, __FUNCTION__, ##args);		\
		plog(0, s, sizeof(s));					\
	} while (0)
#endif
#endif
#endif // !__MSG_H__