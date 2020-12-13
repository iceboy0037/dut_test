/**
 * @file dtu_config.h
 * @brief DTU device hardware configuration
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

#ifndef __DTU_CONFIG_H__
#define __DTU_CONFIG_H__

#define CONFIG_PWR_BOARD_NUMBER		1	// Power board number
#define CONFIG_DO_BOARD_NUMBER 		2	// DO output board number
#define	CONFIG_DI_BOARD_NUMBER		4 	// DI input board number
#define CONFIG_AD_BOARD_NUMBER 		5	// AD board number

// DI board configuration
#define	CONFIG_DI_NUMBER_PER_BOARD	23
#define	CONFIG_DI_NUMBER 		(CONFIG_DI_BOARD_NUMBER * CONFIG_DI_NUMBER_PER_BOARD)

// DO board configuration
#define CONFIG_DO_NUMBER_PER_BOARD	16
#define CONFIG_DO_NUMBER 		(CONFIG_DO_BOARD_NUMBER * CONFIG_DO_NUMBER_PER_BOARD)

// Power board configuration
#define CONFIG_PWR_DI_NUMBER 		7
#define CONFIG_PWR_DC_NUMBER 		2

// AD board configuration
#define CONFIG_ADC_CHANNEL_PER_BOARD	16
#define CONFIG_ADC_CHANNEL_NUMBER	(CONFIG_AD_BOARD_NUMBER * CONFIG_ADC_CHANNEL_PER_BOARD)

#endif