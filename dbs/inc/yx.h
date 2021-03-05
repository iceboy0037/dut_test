/**
 * @file yx.h
 * @brief YX APIs
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2021-01-08
 * @copyright Copyright (c) 2020 - 2021 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-01-08 <td>1.0     <td>rock     <td>Create
 * </table>
 */
#ifndef __YX_H__
#define __YX_H__

#include "tables.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Read YX desc structure single
 * @param  desc	Return value
 * @param  ptid	Point ID
 * @return int 0 - success
 */
extern int yx_read_desc_single(struct tbl_yx_t *desc, int ptid);

/**
 * @brief Save a YX value by Point ID
 * @param  value YX value
 * @param  ptid	YX point ID
 * @param  ts YX time stamp, if not need, set it to NULL
 * @return int 0 - success
 */
extern int yx_save_by_id(int value, int ptid, struct time_stamp *ts);

/**
 * @brief Read YX value by value
 * @param  value Return value
 * @param  ptid	YX point id
 * @param  ts	YX time stamp, if not need, set it to NULL
 * @return int 0 - success
 */
extern int yx_read_single(char *value, int ptid, struct time_stamp *ts);

#ifdef __cplusplus
}
#endif
#endif