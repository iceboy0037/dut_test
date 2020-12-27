/**
 * @file yc.h
 * @brief
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2020-12-21
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-21 <td>1.0     <td>rock     <td>
 * </table>
 */

#ifndef __YC_H__
#define __YC_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "dtu.h"

/**
 * @brief Save YC table to RT DB
 * @param entry YC table entry
 * $param name
 * @return int
 */
extern int yc_save_table(struct yc_table_t *base);

/**
 * @brief Read YC by ID
 * @param  value Return value
 * @param  id	YC ID
 * @return int 0 - success
 */
extern int yc_read_single(void *value, int id);

#ifdef __cplusplus
}
#endif
#endif