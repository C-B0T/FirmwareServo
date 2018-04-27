/*
 * adc_api.h
 *
 *  Created on: 27 avr. 2018
 *      Author: Jérémy
 */

#ifndef INPUTS_H_
#define INPUTS_H_

#include "stdint.h"

enum input {DIO1 = 1, DIO2, DIO3, DIO4, DIO5};

void Inputs_Init (void);
uint8_t Inputs_ADC_Read (enum input dio);

#endif /* INPUTS_H_ */
