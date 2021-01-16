/**
 * @file fft.c
 * @brief
 * @author liuyixi (liuyixinuaa@163.com)
 * @version 1.0
 * @date 2021-01-14
 * @copyright Copyright (c) 2020 - 2021 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-01-14 <td>1.0     <td>liuyixi     <td>fft 计算
 * </table>
 */

#include "relay_fft.h"
#include "sin_cos_tbl.h"

static short fft_cnt = 0;
/**
 * @brief               计算基波分量，输出为峰值的平方
 * @param  p	        指向结构体的指针,fft输入数据
 * @param  channel_num	需要进行fft的通道数量
 */
void  fft_cal_harm1(struct harm *p, short channel_num)
{
	float tempx = 0.0, tempy = 0.0, temp = 0.0;
	short i;

	for (fft_cnt = 0; fft_cnt < FFT_POINT; fft_cnt++) {
		for (i = 0; i < channel_num; i++) {
			p->fft_in[i] = fft_buf[i][fft_cnt];//fft输入赋值
			p->axsum[i]  += p->fft_in[i] * cos_table_1_fft[fft_cnt];
			p->aysum[i]  += p->fft_in[i] * sin_table_1_fft[fft_cnt];
		}
	}

	if (fft_cnt == FFT_POINT) {
		fft_cnt = 0;

		for (i = 0; i < channel_num; i++) {
			p->ax[i] = HF_COFFICIENT * p->axsum[i];
			p->ay[i] = HF_COFFICIENT * p->aysum[i];
			tempx = p->ax[i]  * p->ax[i] ;
			tempy = p->ay[i]  * p->ay[i] ;
			temp = tempx + tempy;
			p->result[i] = temp;
			p->axsum[i] = 0.0;
			p->aysum[i] = 0.0;
		}
	}
}

/**
 * @brief               计算二次谐波分量，输出为峰值的平方
 * @param  p	        指向结构体的指针,fft输入数据
 * @param  channel_num	需要进行fft的通道数量
 */
void  fft_cal_harm2(struct harm *p, short channel_num)
{
	float tempx = 0.0, tempy = 0.0, temp = 0.0;
	short i;

	for (fft_cnt = 0; fft_cnt < FFT_POINT; fft_cnt++) {
		for (i = 0; i < channel_num; i++) {
			p->fft_in[i] = fft_buf[i][fft_cnt];//fft输入赋值
			p->axsum[i]  += p->fft_in[i] * cos_table_2_fft[fft_cnt];
			p->aysum[i]  += p->fft_in[i] * sin_table_2_fft[fft_cnt];
		}
	}

	if (fft_cnt == FFT_POINT) {
		fft_cnt = 0;

		for (i = 0; i < channel_num; i++) {
			p->ax[i] = HF_COFFICIENT * p->axsum[i];
			p->ay[i] = HF_COFFICIENT * p->aysum[i];
			tempx = p->ax[i]  * p->ax[i] ;
			tempy = p->ay[i]  * p->ay[i] ;
			temp = tempx + tempy;
			p->result[i] = temp;
			p->axsum[i] = 0.0;
			p->aysum[i] = 0.0;
		}
	}
}
