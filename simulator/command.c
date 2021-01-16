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
 * <tr><td>2020-12-13 <td>1.0     <td>rock     <td>Create
 * <tr><td>2020-12-30 <td>1.0     <td>rock     <td>Merge Simulator and HW interface
 * </table>
 */
#include "simulator.h"
#include "main.h"
#include "devs.h"
#include "rdb.h"
#include "dbg.h"
#include "dio.h"
#include "yc.h"
#include "yx.h"
#include "tables.h"
#include "dtu_data.h"

static int cmd_di_buf[CONFIG_DI_NUMBER];
static int cmd_do_buf[CONFIG_DO_NUMBER];
static int shell_cmd_lsdi(int argc, char *argv)
{
	int i;
	int count = di_get_limit();

	if (di_get(cmd_di_buf, 0, count) != SUCCESS) {
		dbg("Get DI Failed\n");
		return -1;
	}

	println("----------------DI Status----------------\n");
	println("Seq\tStatus\n");
	for (i = 0; i < count; i++) {
		println("%d\t%d\n", i, cmd_di_buf[i]);
	}
	println("\n");

	return 0;
}

static int shell_cmd_lsdo(int argc, char *argv)
{
	int i;
	int count = do_get_limit();

	if (do_get(cmd_do_buf, 0, count) != SUCCESS) {
		dbg("Get DO Failed\n");
		return -1;
	}

	println("----------------DO Status----------------\n");
	println("Seq\tStatus\n");
	for (i = 0; i < count; i++) {
		println("%d\t%d\n", i, cmd_do_buf[i]);
	}
	println("\n");

	return 0;
}

static int shell_cmd_setdo(int argc, char *argv)
{
	int start;
	int count;
	int buf[CONFIG_DO_NUMBER];
	int limit = do_get_limit();

	if (argc > 3) {
		println("Usage: setdo <start> <count>\n");
		return -1;
	}

	start = atoi(ARGV(1));
	count = (argc == 2) ? 1 : atoi(ARGV(2));
	if (start < 0 || start > limit || count > (limit - start)) {
		println("Out of range, {0 ~ %d}\n", limit - 1);
		return -1;
	}
	for (int i = 0; i < count; i++) {
		buf[i] = 1;
	}
	if (do_set_buf(buf, start, count) == 0) {
		println("Set DO (%d ~ %d) to 1 success\n", start, start + count);
		return 0;
	}

	println("Set DO (%d ~ %d) to 1 failed\n", start, start + count);
	return -1;
}

static int shell_cmd_setdi(int argc, char *argv)
{
	int start;
	int count;
	int buf[CONFIG_DI_NUMBER];
	int limit = di_get_limit();

	if (argc > 3) {
		println("Usage: setdi <start> <count>\n");
		return -1;
	}

	start = atoi(ARGV(1));
	count = (argc == 2) ? 1 : atoi(ARGV(2));
	CHECK_DIO_RANGE();
	for (int i = 0; i < count; i++) {
		buf[i] = 1;
	}
	if (di_set_buf(buf, start, count) == 0) {
		println("Set DI (%d ~ %d) to 1 success\n", start, start + count);
		return 0;
	}

	println("Set DI (%d ~ %d) to 1 failed\n", start, start + count);
	return -1;
}

static int shell_cmd_clrdo(int argc, char *argv)
{
	int start;
	int count;
	int buf[CONFIG_DO_NUMBER];
	int limit = do_get_limit();

	if (argc > 3) {
		println("Usage: clrdo <start> <count>\n");
		return -1;
	}

	start = atoi(ARGV(1));
	count = (argc == 2) ? 1 : atoi(ARGV(2));
	CHECK_DIO_RANGE();
	for (int i = 0; i < count; i++) {
		buf[i] = 0;
	}
	if (do_set_buf(buf, start, count) == 0) {
		println("Clear DO (%d ~ %d) to 1 success\n", start, start + count);
		return 0;
	}

	println("Clear DO (%d ~ %d) to 1 failed\n", start, start + count);
	return -1;
}

static int shell_cmd_clrdi(int argc, char *argv)
{
	int start;
	int count;
	int buf[CONFIG_DI_NUMBER];
	int limit = di_get_limit();

	if (argc > 3) {
		println("Usage: clrdi <start> <count>\n");
		return -1;
	}

	start = atoi(ARGV(1));
	count = (argc == 2) ? 1 : atoi(ARGV(2));
	CHECK_DIO_RANGE();
	for (int i = 0; i < count; i++) {
		buf[i] = 0;
	}
	if (di_set_buf(buf, start, count) == 0) {
		println("Set DI (%d ~ %d) to 1 success\n", start, start + count);
		return 0;
	}

	println("Set DI (%d ~ %d) to 1 failed\n", start, start + count);
	return -1;
}

static int shell_cmd_togdo(int argc, char *argv)
{
	int start;
	int count;
	int buf[CONFIG_DO_NUMBER];
	int limit = do_get_limit();

	if (argc > 3) {
		println("Usage: togdo <start> [count]\n");
	}

	start = atoi(ARGV(1));
	count = (argc == 2) ? 1 : atoi(ARGV(2));
	CHECK_DIO_RANGE();

	do_get(buf, start, count);
	for (int i = 0; i < count; i++) {
		if (buf[i] == 1) {
			buf[i] = 0;
		} else {
			buf[i] = 1;
		}
	}

	if (do_set_buf(buf, start, count) == 0) {
		println("Toggle DO (%d ~ %d) success\n", start, start + count);
		return 0;
	}

	println("Toggle DO (%d ~ %d) failed\n", start, start + count);
	return -1;
}

static int shell_cmd_togdi(int argc, char *argv)
{
	int start;
	int count;
	int buf[CONFIG_DI_NUMBER];
	int limit = di_get_limit();

	if (argc > 3) {
		println("Usage: togdi <start> [count]\n");
	}

	start = atoi(ARGV(1));
	count = (argc == 2) ? 1 : atoi(ARGV(2));
	CHECK_DIO_RANGE();

	di_get(buf, start, count);
	for (int i = 0; i < count; i++) {
		if (buf[i] == 1) {
			buf[i] = 0;
		} else {
			buf[i] = 1;
		}
	}

	if (di_set_buf(buf, start, count) == 0) {
		println("Toggle DI (%d ~ %d) success\n", start, start + count);
		return 0;
	}

	println("Toggle DI (%d ~ %d) failed\n", start, start + count);
	return -1;
}

static int shell_cmd_dbset(int argc, char *argv)
{
	if (argc != 3) {
		println("Usage: dbset <key> <value>\n");
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
	char buf[RDB_VAL_LEN] = {0};

	if (argc != 2) {
		println("Usage: dbset <key> <value>\n");
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
	yc_save_table(&yc_tbl);
	return 0;
}

static int shell_cmd_readyc(int argc, char *argv)
{
	float value;
	if (argc != 2) {
		println("Usage: dbset <key> <value>\n");
		return -1;
	}
	if (yc_read_single(&value, atoi(ARGV(1))) != 0) {
		println("Invalid\n");
		return -1;
	}
	println("YC %d : %f\n", atoi(ARGV(1)), value);
	return 0;
}

static int shell_cmd_lsyc(int argc, char *argv)
{
	println("----------------YC Status----------------\n");
	println("%24s%16s", "Key", "Status\n");
	rdb_ls_key("keys yc:*");
	return 0;
}

static int shell_cmd_yxset(int argc, char *argv)
{
	int ptid;

	if (argc == 2) {	// select with ptid
		ptid = atoi(ARGV(1));
	} else if (argc == 3) {
		ptid = (atoi(ARGV(1)) << 16) + atoi(ARGV(2));
	} else {
		println("Usage: \n");
		println("\tyxset ptid    - List YX with ptid\n");
		println("\tyxset fun inf - List YX with fun and inf\n\n");
		return -1;
	}

	println("Set YX(%d) to 1\n", ptid);
	return yx_save_by_id(1, ptid, NULL);
}

static int shell_cmd_lsyx(int argc, char *argv)
{
	struct yx_desc_t *desc;
	struct yx_desc_t *tmp;
	int cnt;
	char cmd[SQL_CMD_LEN + 1] = { 0 };

	if (argc == 2) {	// select with ptid
		snprintf(cmd, SQL_CMD_LEN, "select * from tbl_yx where ptid=%s", ARGV(1));
	} else if (argc == 3) {
		snprintf(cmd, SQL_CMD_LEN, "select * from tbl_yx where fun=%s and inf=%s", ARGV(1), ARGV(2));
	} else if (argc == 1) {
		snprintf(cmd, SQL_CMD_LEN, "select * from tbl_yx");
	} else {
		println("Usage: \n");
		println("\tlsyx         - List all YX \n");
		println("\tlsyx ptid    - List YX with ptid\n");
		println("\tlsyx fun inf - List YX with fun and inf\n\n");
		return -1;
	}

	println("--------------------------YX Status--------------------------\n");
	cnt = sdb_select_multi(cmd, &sdb_map_yx_desc, (void **)&desc, sizeof(struct yx_desc_t));
	if (cnt < 0) {
		dbg("Select failed\n");
		return -1;
	}

	tmp = desc;
	println("%-4s: %-6s %-6s %-6s %-6s %-24s %-32s %-32s\n",
		"seq", "ptid", "fun", "inf", "val", "time", "alias", "desc");
	for (int i = 0; i < cnt; i++, desc++) {
		println("%-4d: %-6d %-6d %-6d %-6d %-24s %-32s %-32s\n",
			i, desc->ptid, desc->fun, desc->inf, desc->value,
			desc->tm, desc->alias, desc->dname );
	}
	sdb_free(tmp);
	return 0;
}

static int shell_cmd_time(int argc, char *argv)
{
	struct time_stamp ts;
	char *day[] = { "星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六"};

	get_time_stamp(&ts);
	println("%04d-%02d-%02d %02d:%02d:%02d.%03d %s\n",
		ts.year, ts.month + 1, ts.date,
		ts.hour, ts.min, ts.sec, ts.msec, day[ts.day]);
	return 0;
}

#include "command.inc"