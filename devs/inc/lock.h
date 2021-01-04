/**
 * @file lock.h
 * @brief mutex lock
 * @author jiashipeng (1060728573@qq.com)
 * @version 1.0
 * @date 2020-12-16
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-16 <td>1.0     <td>jiashipeng     <td>mutex lock
 * </table>
 */
#ifndef __LOCK_H__
#define __LOCK_H__

#if !defined SIMULATOR && defined M4FIRMWARE
/**
 * @brief mutex lock share memory addr init
 * @return int
 * 		0 success
 * 		-1 error
 */
extern int mem_mutex_init(void);

/**
 * @brief mutex lock share memory addr deinit
 * @return int
 * 		0 success
 * 		-1 error
 */
extern int mem_mutex_deinit(void);

/**
 * @brief mutex lock
 * @return int
 * 		0 success
 * 		-1 error
 */
extern int mem_mutex_lock(void);

/**
 * @brief mutex unlock
 * @return int
 * 		0 success
 * 		-1 error
 */
extern int mem_mutex_unlock(void);
#endif
#endif // !__LOCK_H__