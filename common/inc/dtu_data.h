/**
 * @file dtu_data.h
 * @brief
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2020-12-19
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-19 <td>1.0     <td>rock     <td>
 * </table>
 */
#ifndef __DTU_DATA_H__
#define __DTU_DATA_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 实时遥测存储结构
 */
struct yc_value_t {
	float	rating;		// 额定值
	float	raw;		// 原始值
	float	output;		// 原始值1次值
	int	q;		// 品质
};

/**
 * @brief 遥测点位描述结构体
 */
struct yc_desc_t {
	int	ptid;				// 点位ID号
	int	devid;				// 设备ID号
	int	fun;				// 功能号
	int	inf;				// 信息编号
	float	ratio;				// 系数
	char	type[TYPE_STR_LENGTH];		// 数据类型
	char	name[POINT_DESC_LENGTH];	// 描述字符串
	char	alias[POINT_DESC_LENGTH];	// 变量名字符串
};

/**
 * @brief 母线遥测数据，电压线
 */
struct yc_bus_t {
	struct yc_value_t ua;
	struct yc_value_t ub;
	struct yc_value_t uc;
	struct yc_value_t uab;
	struct yc_value_t ubc;
	struct yc_value_t u0;
	struct yc_value_t f;
};

/**
 * @brief 线路遥测数据结构定义，电流线
 */
struct yc_line_t {
	struct yc_value_t ia;
	struct yc_value_t ib;
	struct yc_value_t ic;
	struct yc_value_t i0;
	struct yc_value_t p;
	struct yc_value_t q;
	struct yc_value_t s;
	struct yc_value_t cos;
};

/**
 * @brief 母线保护遥测
 */
struct yc_relay_bus_t {
	struct yc_value_t ua;
	struct yc_value_t ub;
	struct yc_value_t uc;
	struct yc_value_t uab;
	struct yc_value_t ubc;
};

/**
 * @brief 线路保护遥测
 */
struct yc_relay_line_t {	// 线路保护遥测值
	float	ia1;		// 基波电流有效值
	float	ib1;
	float	ic1;
	float	ia2;		// 二次谐波有效值
	float	ib2;
	float	ic2;
};

struct yc_misc_t {						// 其它遥测值
	union rtc_tm {
		struct time_stamp rtc;				// 时间结构
		char buff[RTC_TIME_BUF_LEN];			// 时间对应时分秒数组
	} tm;
	int 	grid_freq;					// 电网频率
	float	dc0;						// 直流0
	float	dc1;						// 直流1
};

// 总遥测表结构
struct yc_table_t {
	struct yc_bus_t		bus[BUS_NUMBER_MAX];		// 母线电压遥测
	struct yc_line_t 	line[LINE_NUMBER_MAX];		// 线路遥测结构表
	struct yc_relay_bus_t	rbus[BUS_NUMBER_MAX]; 		// 保护遥测值
	struct yc_relay_line_t	rline[LINE_NUMBER_MAX];		// 保护线路遥测值
};

extern struct yc_table_t yc_tbl;				// 电气遥测表
extern struct yc_misc_t yc_misc;				// 系统其它遥测值
#ifdef __cplusplus
}
#endif
#endif