/**
 * @file adc.c
 * @brief ADC hw interface
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

#include "dtu.h"
#include "adc.h"
#include "dbg.h"

#ifdef SIMULATOR
#include <math.h>
#include <pthread.h>
#include <unistd.h>

static float grid_freq = ADC_GRID_FREQ_DEFAULT;
static int sample_points = ADC_WAVE_SAMPLE_POINT;
static int adc_buff_count = ADC_BUF_COUNT_DEFAULT;

static short adc_sample_buf[ADC_BUF_COUNT_DEFAULT][CONFIG_ADC_CHANNEL_NUMBER];
int is_adc_initialized = 0;
int is_adc_started = 0;
pthread_t adc_thread_id;
int sample_delay = 1000000;
long long int sample_count = 0;

void adc_sample_thread(void *p)
{
	short val;
	float pi = 3.1415926;	
	int wave_count = 0;
	extern void relay_isr(void);
	
	while (1) {
		if (!is_adc_started) {	// ADC stopped
			usleep(sample_delay);
			continue;
		}
		wave_count++;
		if (wave_count == sample_points) {
			wave_count = 0;
		}
		val = (short)(sin(2 * pi * wave_count / sample_points) * 32768);
		
		sample_points++;
		for (int i = 0; i < CONFIG_ADC_CHANNEL_NUMBER; i++) {
			adc_sample_buf[sample_points % adc_buff_count][i] = val;
		}
		if (sample_points > 0 && (sample_points % sample_points) == 0) {
			#ifdef M4FIRMWARE			
			relay_isr();
			#endif
		}
		
		usleep(sample_delay);
	}
}
#endif


/**
 * @brief Init ADC peripheral
 * @param  grid		ADC sample frequency
 * @param  points	ADC Sample count per period
 * @return int		0 - success 
 */
int adc_init(int grid, int points)
{
#ifdef SIMULATOR
	grid_freq = grid;
	sample_points = points;
	sample_count = 0;
	sample_delay = 1000000 / grid_freq / sample_points;
	if (pthread_create(&adc_thread_id, NULL, (void *)adc_sample_thread, NULL) != 0) {
		dbg("Create sample thread failed\n");
		return -1;
	}
#endif
	return 0;
}

/**
 * @brief Get Current Grid frequency from FPGA
 * @param  grid	Store freq from FPGA
 * @return int 	0 - success
 */
int adc_get_grid_freq(float *grid)
{
#ifdef SIMULATOR
	*grid = grid_freq;
#endif
	return 0;
}

/**
 * @brief Set ADC sample buffer count
 * @param  cnt	Default = 4
 * @return int 0 - success
 */
int adc_set_buff_count(int cnt)
{
#ifdef SIMULATOR
	adc_buff_count = cnt;
#endif
	return 0;
}

/**
 * @brief Read ADC sample buffer count
 * @param  cnt	Desc.
 * @return int 0 - success
 */
int adc_get_buff_count(int *cnt)
{
#ifdef SIMULATOR
	*cnt = adc_buff_count;
#endif
	return 0;	
}


/**
 * @brief Read ADC Buffer
 * @param  buf	Return ADC sample buffer, point count = adc_get_buff_count()
 * @return int 
 */
int adc_get(short *buf)
{
#ifdef SIMULATOR
	for (int i = 0; i < adc_buff_count; i++) {
		memcpy(buf + CONFIG_ADC_CHANNEL_NUMBER * sizeof(short), 
			adc_sample_buf[i], CONFIG_ADC_CHANNEL_NUMBER * sizeof(short));
	}	
#endif
	return 0;
}

/**
 * @brief Start ADC sample, M4's relay_isr() will be called every adc_get_buff_count() points
 * @return int 
 */
int adc_start(void)
{
#ifdef SIMULATOR
	is_adc_started = 1;
#endif
	return 0;
}

/**
 * @brief Stop ADC sample, and relay_isr() will be stop
 * @return int 
 */
int adc_stop(void)
{
#ifdef SIMULATOR
	is_adc_started = 0;
#endif
	return 0;
}