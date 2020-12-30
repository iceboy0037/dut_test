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
#include "dio.h"
#include "share_memory.h"

#ifdef SIMULATOR
#include "rdb.h"
static int do_buf[CONFIG_DO_NUMBER];
static int di_buf[CONFIG_DI_NUMBER];
static int pwr_di_buf[CONFIG_PWR_DI_NUMBER];

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
#else
#ifdef M4FIRMWARE
#include "lmem.h"
#include "mu_imx.h"
#include "debug_console_imx.h"
#include "mu.h"
#define DIO_PRINT PRINTF
#else
#include <sys/mman.h>
#include <stdio.h>
#define DIO_PRINT printf
#endif

static volatile unsigned int *dio_addr_base;

#define DI_BASE dio_addr_base
#define DO_BASE (dio_addr_base + (DI_SIZE/sizeof(*dio_addr_base)))


/**
 * @brief DIO shared memory addr init
 * @return int
 * 		0 success
 * 		-1 error
 */
int devs_dio_init(unsigned int addr_base)
{
	if (addr_base == 0)
		return -1;

	dio_addr_base = (volatile unsigned int *)addr_base;
	memset((void *)dio_addr_base, 0, (DI_SIZE + DO_SIZE));
#ifdef M4FIRMWARE
	LMEM_CleanSystemCache(LMEM);
#endif
	return 0;
}

/**
 * @brief DIO shared memory addr deinit
 * @return int
 * 		0 success
 */
int devs_dio_deinit(void)
{
	return 0;
}

/**
 * @brief get DI
 * @param  buf              di data buffer
 * @param  start            start number
 * @param  count            count
 * @return int
 * 		0 success
 * 		-1 error
 */
int devs_di_get(int *buf, int start, int count)
{
	int ret = 0;

	if (NULL == buf || dio_addr_base == NULL)
		return -1;

	if (start >= CONFIG_DI_NUMBER || (start + count) >  CONFIG_DI_NUMBER)
		return -1;

#ifdef M4FIRMWARE
	int i = 0;
	LMEM_CleanSystemCache(LMEM);

	for (i = 0; i < count; i++) {
		buf[i] = *(DI_BASE + start + i);
	}

#else
	// todo: A9 scan DI & set DI share memory
#endif
	return ret;
}

/**
 * @brief set DO
 * @param  start            start number
 * @param  count            count
 * @return int
 * 		0 success
 * 		-1 error
 */
int devs_do_set(int start, int count)
{
	int ret = 0;
	int data = 0;

	if (dio_addr_base == NULL)
		return -1;

	if (start >= CONFIG_DO_NUMBER || (start + count) >  CONFIG_DO_NUMBER)
		return -1;

#ifdef M4FIRMWARE
	data = (start & 0xFF) << 8 | (count & 0xFF);
	MU_SendMsg(MUB, MU_CH, M4 | (SET_DO << CMD_POS) | data);
#else

	// todo: A9 set DO & set DO share memory
	for (data = 0; data < count; data++) {
		*(DO_BASE + start + data) = 1;
	}

#endif
	return ret;
}

/**
 * @brief clean DO
 * @param  start            start number
 * @param  count            count
 * @return int
 *		0 success
 * 		-1 error
 */
int devs_do_clean(int start, int count)
{
	int ret = 0;
	int data = 0;

	if (dio_addr_base == NULL)
		return -1;

	if (start >= CONFIG_DO_NUMBER || (start + count) >  CONFIG_DO_NUMBER)
		return -1;

#ifdef M4FIRMWARE
	data = (start & 0xFF) << 8 | (count & 0xFF);
	MU_SendMsg(MUB, MU_CH, M4 | (CLN_DO << CMD_POS) | data);
#else

	// todo: A9 set DO & set DO share memory
	for (data = 0; data < count; data++) {
		*(DO_BASE + start + data) = 0;
	}

#endif
	return ret;
}

/**
 * @brief Print share memory DI and DO value
 * @return int
 * 		0 success
 * 		-1 error
 */
int devs_dio_dbg(void)
{
	int i = 0;
	DIO_PRINT("==========\n");

	if (NULL == DI_BASE || NULL == DO_BASE)
		return -1;

#ifdef M4FIRMWARE
	LMEM_CleanSystemCache(LMEM);
#endif

	for (i = 0; i < CONFIG_DI_NUMBER; i++) {
		DIO_PRINT("DI [%d] = %d\n", i, *(DI_BASE + i));
	}

	for (i = 0; i < CONFIG_DO_NUMBER; i++) {
		DIO_PRINT("DO [%d] = %d\n", i, *(DO_BASE + i));
	}

	DIO_PRINT("==========\n");
	return 0;
}

#endif