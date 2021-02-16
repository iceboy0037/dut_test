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

#define BUS_NUMBER_MAX		(4)			// 最大母线数量
#define LINE_NUMBER_MAX 	(16)			// 最大线路数量

#define MAX_TRAN_AI		2560			// 遥测参数
#define MAX_TRAN_DI		2560			// 遥信参数
#define MAX_TRAN_DO		2560			// 遥控参数
#define MAX_TRAN_DD		2560			// 电度参数

#define TM_STR_LEN		24			// 时间字符串长度 "1970-01-01 00:00:00.000"
#define STR_LEN			64			// 常用字符串长度定义
#define SQL_CMD_LEN		128			// SQL 查询命令长度
#define TYPE_STR_LENGTH		16			// 数据类型字符串长度
#define POINT_DESC_LENGTH	32			// 点位描述字符串长度
#define DTU_YC_LIST_MAX		256			// 本机遥测点位最大数量
#define POINT_UNUSED		"UNUSED"
#define NAME_LENGTH		32			// 常用名称字符串长度
#define VALUE_LENGTH		32			// 变量值字符串长度
#define UNIT_LENGTH		16			// 单位字符串长度

#ifdef __cplusplus
}
#endif
#endif