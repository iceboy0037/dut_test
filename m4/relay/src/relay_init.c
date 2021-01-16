/**
 * @file relay_init.c
 * @brief
 * @author liuyixi (liuyixinuaa@163.com)
 * @version 1.0
 * @date 2021-01-14
 * @copyright Copyright (c) 2020 - 2021 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-01-14 <td>1.0     <td>liuyixi     <td>初始化文件
 * </table>
 */
#include "relay_yc.h"
#include "relay_fft.h"

/**
 * @brief 计算过程中用到的数据进行初始化
 */
void init_yc(void)
{
	short i;

	for (i = 0; i < CONFIG_ADC_CHANNEL_NUMBER; i++) {
		yc_adc_result[i] = 0.0;
		harm1.fft_in[i]  = 0.0;
		harm1.axsum[i]   = 0.0;
		harm1.aysum[i]   = 0.0;
		harm1.result[i]  = 0.0;
		harm2.fft_in[i]  = 0.0;
		harm2.axsum[i]   = 0.0;
		harm2.aysum[i]   = 0.0;
		harm2.result[i]  = 0.0;
	}

	bus_array[0].mode = 0;
	bus_array[1].mode = 0;
	bus_array[2].mode = 0;
	bus_array[3].mode = 0;
	bus_array[0].ua_index = 0;
	bus_array[0].ub_index = 1;
	bus_array[0].uc_index = 2;
	bus_array[0].line[0].ia_index = 3;
	bus_array[0].line[0].ib_index = 4;
	bus_array[0].line[0].ic_index = 5;
	bus_array[0].line[1].ia_index = 6;
	bus_array[0].line[1].ib_index = 7;
	bus_array[0].line[1].ic_index = 8;
	bus_array[0].line[2].ia_index = 9;
	bus_array[0].line[2].ib_index = 10;
	bus_array[0].line[2].ic_index = 11;
	bus_array[1].ua_index = 12;
	bus_array[1].ub_index = 13;
	bus_array[1].uc_index = 14;
	bus_array[1].line[0].ia_index = 15;
	bus_array[1].line[0].ib_index = 16;
	bus_array[1].line[0].ic_index = 17;
	bus_array[1].line[1].ia_index = 18;
	bus_array[1].line[1].ib_index = 19;
	bus_array[1].line[1].ic_index = 20;
	bus_array[0].line[2].ia_index = 21;
	bus_array[0].line[2].ib_index = 22;
	bus_array[0].line[2].ic_index = 23;
	bus_array[0].line_count = 3;
	bus_array[1].line_count = 3;
}

/**
 * @brief  				矩阵转置
 * @param  des				转置后矩阵
 * @param  src				转置前输入
 * @param  row_len			行数
 * @param  col_len			列数
 */
void reverse_array(short *des, short *src, short row_len, short col_len)
{
	short i, j;

	for (i = 0; i < row_len; i++) {
		for (j = 0; j < col_len; j++) {
			*(des + i * col_len + j) = *(src + j * row_len + i);
		}
	}
}