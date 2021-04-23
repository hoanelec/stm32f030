#ifndef TCS3200_H
#define TCS3200_H
#include "main.h"
#define S0	GPIO_PIN_0
#define S1	GPIO_PIN_1
#define S2	GPIO_PIN_2
#define S3	GPIO_PIN_3
#define TCS3200_FREQ_0	0
#define TCS3200_FREQ_1	1
#define TCS3200_FREQ_2	2
#define TCS3200_FREQ_3	3

enum color{RED,BLUE,GREEN,CLEAR};
enum freq{F_0,F_2,F_20,F_100};
void tcs3200_switchColor(enum color c);
void tcs3200_freq(enum freq f);
uint32_t tcs3200_getPulseFreq(TIM_HandleTypeDef htim,uint32_t channel);

#endif

