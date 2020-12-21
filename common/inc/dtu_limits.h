/**
 * @file dtu_limits.h
 * @brief some common limits declaration
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2020-12-16
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-16 <td>1.0     <td>rock     <td>
 * </table>
 */

#ifndef	__DTU_LIMITS_H__
#define	__DTU_LIMITS_H__
#ifdef __cplusplus
extern "C" {
#endif


#define	BUS_NUMBER_MAX		(4)	// 最大母线数量
#define LINE_NUMBER_MAX 	(16)	// 最大线路数量

#define	MAX_TRAN_AI		256	// 遥测参数
#define MAX_TRAN_DI		256	// 遥信参数
#define	MAX_TRAN_DO		256	// 遥控参数
#define MAX_TRAN_DD		256	// 电度参数

#define POINT_DESC_LEN		32	// 点位描述字符串长度

#ifdef __cplusplus
}
#endif
#endif