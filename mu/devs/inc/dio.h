/**
 * @file dio.h
 * @brief DIO hardware interface
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
#ifndef __DIO_H__
#define __DIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef SIMULATOR
#include <hiredis/hiredis.h>
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

extern int sim_devs_init(void);
extern int sim_do_init(void);
extern int sim_di_init(void);
extern int sim_do_set(int *buf, int start, int count);
extern int sim_do_get(int *buf, int start, int count);
extern int sim_di_set(int *buf, int start, int count);
extern int sim_di_get(int *buf, int start, int count);
#else
extern int devs_dio_init(unsigned int addr_base);
extern int devs_dio_deinit(void);
extern int devs_di_get(int *buf, int start, int count);
extern int devs_do_set(int start, int count);
extern int devs_do_clean(int start, int count);
extern int devs_dio_dbg(void);
#endif

#ifdef __cplusplus
}
#endif
#endif
