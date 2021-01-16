/**
 * @file pwr.h
 * @brief power board
 * @author jiashipeng (1060728573@qq.com)
 * @version 1.0
 * @date 2021-01-05
 * @copyright Copyright (c) 2020 - 2021 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-01-05 <td>1.0     <td>jiashipeng     <td>power board
 * </table>
 */

#if !defined SIMULATOR

#define PWR_ACTIVATION_LIMIT 2
extern int pwr_qdj_set(int value);
extern int pwr_activation_set(int index, int value);
#endif