/*
 * adc_api.c
 *
 *  Created on: 27 avr. 2018
 *      Author: Jérémy
 */

#include "inputs.h"
#include "stm32f0xx_hal.h"
#include "adc.h"

#define DIO1_CHANNEL	ADC_CHANNEL_0
#define DIO2_CHANNEL	ADC_CHANNEL_1
#define DIO3_CHANNEL	ADC_CHANNEL_2
#define DIO4_CHANNEL	ADC_CHANNEL_3
#define DIO5_CHANNEL	ADC_CHANNEL_7

void Inputs_Init (void)
{
	// Init ADC inputs
	ADC_ChannelConfTypeDef sConfig = {DIO1_CHANNEL | DIO2_CHANNEL | DIO3_CHANNEL | DIO4_CHANNEL | DIO5_CHANNEL, ADC_RANK_NONE};
	HAL_ADC_ConfigChannel(&hadc, &sConfig);

	// Init other special inputs
}

uint8_t Inputs_ADC_Read (enum input dio)
{
	uint8_t val = 0;
	ADC_ChannelConfTypeDef sConfig = {0};

	switch (dio)
	{
		case DIO1:
			sConfig.Channel = DIO1_CHANNEL;
			break;
		case DIO2:
			sConfig.Channel = DIO2_CHANNEL;
			break;
		case DIO3:
			sConfig.Channel = DIO3_CHANNEL;
			break;
		case DIO4:
			sConfig.Channel = DIO4_CHANNEL;
			break;
		case DIO5:
			sConfig.Channel = DIO5_CHANNEL;
			break;
		default:
			break;
	}

	// Enable the channel
	sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
	HAL_ADC_ConfigChannel(&hadc, &sConfig);

	// Convert Analog to Digital
	HAL_ADC_Start(&hadc);
	HAL_ADC_PollForConversion(&hadc, 1);	// Timeout: 1ms
	val = HAL_ADC_GetValue(&hadc);

	// Disable the channel
	sConfig.Rank = ADC_RANK_NONE;
	HAL_ADC_ConfigChannel(&hadc, &sConfig);

	return val;
}
