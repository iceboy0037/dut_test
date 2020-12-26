/**
 * @file command.c
 * @brief Shell command implementation
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2020-12-13
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-13 <td>1.0     <td>rock     <td>Modify Content
 * </table>
 */
#include "simulator.h"
#include "main.h"
#include "devs.h"
#include "rdb.h"
#include "dbg.h"
#include "dio.h"

static int shell_cmd_lsdi(int argc, char *argv)
{
	int i;

	printf("----------------DI Status----------------\n");
	printf("Seq\tStatus\n");
	for (i = 0; i < sim_di.count; i++) {
		printf("%d\t%d\n", i, sim_di.buf[i]);
	}
	printf("\n");

	return 0;
}

static int shell_cmd_lsdo(int argc, char *argv)
{
	int i;

	printf("----------------DO Status----------------\n");
	printf("Seq\tStatus\n");
	for (i = 0; i < sim_do.count; i++) {
		printf("%d\t%d\n", i, sim_do.buf[i]);
	}
	printf("\n");

	return 0;
}

static int shell_cmd_setdo(int argc, char *argv)
{
	int start;
	int count;
	int buf[CONFIG_DO_NUMBER];

	if (argc == 2) {
		start = atoi(ARGV(1));
		count = 1;
		if (start < 0 || start > CONFIG_DO_NUMBER) {
			printf("Start value out of range, {0 ~ %d}\n", CONFIG_DO_NUMBER - 1);
			return -1;
		}
		buf[0] = 1;
		if (sim_do_set(buf, start, count) == 0) {
			printf("Set DO %d to 1 success\n", start);
			return 0;
		} else {
			printf("Set DO %d to 1 failed\n", start);
			return -1;
		}
	}

	if (argc == 3) {
		start = atoi(ARGV(1));
		count = atoi(ARGV(2));
		if (start < 0 || start > CONFIG_DO_NUMBER || count > (CONFIG_DO_NUMBER - start)) {
			printf("Out of range, {0 ~ %d}\n", CONFIG_DO_NUMBER - 1);
			return -1;
		}
		for (int i = 0; i < count; i++) {
			buf[i] = 1;
		}
		if (sim_do_set(buf, start, count) == 0) {
			printf("Set DO (%d ~ %d) to 1 success\n", start, start + count);
			return 0;
		} else {
			printf("Set DO (%d ~ %d) to 1 failed\n", start, start + count);
			return -1;
		}
	}

	printf("Usage: setdo <start> <count>\n");
	return -1;
}

static int shell_cmd_setdi(int argc, char *argv)
{
	int start;
	int count;
	int buf[CONFIG_DI_NUMBER];

	if (argc == 2) {
		start = atoi(ARGV(1));
		count = 1;
		if (start < 0 || start > CONFIG_DI_NUMBER) {
			printf("Start value out of range, {0 ~ %d}\n", CONFIG_DI_NUMBER - 1);
			return -1;
		}
		buf[0] = 1;
		if (sim_di_set(buf, start, count) == 0) {
			printf("Set DI %d to 1 success\n", start);
			return 0;
		} else {
			printf("Set DI %d to 1 failed\n", start);
			return -1;
		}
	}

	if (argc == 3) {
		start = atoi(ARGV(1));
		count = atoi(ARGV(2));
		if (start < 0 || start > CONFIG_DI_NUMBER || count > (CONFIG_DI_NUMBER - start)) {
			printf("Out of range, {0 ~ %d}\n", CONFIG_DI_NUMBER - 1);
			return -1;
		}
		for (int i = 0; i < count; i++) {
			buf[i] = 1;
		}
		if (sim_di_set(buf, start, count) == 0) {
			printf("Set DI (%d ~ %d) to 1 success\n", start, start + count);
			return 0;
		} else {
			printf("Set DI (%d ~ %d) to 1 failed\n", start, start + count);
			return -1;
		}
	}

	printf("Usage: setdi <start> <count>\n");
	return -1;
}

static int shell_cmd_clrdo(int argc, char *argv)
{
	int start;
	int count;
	int buf[CONFIG_DO_NUMBER];

	if (argc == 2) {
		start = atoi(ARGV(1));
		count = 1;
		if (start < 0 || start > CONFIG_DO_NUMBER) {
			printf("Start value out of range, {0 ~ %d}\n", CONFIG_DO_NUMBER - 1);
			return -1;
		}
		buf[0] = 0;
		if (sim_do_set(buf, start, count) == 0) {
			printf("Clear DO %d to 0 success\n", start);
			return 0;
		} else {
			printf("Clear DO %d to 0 failed\n", start);
			return -1;
		}
	}

	if (argc == 3) {
		start = atoi(ARGV(1));
		count = atoi(ARGV(2));
		if (start < 0 || start > CONFIG_DO_NUMBER || count > (CONFIG_DO_NUMBER - start)) {
			printf("Out of range, {0 ~ %d}\n", CONFIG_DO_NUMBER - 1);
			return -1;
		}
		for (int i = 0; i < count; i++) {
			buf[i] = 0;
		}
		if (sim_do_set(buf, start, count) == 0) {
			printf("Clear DO (%d ~ %d) to 0 success\n", start, start + count);
			return 0;
		} else {
			printf("Clear DO (%d ~ %d) to 0 failed\n", start, start + count);
			return -1;
		}
	}
	printf("Usage: clrdo <start> <count>\n");
	return -1;
}

static int shell_cmd_clrdi(int argc, char *argv)
{
	int start;
	int count;
	int buf[CONFIG_DI_NUMBER];

	if (argc == 2) {
		start = atoi(ARGV(1));
		count = 1;
		if (start < 0 || start > CONFIG_DI_NUMBER) {
			printf("Start value out of range, {0 ~ %d}\n", CONFIG_DI_NUMBER - 1);
			return -1;
		}
		buf[0] = 0;
		if (sim_di_set(buf, start, count) == 0) {
			printf("Clear DI %d to 0 success\n", start);
			return 0;
		} else {
			printf("Clear DI %d to 0 failed\n", start);
			return -1;
		}
	}

	if (argc == 3) {
		start = atoi(ARGV(1));
		count = atoi(ARGV(2));
		if (start < 0 || start > CONFIG_DI_NUMBER || count > (CONFIG_DI_NUMBER - start)) {
			printf("Out of range, {0 ~ %d}\n", CONFIG_DI_NUMBER - 1);
			return -1;
		}
		for (int i = 0; i < count; i++) {
			buf[i] = 0;
		}
		if (sim_di_set(buf, start, count) == 0) {
			printf("Clear DI (%d ~ %d) to 0 success\n", start, start + count);
			return 0;
		} else {
			printf("Clear DI (%d ~ %d) to 0 failed\n", start, start + count);
			return -1;
		}
	}
	printf("Usage: clrdi <start> <count>\n");
	return -1;
}

static int shell_cmd_togdo(int argc, char *argv)
{
	int start;
	int count;
	int buf[CONFIG_DO_NUMBER];

	if (argc == 2) {
		start = atoi(ARGV(1));
		count = 1;
		if (start < 0 || start > CONFIG_DO_NUMBER) {
			printf("Start value out of range, {0 ~ %d}\n", CONFIG_DO_NUMBER - 1);
			return -1;
		}

		sim_do_get(buf, start, 1);
		if (buf[0] == 1) {
			buf[0] = 0;
		} else {
			buf[0] = 1;
		}

		if (sim_do_set(buf, start, count) == 0) {
			printf("Toggle DO %d success\n", start);
			return 0;
		} else {
			printf("Toggle DO %d failed\n", start);
			return -1;
		}
	}

	if (argc == 3) {
		start = atoi(ARGV(1));
		count = atoi(ARGV(2));
		if (start < 0 || start > CONFIG_DO_NUMBER || count > (CONFIG_DO_NUMBER - start)) {
			printf("Out of range, {0 ~ %d}\n", CONFIG_DO_NUMBER - 1);
			return -1;
		}

		sim_do_get(buf, start, count);
		for (int i = 0; i < count; i++) {
			if (buf[i] == 1) {
				buf[i] = 0;
			} else {
				buf[i] = 1;
			}
		}

		if (sim_do_set(buf, start, count) == 0) {
			printf("Toggle DO (%d ~ %d) success\n", start, start + count);
			return 0;
		} else {
			printf("Toggle DO (%d ~ %d) failed\n", start, start + count);
			return -1;
		}
	}
	printf("Usage: togdo <start> <count>\n");
	return -1;
}

static int shell_cmd_togdi(int argc, char *argv)
{
	int start;
	int count;
	int buf[CONFIG_DI_NUMBER];

	if (argc == 2) {
		start = atoi(ARGV(1));
		count = 1;
		if (start < 0 || start > CONFIG_DI_NUMBER) {
			printf("Start value out of range, {0 ~ %d}\n", CONFIG_DI_NUMBER - 1);
			return -1;
		}

		sim_di_get(buf, start, 1);
		if (buf[0] == 1) {
			buf[0] = 0;
		} else {
			buf[0] = 1;
		}

		if (sim_di_set(buf, start, count) == 0) {
			printf("Toggle DI %d success\n", start);
			return 0;
		} else {
			printf("Toggle DI %d failed\n", start);
			return -1;
		}
	}

	if (argc == 3) {
		start = atoi(ARGV(1));
		count = atoi(ARGV(2));
		if (start < 0 || start > CONFIG_DI_NUMBER || count > (CONFIG_DI_NUMBER - start)) {
			printf("Out of range, {0 ~ %d}\n", CONFIG_DI_NUMBER - 1);
			return -1;
		}

		sim_di_get(buf, start, count);
		for (int i = 0; i < count; i++) {
			if (buf[i] == 1) {
				buf[i] = 0;
			} else {
				buf[i] = 1;
			}
		}

		if (sim_di_set(buf, start, count) == 0) {
			printf("Toggle DI (%d ~ %d) success\n", start, start + count);
			return 0;
		} else {
			printf("Toggle DI (%d ~ %d) failed\n", start, start + count);
			return -1;
		}
	}
	printf("Usage: togdi <start> <count>\n");
	return -1;
}

static int shell_cmd_dbset(int argc, char *argv)
{
	if (argc != 3) {
		printf("Usage: dbset <key> <value>\n");
		return -1;
	}
	if (rdb_set_str(ARGV(1), ARGV(2)) != TRUE) {
		dbg("Set %s failed\n", ARGV(1));
		return -1;
	}
	dbg("Set %s to %s success\n", ARGV(1), ARGV(2));

	return 0;
}

static int shell_cmd_dbget(int argc, char *argv)
{
	char buf[RDB_REPLY_BUF_LEN] = {0};

	if (argc != 2) {
		printf("Usage: dbset <key> <value>\n");
		return -1;
	}

	if (rdb_get_str(ARGV(1), buf) != TRUE) {
		dbg("Get %s failed\n", ARGV(1));
		return -1;
	}
	dbg("Get %s success : value = %s\n", ARGV(1), buf);

	return 0;
}

static int shell_cmd_saveyc(int argc, char *argv)
{
	yc_save_table();
	return 0;
}
#include "command.inc"