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

#define PRINT_HEX	0
#define PRINT_DEC 	1

/**
 * @brief Printf float array
 * @param  buf memory buffer entry
 * @param  len size in floats
 * @return int
 */
extern int print_float(float *buf, int len);

/**
 * @brief Print memory buffer
 * @param  buf	memory buffer entry
 * @param  len	size in ints
 * @param  type	PRINT_DEC or PRINT_HEX
 * @return int 0 - success
 */
extern int print_int32(int *buf, int len, int type);

/**
 * @brief Print memory buffer
 * @param  buf	memory buffer entry
 * @param  len	size in short
 * @param  type	PRINT_DEC or PRINT_HEX
 * @return int 0 - success
 */
extern int print_int16(short *buf, int len, int type);

/**
 * @brief Print memory buffer
 * @param  buf	memory buffer entry
 * @param  len	size in bytes
 * @param  type	PRINT_DEC or PRINT_HEX
 * @return int 0 - success
 */
extern int print_buf(char *buf, int len, int type);

#ifdef __cplusplus
}
#endif
#endif