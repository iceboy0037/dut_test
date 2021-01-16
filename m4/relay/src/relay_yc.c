/**
 * @file relay_yc.c
 * @brief
 * @author liuyixi (liuyixinuaa@163.com)
 * @version 1.0
 * @date 2021-01-14
 * @copyright Copyright (c) 2020 - 2021 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-01-14 <td>1.0     <td>liuyixi     <td>遥测文件
 * </table>
 */
#include "adc.h"
#include "stdio.h"
#include "dtu.h"

#include "relay_yc.h"
#include "relay_fft.h"
//#include "sin_table1_96.h"
//#include "cos_table1_96.h"
#include "sin_cos_tbl.h"

/**
 * @brief 		用于计算线电压，buf1-buf2
 * @param  buf1		输入相采样数据
 * @param  buf2		输入相采样数据
 * @param  len		采样数据点数.
 * @return float 	返回有效值
 */
float calc_diff_rms(float *buf1, float *buf2, short len)
{
	short	i;
	float	datatemp = 0.0;
	float	sum = 0.0;
	float	coff = 0.0;
	coff = 1.0 / len;

	for (i = 0; i < len; i++) {
		datatemp = (*(buf1 + i)) - (*(buf2 + i));
		sum += datatemp * datatemp;
	}

	sum = sum * coff;
	sum = sqrt(sum);
	return (sum);
}

/**
 * @brief  		计算零序有效值
 *
 * @param buf1		输入相采样数据
 * @param buf2		输入相采样数据
 * @param buf3		输入相采样数据
 * @param len		采样数据点数.
 * @return float	返回有效值
 */
float calc_zero_rms(float *buf1, float *buf2, float *buf3, short len)
{
	short i;
	float datatemp = 0.0;
	float sum = 0.0;
	float coff = 0.0;
	coff = 1.0 / len;

	for (i = 0; i < len; i++) {
		datatemp = (*(buf1 + i)) + (*(buf2 + i)) + (*(buf3 + i));
		sum += datatemp * datatemp;
	}

	sum = sum * coff;
	sum = sqrt(sum);
	return (sum);
}

/**
 * @brief 		非三表法下计算线电压
 * @param  buf1		输入一路线电压
 * @param  buf2		输入第二路线电压
 * @param  len		采样数据点数
 * @return float 	第三路线电压有效值计算结果
 */
float cal_line(float *buf1, float *buf2, short len)
{
	short i;
	float datatemp = 0.0;
	float sum = 0.0;
	float coff = 0.0;
	coff = 1.0 / len;

	for (i = 0; i < len; i++) {
		datatemp = -((*(buf1 + i)) + (*(buf2 + i)));
		sum += datatemp * datatemp;
	}

	sum = sum * coff;
	sum = sqrt(sum);
	return (sum);
}
/**
 * @brief 		cal rms
 * @param  buf		input
 * @param  len		sample point
 * @return float    	return rms
 */
float calc_rms(float *buf, short len)
{
	short i;
	float datatemp = 0.0;
	float  sum = 0.0;
	float coff = 0.0;
	coff = 1.0 / len;

	for (i = 0; i < len; i++) {
		datatemp = *(buf + i);
		sum  += datatemp * datatemp;
	}

	sum = sum * coff;
	sum = sqrt(sum);
	return (sum);
}
/**
 * @brief
 *
 * @param buf
 * @param len
 * @return float
 */

/**
 * @brief		cal real value
 * @param  buf		input
 * @param  len		sample points
 * @return float 	return real value
 */
float real_cal(float *buf, short len)
{
	short i;
	float sum_real = 0.0 ;
	float real = 0.0;

	for (i = 0; i < len ; i++) {
		sum_real  += buf[i] * cos_table_1_yc[i];
	}

	real = sum_real * HF_COFFICIENT_YC;
	return (real);
}

/**
 * @brief 		cal imag value
 * @param  buf		input
 * @param  len		sample points
 * @return float	return imag value
 */
float imag_cal(float *buf, short len)
{
	short i;
	float sum_imag = 0.0 ;
	float imag = 0.0;

	for (i = 0; i < len ; i++) {
		sum_imag  += buf[i] * sin_table_1_yc[i];
	}

	imag = sum_imag * HF_COFFICIENT_YC;
	return (imag);
}

/**
 * @brief
 * mode0：三表法，其余接线方式按配置
 *
 * @param config
 * @param bus_num
 * @param len
 */

/**
 * @brief 		cal pqs
 * @param  config	配置
 * @param  bus_num	母线数量.
 * @param  len		采样数据点数.
 */
void cal_pqs_mode0(struct bus_config_t *config, short bus_num, short len)
{
	short i, j;
	static float datatemp;
	static float real1, real2, imag1, imag2;
	static float cosa, cosb, cosc, sina, sinb, sinc;
	static float angel_diff1, angel_diff2, angel_diff;
	static float pa, pb, pc, qa, qb, qc, p_gl, q_gl, s_gl;

	for (i = 0; i < bus_num; i++) {
		if(config[i].mode == 0){
			for (j = 0; j < config[i].line_count; j++) {
				real1 = real_cal(yc_adc_getbuf[config[i].ua_index], len);
				imag1 = imag_cal(yc_adc_getbuf[config[i].ua_index], len);
				real2 = real_cal(yc_adc_getbuf[config[i].line[j].ia_index], len);
				imag2 = imag_cal(yc_adc_getbuf[config[i].line[j].ia_index], len);
				angel_diff1 = atan2(imag1, real1);
				angel_diff2 = atan2(imag2, real2);
				angel_diff  = angel_diff2 - angel_diff1;
				cosa = cos(angel_diff);
				sina = sin(angel_diff);
				pa = yc_tbl.bus[i].ua.raw * yc_tbl.line[j].ia.raw * cosa;
				qa = yc_tbl.bus[i].ua.raw * yc_tbl.line[j].ia.raw * sina;
				real1 = real_cal(yc_adc_getbuf[config[i].ub_index], len);
				real2 = real_cal(yc_adc_getbuf[config[i].line[j].ib_index], len);
				imag1 = imag_cal(yc_adc_getbuf[config[i].ub_index], len);
				imag2 = imag_cal(yc_adc_getbuf[config[i].line[j].ib_index], len);
				angel_diff1 = atan2(imag1, real1);
				angel_diff2 = atan2(imag2, real2);
				angel_diff  = angel_diff2 - angel_diff1;
				cosb = cos(angel_diff);
				sinb = sin(angel_diff);
				pb = yc_tbl.bus[i].ub.raw * yc_tbl.line[j].ib.raw * cosb;
				qb = yc_tbl.bus[i].ub.raw * yc_tbl.line[j].ib.raw * sinb;
				real1 = real_cal(yc_adc_getbuf[config[i].uc_index], len);
				real2 = real_cal(yc_adc_getbuf[config[i].line[j].ic_index], len);
				imag1 = imag_cal(yc_adc_getbuf[config[i].uc_index], len);
				imag2 = imag_cal(yc_adc_getbuf[config[i].line[j].ic_index], len);
				angel_diff1 = atan2(imag1, real1);
				angel_diff2 = atan2(imag2, real2);
				angel_diff  = angel_diff2 - angel_diff1;
				cosc = cos(angel_diff);
				sinc = sin(angel_diff);
				pc = yc_tbl.bus[i].uc.raw * yc_tbl.line[j].ic.raw * cosc;
				qc = yc_tbl.bus[i].uc.raw * yc_tbl.line[j].ic.raw * sinc;
				p_gl = pa + pb + pc;
				q_gl = qa + qb + qc;
				datatemp = p_gl * p_gl + q_gl * q_gl;
				s_gl = sqrt(datatemp);
				yc_tbl.line[i * config[i].line_count + j].p.raw = p_gl;
				yc_tbl.line[i * config[i].line_count + j].q.raw = q_gl;
				yc_tbl.line[i * config[i].line_count + j].s.raw = s_gl;
				yc_tbl.line[i * config[i].line_count + j].cos.raw = (p_gl / s_gl);
			}
		}
		else
		{
			for (j = 0; j < config[i].line_count; j++) {
				real1 = real_cal(yc_adc_getbuf[config[i].ua_index], len);
				imag1 = imag_cal(yc_adc_getbuf[config[i].ua_index], len);
				real2 = real_cal(yc_adc_getbuf[config[i].line[j].ia_index], len);
				imag2 = imag_cal(yc_adc_getbuf[config[i].line[j].ia_index], len);//计算
				angel_diff1 = atan2(imag1, real1);
				angel_diff2 = atan2(imag2, real2);
				angel_diff  = angel_diff2 - angel_diff1;
				cosa = cos(angel_diff);
				sina = sin(angel_diff);
				pa = yc_tbl.bus[i].ua.raw * yc_tbl.line[j].ia.raw * cosa;
				qa = yc_tbl.bus[i].ua.raw * yc_tbl.line[j].ia.raw * sina;
				real1 = real_cal(yc_adc_getbuf[config[i].ub_index], len);
				real2 = real_cal(yc_adc_getbuf[config[i].line[j].ib_index], len);
				imag1 = imag_cal(yc_adc_getbuf[config[i].ub_index], len);
				imag2 = imag_cal(yc_adc_getbuf[config[i].line[j].ib_index], len);
				angel_diff1 = atan2(imag1, real1);
				angel_diff2 = atan2(imag2, real2);
				angel_diff  = angel_diff2 - angel_diff1;
				cosb = cos(angel_diff);
				sinb = sin(angel_diff);
				pb = yc_tbl.bus[i].ub.raw * yc_tbl.line[j].ib.raw * cosb;
				qb = yc_tbl.bus[i].ub.raw * yc_tbl.line[j].ib.raw * sinb;
				p_gl = pa + pb;
				q_gl = qa + qb;
				datatemp = p_gl * p_gl + q_gl * q_gl;
				s_gl = sqrt(datatemp);
				yc_tbl.line[i * config[i].line_count + j].p.raw = p_gl;
				yc_tbl.line[i * config[i].line_count + j].q.raw = q_gl;
				yc_tbl.line[i * config[i].line_count + j].s.raw = s_gl;
				yc_tbl.line[i * config[i].line_count + j].cos.raw = (p_gl / s_gl);
			}
		}
	}
}

/**
 * @brief 		adc采样数据校正/恢复调理系数
 * @param  in		输入数据指针
 * @param  out		校正后输出数据
 * @param  row_len	行数
 * @param  col_len	列数
 * @param  coff		校正系数
 */
void cal_adjust(short *in, float *out, short row_len, short col_len, float coff[]) //进行数据矫正
{
	short i, j;

	for (i = 0; i < row_len; i++) {
		for (j = 0; j < col_len; j++) {
			*(out + i * col_len + j) = (float)((*(in + i * col_len + j)) * coff[i]);
		}
	}
}

/**
 * @brief 		计算yc数据有效值
 * @param  config	线路配置结构体
 * @param  bun_num	母线数量
 * @param  len		采样数据点数
 */
void calc_yc(struct bus_config_t *config, short bun_num, short len)
{
	short i, j;

	if (config->mode == 0) { //三表法
		for (i = 0; i < bun_num; i++) {
			yc_tbl.bus[i].ua.raw  = calc_rms(yc_adc_getbuf[config[i].ua_index], len);	// ua
			yc_tbl.bus[i].ub.raw  = calc_rms(yc_adc_getbuf[config[i].ub_index], len);	// ub
			yc_tbl.bus[i].uc.raw  = calc_rms(yc_adc_getbuf[config[i].uc_index], len);	// uc
			yc_tbl.bus[i].u0.raw  = calc_zero_rms(yc_adc_getbuf[config[i].ua_index], yc_adc_getbuf[config[i].ub_index], yc_adc_getbuf[config[i].uc_index], len); //u0
			yc_tbl.bus[i].uab.raw = calc_diff_rms(yc_adc_getbuf[config[i].ua_index], yc_adc_getbuf[config[i].ub_index], len);
			yc_tbl.bus[i].ubc.raw = calc_diff_rms(yc_adc_getbuf[config[i].ub_index], yc_adc_getbuf[config[i].uc_index], len);
			yc_tbl.bus[i].uca.raw = calc_diff_rms(yc_adc_getbuf[config[i].uc_index], yc_adc_getbuf[config[i].ua_index], len);
			for (j = 0; j < config[i].line_count; j++) {
				yc_tbl.line[i * config[i].line_count + j].ia.raw = calc_rms(yc_adc_getbuf[config[i].line[j].ia_index], len);
				yc_tbl.line[i * config[i].line_count + j].ib.raw = calc_rms(yc_adc_getbuf[config[i].line[j].ib_index], len);
				yc_tbl.line[i * config[i].line_count + j].ic.raw = calc_rms(yc_adc_getbuf[config[i].line[j].ic_index], len);
				yc_tbl.line[i * config[i].line_count + j].i0.raw = calc_zero_rms(yc_adc_getbuf[config[i].line[j].ia_index], yc_adc_getbuf[config[i].line[j].ib_index], yc_adc_getbuf[config[i].line[j].ic_index], len);
			}//计算线路数据
		}
	} else {
		for (i = 0; i < bun_num; i++) {
			yc_tbl.bus[i].ua.raw  = 0.0;	// ua
			yc_tbl.bus[i].ub.raw  = 0.0;	// ub
			yc_tbl.bus[i].uc.raw  = 0.0;	// uc
			yc_tbl.bus[i].u0.raw  = 0.0; 	//u0
			yc_tbl.bus[i].uab.raw = calc_rms(yc_adc_getbuf[config[i].ua_index], len);
			yc_tbl.bus[i].ubc.raw = calc_rms(yc_adc_getbuf[config[i].ub_index], len);
			yc_tbl.bus[i].uca.raw = cal_line(yc_adc_getbuf[config[i].ua_index], yc_adc_getbuf[config[i].ub_index], len);
			dbg("%f\n",yc_tbl.bus[i].uca.raw);
			for (j = 0; j < config->line_count; j++) {
				yc_tbl.line[i * config->line_count + j].ia.raw = calc_rms(yc_adc_getbuf[config[i].line[j].ia_index], len);
				yc_tbl.line[i * config->line_count + j].ib.raw = calc_rms(yc_adc_getbuf[config[i].line[j].ib_index], len);
				yc_tbl.line[i * config->line_count + j].ic.raw = calc_rms(yc_adc_getbuf[config[i].line[j].ic_index], len);
				yc_tbl.line[i * config[i].line_count + j].i0.raw = calc_zero_rms(yc_adc_getbuf[config[i].line[j].ia_index], yc_adc_getbuf[config[i].line[j].ib_index], yc_adc_getbuf[config[i].line[j].ic_index], len);
			}//计算线路数据
		}
	}

	//yc_save_table(&yc_tbl);
}