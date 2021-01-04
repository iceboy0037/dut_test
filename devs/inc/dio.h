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

#define	CHECK_DIO_RANGE()	do { \
		if ((start > limit) || (start + count > limit)) { \
			dbg("Out of range : 0 ~ %d\n", limit);\
			return FAIL; \
		} \
	} while (0)

/**
 * @brief Get system DI Channel number
 */
#define	di_get_limit()		(CONFIG_DI_NUMBER)

/**
 * @brief Get System DO Channel number
 */
#define	do_get_limit()		(CONFIG_DO_NUMBER)

/**
 * @brief Init DIO system
 * @param  base	DIO buffer base address
 * @return int 0 - success
 */
extern int dio_init(void);

/**
 * @brief De-Init DIO system
 * @return int 0 - success
 */
extern int dio_deinit(void);

/**
 * @brief Get DI status from DI boards
 * @param  buf DI status return buffer
 * @param  start DI start index
 * @param  count DI Count that wanted
 * @return int 0 - success
 */
extern int di_get(int *buf, int start, int count);

/**
 * @brief Set DI value, Only valid in simulator environment
 * @param  buf	DI buffer value
 * @param  start Start index
 * @param  count DI Count
 * @return int 0 - success
 */
extern int di_set_buf(int *buf, int start, int count);

/**
 * @brief Set DO value
 * @param  buf	DO buffer value
 * @param  start Start index
 * @param  count DO Count
 * @return int 0 - success
 */
extern int do_set_buf(int *buf, int start, int count);

/**
 * @brief Set DO status
 * @param  buf DO status return buffer
 * @param  start DO start index
 * @param  count DO Count that wanted
 * @return int 0 - success
 */
extern int do_set(int start, int count);

/**
 * @brief Get DO status from DO buffer
 * @param  buf DO status return buffer
 * @param  start DO start index
 * @param  count DO Count that wanted
 * @return int 0 - success
 */
extern int do_get(int *buf, int start, int count);

extern int do_clr(int start, int count);
extern int dio_dbg(void);


/**
 * @brief set DO channel to 1 or 0
 * @param  index            DO channel index
 * @param  value            1 or 0
 * @return int 0 - success
 */
extern int do_set_value(int index, int value);

#ifndef SIMULATOR
extern int hw_dio_init(unsigned int addr_base);
#endif
#ifdef __cplusplus
}
#endif
#endif
