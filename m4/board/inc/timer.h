/**
 * @file timer.h
 * @brief timer
 * @author jiashipeng (1060728573@qq.com)
 * @version 1.0
 * @date 2020-12-23
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-23 <td>1.0     <td>jiashipeng     <td>timer
 * </table>
 */
#ifndef __TIMER_H__
#define __TIMER_H__
extern void timer_init(void);
extern void timer_start(void);
extern void timer_stop(void);
extern void timer_set_irq_freq(unsigned int ms);
#endif