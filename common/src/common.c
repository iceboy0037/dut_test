/**
 * @file common.c
 * @brief Some common functions
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2020-12-16
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-16 <td>1.0     <td>rock     <td>
 * </table>
 */
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

/**
 * @brief Printf float array
 * @param  buf memory buffer entry
 * @param  len size in floats
 * @return int
 */
int print_float(float *buf, int len)
{
	int i;

	printf("      ");
	for (i = 0; i < 8; i++) {
		printf("%16d", i);
	}

	printf("\n%4d: ", 0);
	for (i = 0; i < len; i++) {
		if ((i % 8) == 0 && i > 0) {
			printf("\n%4d: ", i);
		}
		printf("%16.6f", buf[i]);
	}
	printf("\n\n");

	return 0;
}

/**
 * @brief Print memory buffer
 * @param  buf	memory buffer entry
 * @param  len	size in ints
 * @param  type	PRINT_DEC or PRINT_HEX
 * @return int 0 - success
 */
int print_int32(int *buf, int len, int type)
{
	int i;

	printf("      ");
	for (i = 0; i < 8; i++) {
		printf("%16d", i);
	}

	printf("\n%4d: ", 0);
	for (i = 0; i < len; i++) {
		if ((i % 8) == 0 && i > 0) {
			printf("\n%4d: ", i);
		}

		if (type == PRINT_DEC) {
			printf("%16d", buf[i] & 0xffffffff);
		} else {
			printf("%16x", buf[i] & 0xffffffff);
		}
	}

	printf("\n\n");
	return 0;
}

/**
 * @brief Print memory buffer
 * @param  buf	memory buffer entry
 * @param  len	size in short
 * @param  type	PRINT_DEC or PRINT_HEX
 * @return int 0 - success
 */
int print_int16(short *buf, int len, int type)
{
	int i;

	printf("      ");
	for (i = 0; i < 8; i++) {
		printf("%16d", i);
	}

	printf("\n%4d: ", 0);
	for (i = 0; i < len; i++) {
		if ((i % 8) == 0 && i > 0) {
			printf("\n%4d: ", i);
		}

		if (type == PRINT_DEC) {
			printf("%16d", buf[i]);
		} else {
			printf("%16x", buf[i]);
		}
	}
	printf("\n\n");

	return 0;
}

/**
 * @brief Print memory buffer
 * @param  buf	memory buffer entry
 * @param  len	size in bytes
 * @param  type	PRINT_DEC or PRINT_HEX
 * @return int 0 - success
 */
int print_buf(char *buf, int len, int type)
{
	int i;

	printf("      ");
	for (i = 0; i < 8; i++) {
		printf("%16d", i);
	}
	printf("\n%4d: ", 0);

	for (i = 0; i < len; i++) {
		if ((i % 8) == 0 && i > 0) {
			printf("\n%4d: ", i);
		}

		if (type == PRINT_DEC) {
    			printf("%16d", buf[i]);
		} else {
    			printf("%16x", buf[i]);
		}
	}
	printf("\n\n");

	return 0;
}