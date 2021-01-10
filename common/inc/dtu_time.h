/**
 * @file dtu_time.h
 * @brief DTU Time service
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2020-12-20
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-20 <td>1.0     <td>rock     <td>Create
 * <tr><td>2021-12-20 <td>1.0     <td>rock     <td>Add Time convert APIs
 * </table>
 */
#ifndef __DTU_TIME_H__
#define __DTU_TIME_H__

#ifdef __cplusplus
extern "C" {
#endif

#if (defined A9APP) || (defined SIMULATOR)
#include <sys/time.h>
#endif

struct time_stamp {
	int	year;	// 年份
	int	month;	// 月份（从一月开始，0代表一月） - 取值区间为[0, 11]
	int	date;	// 一个月中的日期 - 取值区间为[1,31]
	int	day;	// 星期几， 0开始，0代表星期天
	int	hour;	// 时 	- 取值区间为[0, 23]
	int	min;	// 分 	- 取值区间为[0, 59]
	int	sec;	// 秒 	– 取值区间为[0, 59]
	int	msec;	// 毫秒  - 取值区间为[0, 999]
	int	isdst;	// 夏令时标识符，实行夏令时的时候，为正。不实行夏令时的进候，为0
};

#define RTC_TIME_BUF_LEN	sizeof(struct time_stamp)
#define TIME_STRING_LEN		(24 + 1)	// strlen("1970-01-01 00:00:00.000")

/**
 * @brief Get the time stamp object
 * @param  ts	Return time stamp
 * @return int 0 - success
 */
extern int get_time_stamp(struct time_stamp *ts);

/**
 * @brief Fomat time stamp to string format
 * @param  ts	Time stamp struct
 * @param  str	Return time string in YYYY-MM-DD HH:MM:SS.SSS
 * @return int 0 - success
 */
extern int stamp_to_string(struct time_stamp *ts, char *str);

/**
 * @brief Convert string to time stamp struct
 * @param  ts	Time stamp struct
 * @param  str	Return time string in YYYY-MM-DD HH:MM:SS.SSS
 * @return int  0 - success
 */
int string_to_stamp(struct time_stamp *ts, char *str);

#ifdef __cplusplus
}
#endif
#endif