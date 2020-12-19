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
 * <tr><td>2020-12-19 <td>1.0     <td>rock     <td>Modify Content
 * </table>
 */
#ifndef __DTU_DATA_H__
#define __DTU_DATA_H__
#ifdef __cplusplus
extern "C" {
#endif

enum yc_id {
	ua1 	= 0x01,
	ub1,
	uc1,
	uab1,
	ubc1,
	uz1,
	f1,

	ua2 	= 0x11,
	ub2,
	uc2,
	uab2,
	ubc2,
	uz2,
	f2,

	ia1 	= 0x21,
	ib1,
	ic1,
	iz1,
	p1,
	q1,
	s1,
	cos1,

	ia2 	= 0x31,
	ib2,
	ic2,
	iz2,
	p2,
	q2,
	s2,
	cos2,
};

/**
 * @brief 实时遥测项结构
 */
struct yc_item_t {
	float	rating;		// 额定值
	float	raw;		// 原始值
	float	output;		// 原始值1次值
	int	q;		// 品质
};

#ifdef __cplusplus
}
#endif
#endif