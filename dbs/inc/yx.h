/**
 * @file yx.h
 * @brief YX APIs
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2021-01-08
 * @copyright Copyright (c) 2020 - 2021 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-01-08 <td>1.0     <td>rock     <td>Create
 * </table>
 */
#ifndef __YX_H__
#define __YX_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 遥信点位描述结构，对应于数据库中的表结构
 */
struct yx_desc_t {
	int	devid;				// 设备ID号
	int	ptid;				// 点位ID号
	int	fun;				// 功能号
	int	inf;				// 信息编号
	char	dname[STR_LEN];			// 显示名，可中文
	char	alias[STR_LEN];			// 英文别名，也是编程中的变量名
	char	value;				// 遥信值都是0或1，统一定义为char
	char	resv[3];
	char	tm[TM_STR_LEN];			// 设置时间
	int	count;				// 计数
	char	tname[STR_LEN];			// 类别描述
	char	type[STR_LEN];			// 类别
	char	aname[STR_LEN];			// 属性描述
	char	attr[STR_LEN];			// 属性
};

/**
 * @brief Read YX desc structure single
 * @param  desc	Return value
 * @param  ptid	Point ID
 * @return int 0 - success
 */
extern int yx_read_desc_single(struct yx_desc_t *desc, int ptid);

/**
 * @brief Save a YX value by Point ID
 * @param  value YX value
 * @param  ptid	YX point ID
 * @param  ts YX time stamp, if not need, set it to NULL
 * @return int 0 - success
 */
extern int yx_save_by_id(int value, int ptid, struct time_stamp *ts);

/**
 * @brief Read YX value by value
 * @param  value Return value
 * @param  ptid	YX point id
 * @param  ts	YX time stamp, if not need, set it to NULL
 * @return int 0 - success
 */
extern int yx_read_single(char *value, int ptid, struct time_stamp *ts);

#ifdef __cplusplus
}
#endif
#endif