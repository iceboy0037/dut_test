/**
 * @file main.c
 * @brief M4 firmware main entry
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

#include <stdio.h>
#include "adc.h"

/**
 * @brief m4 firmware main entry
 * @param  argc	
 * @param  argv	
 * @return int 
 */
int main(int argc, char *argv[])
{
	extern int relay_main(void);
	
	printf("Relay Entry...\n");
	adc_init(ADC_GRID_FREQ_DEFAULT, ADC_WAVE_SAMPLE_POINT);	
	relay_main();
	return 0;
}