/**
 * @file dtu_param.h
 * @brief DTU param definition
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2020-12-19
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-19 <td>1.0     <td>rock     <td>Create
 * </table>
 */
#ifndef __DTU_PARAM_H__
#define __DTU_PARAM_H__
#ifdef __cplusplus
extern "C" {
#endif

// 电流线路配置表
struct line_config_t {
	char name[NAME_LENGTH];				// 线路名称
	int  enable;
	int  id;					// id号，所有线路独立编号
	int  ia_index;					// 四线电流所在的采样点位
	int  ib_index;
	int  ic_index;
	int  iz_index;
};

struct bus_config_t {
	char name[NAME_LENGTH];				// 母线名称
	int  enable;					// 是否使能，非使能时，将不参与计算
	int  line_count;				// 当前母线包涵多少条电流线
	int  id;					// id号所有母线独立编号，对应于系统
	int  mode;					// 两表法，三表法接法
	int  ua_index;					// 当前电压线四个电压所在的采样点位
	int  ub_index;
	int  uc_index;
	int  uz_index;
	struct line_config_t line[LINE_NUMBER_MAX];	// 电流线配置表单
};

extern struct bus_config_t bus_array[BUS_NUMBER_MAX];
#ifdef __cplusplus
}
#endif
#endif