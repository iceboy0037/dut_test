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

/**
 * @brief Fomat time stamp to string format
 * @param  ts	Time stamp struct
 * @param  str	Return time string in YYYY-MM-DD HH:MM:SS.SSS
 * @return int 0 - success
 */
int stamp_to_string(struct time_stamp *ts, char *str)
{
	snprintf(str, TIME_STRING_LEN, "%04d-%02d-%02d %02d:%02d:%02d.%03d",
		ts->year, ts->month + 1, ts->date,
		ts->hour, ts->min, ts->sec, ts->msec);
	return 0;
}

/**
 * @brief Convert string to time stamp struct
 * @param  ts	Time stamp struct
 * @param  str	Return time string in YYYY-MM-DD HH:MM:SS.SSS
 * @return int  0 - success
 */
int string_to_stamp(struct time_stamp *ts, char *str)
{
	char buf[TIME_STRING_LEN + 1] = { 0 };

	// "1970-01-01 00:00:00.000"
	if (strlen(str) != TIME_STRING_LEN) {
		dbg("Invalid time string format\n");
		return -1;
	}

	strcpy(buf, str);
	buf[4]  = '\0';
	buf[7]  = '\0';
	buf[10] = '\0';
	buf[13] = '\0';
	buf[16] = '\0';
	buf[19] = '\0';

	ts->year  = atoi(&buf[0]);
	ts->month = atoi(&buf[5]);
	ts->date  = atoi(&buf[8]);
	ts->hour  = atoi(&buf[11]);
	ts->min   = atoi(&buf[14]);
	ts->sec   = atoi(&buf[17]);
	ts->msec  = atoi(&buf[20]);

	/// TODO: Calc day and dst mode

	return 0;
}
