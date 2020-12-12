#ifndef __DTU_CONFIG_H__
#define __DTU_CONFIG_H__

#define CONFIG_PWR_BOARD_NUMBER		1	// Power board number
#define CONFIG_DO_BOARD_NUMBER 		2	// DO output board number
#define	CONFIG_DI_BOARD_NUMBER		4 	// DI input board number
#define CONFIG_AD_BOARD_NUMBER 		5	// AD board number


// DI board configuration
#if CONFIG_DI_BOARD_NUMBER > 0
#define	CONFIG_DI_NUMBER_PER_BOARD	23
#define	CONFIG_DI_NUMBER 		(CONFIG_DI_BOARD_NUMBER * CONFIG_DI_NUMBER_PER_BOARD)
#endif

// DO board configuration
#if CONFIG_DO_BOARD_NUMBER > 0
#define CONFIG_DO_NUMBER_PER_BOARD	16
#define CONFIG_DO_NUMBER 		(CONFIG_DO_BOARD_NUMBER * CONFIG_DO_NUMBER_PER_BOARD)
#endif

// Power board configuration
#if (CONFIG_PWR_BOARD_NUMBER > 0)
#define CONFIG_PWR_DI_NUMBER 		7
#define CONFIG_PWR_DC_NUMBER 		2
#endif

#if (CONFIG_AD_BOARD_NUMBER > 0)
#define CONFIG_ADC_CHANNEL_PER_BOARD	16
#define CONFIG_ADC_CHANNEL_NUMBER	(CONFIG_AD_BOARD_NUMBER * CONFIG_ADC_CHANNEL_PER_BOARD)
#endif

#endif