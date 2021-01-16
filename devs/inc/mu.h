/**
 * @file mu.h
 * @brief mu
 * @author jiashipeng (1060728573@qq.com)
 * @version 1.0
 * @date 2020-12-16
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-16 <td>1.0     <td>jiashipeng     <td>mu
 * </table>
 */
#ifndef __MU_H__
#define __MU_H__

#ifndef SIMULATOR
#define A9 (1<<31)
#define M4 (0<<31)
#define CMD_POS	(16)
#define CMD_MASK (0x7FFF << CMD_POS)
#define CMD_DATA_MASK (0xFFFF)
#define MU_CH	2
#define MU_WCH	3

enum MU_CMD {
	ADC_DATA,
	MSG,
	SET_DO,
	SET_DO_VALUE,
	CLEAR_DO,
	KICK_DOG,
	PWR_QDJ,
	PWR_ACTIVATION,
	ERR_MU_CMD,
};


enum MSG_STATUS {
	M4_SEND,
	M4_SEND_OK,
	A9_SEND,
	A9_SEND_OK,
	ERR_MSG_STATUS,
};

#ifdef M4FIRMWARE
extern void m4_mu_handler(void);
#endif
#endif
#endif // !__MU_H__
