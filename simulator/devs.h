/**
 * @file devs.h
 * @brief Device simulator interface
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2020-12-13
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-13 <td>1.0     <td>rock     <td>Modify Content
 * </table>
 */
#ifndef __DEVS_H__
#define __DEVS_H__

struct sim_do_t {
	int count;
	int *buf;
};

struct sim_di_t {
	int count;
	int *buf;
};

struct sim_dc_t {
	int count;
	int *buf;
};

extern struct sim_do_t sim_do;
extern struct sim_di_t sim_di;
extern struct sim_di_t sim_pwr_di;
int sim_do_set(int *buf, int start, int count);
int sim_di_get(int *buf, int start, int count);

#endif