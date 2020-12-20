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

#pragma pack(1)
struct rtc_time {
	char	year;
	char	mon;
	char	day;
	char	date;
	char 	hour;
	char	min;
	char	sec;
};
#define RTC_TIME_BUF_LEN	7

#ifdef __cplusplus
}
#endif
#endif