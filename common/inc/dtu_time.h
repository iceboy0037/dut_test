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
};

#define RTC_TIME_BUF_LEN	sizeof(struct time_stamp)

/**
 * @brief Get the time stamp object
 * @param  ts	Return time stamp
 * @return int 0 - success
 */
extern int get_time_stamp(struct time_stamp *ts);

#ifdef __cplusplus
}
#endif
#endif