/**
 * @file common.h
 * @brief Some common definition
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2020-12-16
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-16 <td>1.0     <td>rock     <td>Create
 * </table>
 */
#ifndef __COMMON_H__
#define __COMMON_H__
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Init watchdog
 * @return int 0 - success
 */
int init_dog(void);

/**
 * @brief kick watchdog
 * @return int 0 - success
 */
int kick_dog(void);

/**
 * @brief Disable watchdog
 * @return int 0 - success
 */
int disable_dog(void);

/**
 * @brief Enable watchdog
 * @return int 0 - success
 */
int enable_dog(void);

#ifdef __cplusplus
}
#endif
#endif