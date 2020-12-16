/**
 * @file relay_types.h
 * @brief relay related struct definition
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2020-12-16
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-16 <td>1.0     <td>rock     <td>Modify Content
 * </table>
 */
#ifndef __RELAY_TYPES_H__
#define __RELAY_TYPES_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "dtu.h"

/**
 * @brief 实时遥测项结构
 */
struct yc_item_t {
	float	rating;		// 额定值
	float	raw;		// 原始值
	float	output;		// 原始值1次值
	int	q;		// 品质
};

/**
 * @brief 母线遥测数据，电压线
 */
struct yc_bus_t {
	struct yc_item_t ua;
	struct yc_item_t ub;
	struct yc_item_t uc;
	struct yc_item_t uab;
	struct yc_item_t ubc;
	struct yc_item_t u0;
	struct yc_item_t f;
};

/**
 * @brief 线路遥测数据结构定义，电流线
 */
struct yc_line_t {	
	struct yc_item_t ia;
	struct yc_item_t ib;
	struct yc_item_t ic;
	struct yc_item_t i0;
	struct yc_item_t p;
	struct yc_item_t q;
	struct yc_item_t s;
	struct yc_item_t cos;
};

/**
 * @brief 母线保护遥测
 */
struct yc_relay_bus_t {
	struct yc_item_t ua;
	struct yc_item_t ub;
	struct yc_item_t uc;
	struct yc_item_t uab;
	struct yc_item_t ubc;
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

#ifdef __cplusplus
}
#endif
#endif
