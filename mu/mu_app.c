/**
 * @file mu_app.c
 * @brief A9 APP
 * @author jiashipeng (1060728573@qq.com)
 * @version 1.0
 * @date 2020-12-23
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-23 <td>1.0     <td>jiashipeng     <td>A9 APP
 * </table>
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include "mu.h"
#include "dbg.h"
#include "msg.h"
#include "dio.h"
#include <sys/mman.h>
#include <sys/time.h>
#include "share_memory.h"

#define MU_DEV_FILE "/dev/imx6sx_mu"
#define MU_MSG_BUFF_SIZE 30
struct queue_t {
	int in;
	int out;
	int count;
	unsigned int msg_buff[MU_MSG_BUFF_SIZE];
};
static int fd = 0;
static int memfd = 0;
static void *ocram_base = NULL;
static int m4_is_alive = 1;


int get_m4_status(void)
{
	return m4_is_alive;
}

static void sigalrm_func(int signum)
{
	m4_is_alive = 0;
	dbg("M4 no alive\n");
}

static void kick_dog(void)
{
	int ret = 0;
	struct itimerval value, old_value;
	value.it_interval.tv_sec = 15;
	value.it_interval.tv_usec = 0;
	value.it_value.tv_sec = 15;
	value.it_value.tv_usec = 0;
	ret = setitimer(ITIMER_REAL, &value, &old_value);

	if (ret < 0)
		dbg("setitimer err\n");

	m4_is_alive = 1;
}

static int dtu_msg_handler(void)
{
	struct msg_t *curr_msg = NULL;
	char tmp_log[100] = {0};
	curr_msg = (struct msg_t *)mq_curr_msg();

	if (NULL == curr_msg)
		return -1;

	switch (curr_msg->type) {
	case LOG:
		if (curr_msg->data.log.buf != NULL) {
			memcpy(tmp_log, curr_msg->data.log.buf, sizeof(tmp_log));
			printf("m4 log :%s", curr_msg->data.log.buf);
		} else {
			dbg("msg err curr_msg_p %#x, log buffer %#x\n",
			    (unsigned int)curr_msg,
			    (unsigned int)curr_msg->data.log.buf);
		}

		break;

	case EVENT:
		dbg("m4 event type %d, value %d\n",
		    curr_msg->data.event.type,
		    curr_msg->data.event.value);
		break;

	default:
		dbg("msg type err, %d\n", curr_msg->type);
		break;
	}

	mq_free_msg(1);
	return 0;
}

static int dtu_mu_msg_handler(unsigned int msg)
{
	int ret = 0;
	short mu_cmd = 0;
	short mu_data = 0;
	mu_cmd = (msg & CMD_MASK) >> CMD_POS;
	mu_data = (msg & CMD_DATA_MASK);

	switch (mu_cmd) {
	case MSG:
		if (mu_data == M4_SEND)
			dtu_msg_handler();

		break;

	case SET_DO:
		ret = do_set(mu_data >> 8, mu_data & 0xFF);

		if (ret < 0)
			dbg("do set err\n");

		break;

	case SET_DO_VALUE:
		ret = do_set_value(mu_data >> 8, mu_data & 0xFF);

		if (ret < 0)
			dbg("do set value err\n");

		break;

	case CLEAR_DO:
		ret = do_clr(mu_data >> 8, mu_data & 0xFF);

		if (ret < 0)
			dbg("do clear err\n");

		break;

	case KICK_DOG:
		kick_dog();
		break;

	default:
		dbg("err msg %#x\n", msg);
		break;
	}

	return 0;
}

static void sigio_signal_func(int signum)
{
	int ret = 0;
	struct queue_t msg_queue = {0};

	if (fd < 0) {
		dbg("Unable to operate file\n");
	}

	ret = read(fd, &msg_queue, sizeof(msg_queue));

	if (ret < 0) {
		dbg("read fail.\n");
	}

	for (; msg_queue.count > 0; msg_queue.count--) {
		dtu_mu_msg_handler(msg_queue.msg_buff[msg_queue.out]);
		msg_queue.out++;
		msg_queue.out %= MU_MSG_BUFF_SIZE;
	}
}

static void sigint_func(int signum)
{
	int ret = 0;
	ret = mq_deinit();

	if (ret < 0)
		dbg("message queue deinit err\n");

	ret = dio_deinit();

	if (ret < 0)
		dbg("dio deinit err\n");

	ret = munmap(ocram_base, OCRAM_SIZE);

	if (ret < 0)
		dbg("ocram munmap err\n");

	ret = close(fd);

	if (ret < 0)
		dbg("close %s err\n", MU_DEV_FILE);

	ret = close(memfd);

	if (ret < 0)
		dbg("close %s err\n", "/dev/mem");

	_exit(0);
}

int main(int argc, char *argv[])
{
	int flags = 0;
	int ret = 0;
	memfd = open("/dev/mem", O_RDWR | O_SYNC);

	if (memfd < 0) {
		printf("open /dev/mem fail\n");
		return -1;
	}

	ocram_base = mmap(0, OCRAM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, memfd, OCRAM_ADDR);
	dbg("ocram base %#x\n", (unsigned int)ocram_base);

	if (NULL == ocram_base) {
		dbg("OCRAM mmap err\n");
		return -1;
	}

	ret = hw_dio_init((unsigned int)((char *)ocram_base + DI_ADDR_OFFSET));

	if (ret < 0) {
		dbg("dio init err\n");
		return -1;
	}

	ret = mq_init((unsigned int)((char *)ocram_base + MSG_QUEUE_STRUCT_ADDR_OFFSET));

	if (ret < 0) {
		dbg("dio init err\n");
		return -1;
	}

	fd = open(MU_DEV_FILE, O_RDWR);

	if (fd < 0) {
		dbg("open fail.\n");
		return -1;
	}

	signal(SIGIO, sigio_signal_func);
	signal(SIGINT, sigint_func);
	signal(SIGALRM, sigalrm_func);
	kick_dog();
	ret = fcntl(fd, F_SETOWN, getpid());

	if (ret < 0) {
		dbg("fcntl F_SETOWN err\n");
		return -1;
	}

	flags = fcntl(fd, F_GETFD);

	if (flags < 0) {
		dbg("fcntl F_GETFD err\n");
		return -1;
	}

	ret = fcntl(fd, F_SETFL, flags | FASYNC);

	if (ret < 0) {
		dbg("fcntl F_SETFL err\n");
		return -1;
	}

	while (1) {
		sleep(2);
	}

	ret = mq_deinit();

	if (ret < 0) {
		dbg("message queue deinit err\n");
		return -1;
	}

	ret = dio_deinit();

	if (ret < 0) {
		dbg("dio deinit err\n");
		return -1;
	}

	ret = munmap(ocram_base, OCRAM_SIZE);

	if (ret < 0) {
		dbg("ocram munmap err\n");
		return -1;
	}

	ret = close(fd);

	if (ret < 0) {
		dbg("close %s err\n", MU_DEV_FILE);
		return -1;
	}

	ret = close(memfd);

	if (ret < 0) {
		dbg("close %s err\n", "/dev/mem");
		return -1;
	}

	return 0;
}