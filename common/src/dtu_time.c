/**
 * @file dtu_time.c
 * @brief DTU Time service
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2020-12-20
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-20 <td>1.0     <td>rock     <td>Create
 * </table>
 */

#include <time.h>
#include "dtu.h"

/**
 * @brief Get the time stamp object
 * @param  ts	Return time stamp
 * @return int 0 - success
 */
int get_time_stamp(struct time_stamp *ts)
{
	struct timeval tv;
	struct tm *p;

	gettimeofday(&tv, NULL);
	p = localtime(&tv.tv_sec);
	ts->year 	= p->tm_year + 1900;
	ts->month 	= p->tm_mon;
	ts->date 	= p->tm_mday;
	ts->day		= p->tm_wday;
	ts->hour	= p->tm_hour;
	ts->min		= p->tm_min;
	ts->sec		= p->tm_sec;
	ts->msec	= tv.tv_usec / 1000;
	ts->isdst	= p->tm_isdst;

	return 0;
}
