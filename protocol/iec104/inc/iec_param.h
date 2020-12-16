/**
 * @file iec_param.h
 * @brief IEC protocol parameters structure
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
#ifndef __IEC_PARAM_H__
#define __IEC_PARAM_H__

#include "dtu.h"

typedef struct tagT_IEC10X_CFG {
	WORD tran_no;//转发序号 区分多个转发，对应转发表
	WORD protocol;//协议类型 0:104 1:101 区分不同协议
	WORD link_addr;//链路地址
	WORD comm_addr;//公共地址
	BYTE encryption;//加密
	BYTE yc_type;//遥测类型
	BYTE yc_time;//遥测时标
	BYTE yc_send_type;//0:循环 1:越限 区分遥测循环上送的方式
	DWORD yc_send_tm;//上送周期 遥测循环上送的周期时间
	BYTE ym_type;//电度类型
	BYTE ym_time;//电度时标
	union {
		BYTE cs_type;//服务器还是客户端 0:server 1:client
		BYTE balance;//平衡传输标记 0:非平衡传输 1:平衡传输
	} tran_model;

	union {
		struct {
			WORD index; //串口序号
			char scom[32]; //串口名称
			WORD badurate; //波特率
			WORD data_bits; //数据位
			WORD stop_bits; //停止位
			WORD parity; //校验
		} ch101;
		struct {

			char sip[32]; //子站IP
			char mip[32]; //主站IP
			WORD prot; //端口号
		} ch104;
	} channel;

	union {
		struct {

			DWORD recv_tm;//接收超时时间
			BYTE resend_count;//重传次送
		} t101;
		struct {
			DWORD T0;
			DWORD T1;
			DWORD T2;
			DWORD T3;
			BYTE K;
			BYTE W;
		} t104;
	} timeout;

	BYTE link_addr_len; //链路地址字节数
	BYTE comm_addr_len; //公共地址字节数
	BYTE cot_len; //传送原因字节数
	BYTE info_len; //信息体地址字节数 细则规定101为2个字节，104为3个字节
	WORD yc_begin, yc_end; //遥测信息体地址起始
	WORD di_begin, di_end; //遥信信息体地址起始
	//WORD spi_begin,spi_end;
	//WORD dpi_begin,dpi_end;
	WORD yk_begin, yk_end; //遥控信息体地址起始
	WORD ym_begin, ym_end; //电度信息体地址起始
	DWORD terminal_start_tm;//终端启动时间
	DWORD link_tm; //104连接响应时间
	DWORD callall_tm; //总召响应时间
	DWORD soe_up_tm; //SOE上送时间
	DWORD yk_sel_tm; //遥控选择响应时间
	DWORD yk_exc_tm; //遥控执行响应时间
	DWORD yk_cancel_tm; //遥控撤消响应时间
	DWORD yk_exc_interval; //选择成功后遥控执行间隔
	DWORD read_runsn_tm; //读取定值区号响应时间
	DWORD read_setval_tm; //读取定值/参数响应时间
	DWORD set_sel_tm; //预置定值响应时间
	DWORD set_exc_tm; //固化定值响应时间
	DWORD read_dir_tm; //读取目录响应时间
	DWORD read_file_tm; //读取文件数据响应时间
} T_IEC10X_CFG;

// 数据条目结构体
typedef struct tagTranDataItem {
	WORD tran_index;//数据远传序号
	WORD point_index;//设备数据点序号
	WORD data_type;//数据类型
	WORD point_type;//数据点类型
	float cc2;//系数
} TranDataItem;

// 远传配置结构体
typedef struct tagT_TRANCFG {
	WORD wIndex; //转发序号
	WORD wAi; //遥测数目
	WORD wDi; //遥信数目
	WORD wDd; //电度数目
	WORD wDo; //遥控数目
	TranDataItem m_ai[MAX_TRAN_AI]; //遥测参数 数组或指针
	TranDataItem m_di[MAX_TRAN_DI]; //遥信参数
	TranDataItem m_do[MAX_TRAN_DO]; //遥控参数
	TranDataItem m_dd[MAX_TRAN_DD]; //电度参数
} T_TRANCFG;

#endif