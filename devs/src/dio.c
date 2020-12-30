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

#ifdef SIMULATOR
#include "rdb.h"
#else
#include "share_memory.h"
#ifdef M4FIRMWARE
#include "lmem.h"
#include "mu_imx.h"
#include "debug_console_imx.h"
#include "mu.h"
#else
#include <sys/mman.h>
#include <stdio.h>
#endif
#endif

#ifndef SIMULATOR
static volatile unsigned int *dio_addr_base;
#define DI_BASE dio_addr_base
#define DO_BASE (dio_addr_base + (DI_SIZE / sizeof(*dio_addr_base)))

/**
 * @brief DIO shared memory addr init
 * @return int
 * 		0 success
 * 		-1 error
 */
static int hw_dio_init(unsigned int addr_base)
{
	if (addr_base == 0) {
		return -1;
	}

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
static int hw_dio_deinit(void)
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
static int hw_di_get(int *buf, int start, int count)
{
	int ret = 0;
	int limit = di_get_limit();

	CHECK_DIO_RANGE();
	if (NULL == buf || dio_addr_base == NULL) {
		return -1;
	}

#ifdef M4FIRMWARE
	LMEM_CleanSystemCache(LMEM);
	for (int i = 0; i < count; i++) {
		buf[i] = *(DI_BASE + start + i);
	}
#else
	// todo: A9 scan DI & set DI share memory
#endif
	return ret;
}

static int hw_do_set(int start, int count)
{
	int ret = 0;
	int data = 0;
	int limit = do_get_limit();

	CHECK_DIO_RANGE();
	if (dio_addr_base == NULL) {
		return -1;
	}

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
static int hw_do_clear(int start, int count)
{
	int ret = 0;
	int data = 0;

	if (dio_addr_base == NULL) {
		return -1;
	}

	if (start >= CONFIG_DO_NUMBER || (start + count) >  CONFIG_DO_NUMBER) {
		return -1;
	}

#ifdef M4FIRMWARE
	data = (start & 0xFF) << 8 | (count & 0xFF);
	MU_SendMsg(MUB, MU_CH, M4 | (CLN_DO << CMD_POS) | data);
#else

	// TODO: A9 set DO & set DO share memory
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
int hw_dio_dbg(void)
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


/**
 * @brief Init DIO system
 * @param  base	DIO buffer base address
 * @return int 0 - success
 */
int dio_init(void)
{
#ifdef SIMULATOR
	int limit = di_get_limit();
	char key[RDB_KEY_LEN];
	char *value = "0";

	for (int i = 0; i < limit; i++) {
		snprintf(key, RDB_KEY_LEN, "di%d", i);
		if (rdb_exists(key) != SUCCESS) {
			if (rdb_set_str(key, value) != SUCCESS) {
				dbg("Create dio failed\n");
				return -1;
			};
		}
	}

	limit = do_get_limit();
	for (int i = 0; i < limit; i++) {
		snprintf(key, RDB_KEY_LEN, "do%d", i);
		if (rdb_exists(key) != SUCCESS) {
			if (rdb_set_str(key, value) != SUCCESS) {
				dbg("Create dio failed\n");
				return -1;
			};
		}
	}
	return 0;
#else
	return hw_dio_init(dio_addr_base);
#endif
}

/**
 * @brief De-Init DIO system
 * @return int 0 - success
 */
int dio_deinit(void)
{
	return 0;
}

/**
 * @brief Get DI status from DI boards
 * @param  buf DI status return buffer
 * @param  start DI start index
 * @param  count DI Count that wanted
 * @return int 0 - success
 */
int di_get(int *buf, int start, int count)
{
	int limit = di_get_limit();

	CHECK_DIO_RANGE();
#ifdef SIMULATOR
	char key[RDB_KEY_LEN] = { 0 };
	char value[RDB_VAL_LEN] = { 0 };

	for (int i = 0; i < count; i++) {
		snprintf(key, RDB_KEY_LEN, "di%d", start + i);
		if (rdb_get_str(key, value) == SUCCESS) {
			buf[i] = atoi(value);
		} else {
			dbg("Failed: index = %d\n", i);
			return FAIL;
		}
	}
#else

#endif
	return SUCCESS;
}

/**
 * @brief Get DO status from DO buffer
 * @param  buf DO status return buffer
 * @param  start DO start index
 * @param  count DO Count that wanted
 * @return int 0 - success
 */
int do_get(int *buf, int start, int count)
{
	int limit = do_get_limit();

	CHECK_DIO_RANGE();
#ifdef SIMULATOR
	char key[RDB_KEY_LEN] = { 0 };
	char value[RDB_VAL_LEN] = { 0 };

	for (int i = 0; i < count; i++) {
		snprintf(key, RDB_KEY_LEN, "do%d", start + i);
		if (rdb_get_str(key, value) == SUCCESS) {
			buf[i] = atoi(value);
		} else {
			dbg("Failed: index = %d\n", i);
			return FAIL;
		}
	}
#else
	// TODO: A9 or M4 get
#endif
	return SUCCESS;
}

/**
 * @brief Set DO value
 * @param  buf	DO buffer value
 * @param  start Start index
 * @param  count DO Count
 * @return int 0 - success
 */
int do_set_buf(int *buf, int start, int count)
{
	int limit = do_get_limit();

	CHECK_DIO_RANGE();
#if defined SIMULATOR
	char name[RDB_KEY_LEN];
	char value[RDB_VAL_LEN];

	for (int i = 0; i < count; i++) {
		memset(name, 0, RDB_KEY_LEN);
		memset(value, 0, RDB_VAL_LEN);
		sprintf(name, "do%d", start + i);
		sprintf(value, "%d", buf[i]);

		if (rdb_set_str(name, value) != SUCCESS) {
			dbg("Set DO status failed, index = %d\n", i);
			return FAIL;
		}
	}
#else

#endif
	return SUCCESS;
}

/**
 * @brief Set DI value, Only valid in simulator environment
 * @param  buf	DI buffer value
 * @param  start Start index
 * @param  count DI Count
 * @return int 0 - success
 */
int di_set_buf(int *buf, int start, int count)
{
	int limit = di_get_limit();

	CHECK_DIO_RANGE();
#if defined SIMULATOR
	char name[RDB_KEY_LEN];
	char value[RDB_VAL_LEN];
	for (int i = 0; i < count; i++) {
		memset(name, 0, RDB_KEY_LEN);
		memset(value, 0, RDB_VAL_LEN);
		sprintf(name, "di%d", start + i);
		sprintf(value, "%d", buf[i]);

		if (rdb_set_str(name, value) != SUCCESS) {
			dbg("Set DI status failed, index = %d\n", i);
			return FAIL;
		}
	}
#endif

	return SUCCESS;
}

/**
 * @brief Set DO status
 * @param  buf DO status return buffer
 * @param  start DO start index
 * @param  count DO Count that wanted
 * @return int 0 - success
 */
int do_set(int start, int count)
{
#ifdef SIMULATOR
	int buf[CONFIG_DO_NUMBER];
	for (int i = 0; i < count; i++) {
		buf[i] = 1;
	}
	return do_set_buf(buf, start, count);
#else
	// TODO: Set in M4 or A9
	return hw_do_set(start, count);
#endif
}

/**
 * @brief Clear DO Status
 * @param  start Start index
 * @param  count DO channel count
 * @return int 0 - success
 */
int do_clr(int start, int count)
{
#if defined SIMULATOR
	int buf[CONFIG_DO_NUMBER];
	for (int i = 0; i < count; i++) {
		buf[i] = 0;
	}
	return do_set_buf(buf, start, count);
#else
	return hw_do_clear(start, count);
#endif
}
