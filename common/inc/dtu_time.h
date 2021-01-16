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
	int	year;	// ���
	int	month;	// �·ݣ���һ�¿�ʼ��0����һ�£� - ȡֵ����Ϊ[0, 11]
	int	date;	// һ�����е����� - ȡֵ����Ϊ[1,31]
	int	day;	// ���ڼ��� 0��ʼ��0����������
	int	hour;	// ʱ 	- ȡֵ����Ϊ[0, 23]
	int	min;	// �� 	- ȡֵ����Ϊ[0, 59]
	int	sec;	// �� 	�C ȡֵ����Ϊ[0, 59]
	int	msec;	// ����  - ȡֵ����Ϊ[0, 999]
	int	isdst;	// ����ʱ��ʶ����ʵ������ʱ��ʱ��Ϊ������ʵ������ʱ��ʱ��Ϊ0
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