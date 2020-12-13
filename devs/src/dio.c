/**
 * @file dio.c
 * @brief DIO interfaces
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2020-12-13
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-13 <td>1.0     <td>rock     <td>
 * </table>
 */

#include "dtu.h"
#include "devs.h"
#include "rdb.h"
#include "dio.h"


static int do_buf[CONFIG_DO_NUMBER];
static int di_buf[CONFIG_DI_NUMBER];
static int pwr_di_buf[CONFIG_PWR_DI_NUMBER];

#ifdef SIMULATOR
struct sim_do_t sim_do = {
	.count = CONFIG_DO_NUMBER,
	.buf = do_buf
};
struct sim_di_t sim_di = {
	.count = CONFIG_DI_NUMBER,
	.buf = di_buf
};
struct sim_di_t sim_pwr_di = {
	.count = CONFIG_PWR_DI_NUMBER,
	.buf = pwr_di_buf
};
static int tmp[CONFIG_DI_NUMBER] = {0};

int sim_devs_init(void) 
{
	sim_do_init();
	sim_di_init();
	
	return 0;
}
int sim_do_init(void) 
{	
	return sim_do_get(tmp, 0, CONFIG_DI_NUMBER);
}

int sim_di_init(void) 
{
	return sim_di_get(tmp, 0, CONFIG_DI_NUMBER);
}

int sim_do_get(int *buf, int start, int count)
{
	char name[RDB_REPLY_BUF_LEN];
	char value[RDB_REPLY_BUF_LEN];

	if (start >= sim_do.count) {
		return -1;
	}

	if (start + count > sim_do.count) {
		count = sim_do.count - start;
	}

	for (int i = 0; i < count; i++) {
		memset(name, 0, RDB_REPLY_BUF_LEN);
		memset(value, 0, RDB_REPLY_BUF_LEN);
		sprintf(name, "do%d", i);
		if (rdb_get_str(name, value) == TRUE) {
			sim_do.buf[start + i] = atoi(value);						
			buf[i] = sim_do.buf[start + i];
		} else {
			sim_do.buf[start + i] = 0;
			rdb_set_str(name, "0");
			buf[i] = sim_do.buf[start + i];
		}
	}

	return 0;
}

int sim_do_set(int *buf, int start, int count)
{	
	char name[RDB_REPLY_BUF_LEN];
	char value[RDB_REPLY_BUF_LEN];

	if (start >= sim_do.count) {
		return -1;
	}

	if (start + count >= sim_do.count) {
		count = sim_do.count - start;
	}

	for (int i = 0; i < count; i++) {
		memset(name, 0, RDB_REPLY_BUF_LEN);
		memset(value, 0, RDB_REPLY_BUF_LEN);
		sprintf(name, "do%d", i);
		sprintf(value, "%d", buf[i]);
		if (rdb_set_str(name, value) == TRUE) {
			sim_do.buf[start + i] = buf[i];
		} else {
			sim_do.buf[start + i] = 0;
		}
	}
	return 0;
}

int sim_di_get(int *buf, int start, int count)
{
	char name[RDB_REPLY_BUF_LEN];
	char value[RDB_REPLY_BUF_LEN];

	if (start >= sim_di.count) {
		return -1;
	}

	if (start + count > sim_di.count) {
		count = sim_di.count - start;
	}

	for (int i = 0; i < count; i++) {
		memset(name, 0, RDB_REPLY_BUF_LEN);
		memset(value, 0, RDB_REPLY_BUF_LEN);
		sprintf(name, "di%d", i);
		if (rdb_get_str(name, value) == TRUE) {
			sim_di.buf[start + i] = atoi(value);
			buf[i] = sim_di.buf[start + i];
		} else {
			sim_di.buf[start + i] = 0;
			rdb_set_str(name, "0");
			buf[i] = sim_di.buf[start + i];
		}
	}

	return 0;
}

int sim_di_set(int *buf, int start, int count)
{
	char name[RDB_REPLY_BUF_LEN];
	char value[RDB_REPLY_BUF_LEN];

	if (start >= sim_di.count) {
		return -1;
	}

	if (start + count >= sim_di.count) {
		count = sim_di.count - start;
	}

	for (int i = 0; i < count; i++) {
		memset(name, 0, RDB_REPLY_BUF_LEN);
		memset(value, 0, RDB_REPLY_BUF_LEN);
		sprintf(name, "di%d", i);
		sprintf(value, "%d", buf[i]);
		if (rdb_set_str(name, value) == TRUE) {
			sim_di.buf[start + i] = buf[i];
		} else {
			sim_di.buf[start + i] = 0;
		}
	}
	return 0;
}
#endif