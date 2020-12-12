#ifndef __DEVS_H__
#define __DEVS_H__

int devs_get_di(int *buf, int start, int count);
int devs_set_do(int *buf, int start, int count);


// 
int devs_adc_init(int freq, int count);
int devs_adc_set_freq(int freq);
int devs_adc_get_freq(int *freq);
int devs_adc_set_buff_count(int cnt);
int devs_adc_get_buff_count(int *cnt);
int devs_adc_get(int *buf, int count);
int devs_adc_start(void);
int devs_adc_stop(void);

#endif