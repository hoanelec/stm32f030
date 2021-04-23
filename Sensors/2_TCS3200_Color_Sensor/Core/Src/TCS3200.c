/*
 * File		: TCS3200.c
 * Author 	: danghoanelec@gmail.com
 * Release	: 23-04-2021
 * Function	: Read frequency of tcs3200 sensor
 * */
#include "TCS3200.h"
TIM_HandleTypeDef htimx;
uint16_t icValue = 0;
uint16_t preIcValue = 0;
uint16_t T = 0;
uint16_t f = 0;
uint8_t firstEdge = 0;
uint8_t done = 0;
uint32_t channelx;

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim -> Instance == htimx.Instance)
	{
		icValue = __HAL_TIM_GET_COMPARE(&htimx,channelx);
			if(firstEdge ==0 )
			{
				preIcValue = icValue;
				firstEdge++;
			}
			else if(firstEdge == 1)
			{
				T = icValue - preIcValue;
				f = 1000000/T;
				firstEdge = 0;
				done = 1;
				HAL_TIM_IC_Stop_IT(&htimx, channelx);
			}
	}
	//	preIcValue = icValue;
	//1MHZ clock = > T xung => t us
}
uint32_t tcs3200_getPulseFreq(TIM_HandleTypeDef htim,uint32_t channel)
{
	htimx = htim;
	channelx = channel;
	done = 0;
	HAL_TIM_IC_Start_IT(&htimx, channelx);
//	while(done == 0);
	return f;
}
void tcs3200_freq(enum freq f)
{
	switch(f)
	{
	case F_0:
		HAL_GPIO_WritePin(GPIOA, S0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, S1, GPIO_PIN_RESET);
		break;
	case F_2:
		HAL_GPIO_WritePin(GPIOA, S0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, S1, GPIO_PIN_SET);
		break;
	case F_20:
		HAL_GPIO_WritePin(GPIOA, S0, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, S1, GPIO_PIN_RESET);
		break;
	case F_100:
		HAL_GPIO_WritePin(GPIOA, S0, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, S1, GPIO_PIN_SET);
	break;
	}
}
void tcs3200_switchColor(enum color c)
{
	switch(c)
	{
	case RED:
		HAL_GPIO_WritePin(GPIOA, S2, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, S3, GPIO_PIN_RESET);
		break;
	case BLUE:
		HAL_GPIO_WritePin(GPIOA, S2, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, S3, GPIO_PIN_SET);
		break;
	case CLEAR:
		HAL_GPIO_WritePin(GPIOA, S2, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, S3, GPIO_PIN_RESET);
	case GREEN:
		HAL_GPIO_WritePin(GPIOA, S2, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, S3, GPIO_PIN_SET);
		break;
	break;
	}
}
