/**
 * @file    actions.c
 * @author  Jeremy ROULLAND
 * @date    13 mar. 2018
 * @brief   Actions (Simple, Complex, Control, ...)
 */

#include "actions.h"

#include "stm32f0xx_hal.h"
#include "tim.h"
#include "smbus2_cmd.h"
#include "status.h"

/*----------------------------------------------------------------------------*/
/* Definitions                                                                */
/*----------------------------------------------------------------------------*/

#define false (0U)
#define true  (1U)

#define SERVO_TIM_1234	(&htim2)
#define SERVO_TIM_5	    (&htim3)

/*----------------------------------------------------------------------------*/
/* Private Members                                                            */
/*----------------------------------------------------------------------------*/

static uint8_t _emergencyStop = false;

/*----------------------------------------------------------------------------*/
/* Private Functions                                                          */
/*----------------------------------------------------------------------------*/

void _readInputs(void)
{
	GPIO_PinState input[4] = {GPIO_PIN_RESET};
	uint8_t buff[4] = {0};
	int16_t i = 0;

	input[0] = HAL_GPIO_ReadPin(DIO1_GPIO_Port, DIO1_Pin);
	input[1] = HAL_GPIO_ReadPin(DIO2_GPIO_Port, DIO2_Pin);
	input[2] = HAL_GPIO_ReadPin(DIO3_GPIO_Port, DIO3_Pin);
	input[3] = HAL_GPIO_ReadPin(DIO4_GPIO_Port, DIO4_Pin);

	for(i = 0 ; i < 4 ; i++) {
		if(input[i] == GPIO_PIN_RESET)
			buff[i] = 0U;
		else
			buff[i] = 255U;
	}
	
	smbus2_cmd_SetData(0x05, 4, buff);
}

void _stop(void)
{
	HAL_TIM_PWM_Stop_IT(SERVO_TIM_1234, TIM_CHANNEL_ALL);
	HAL_TIM_PWM_Stop_IT(SERVO_TIM_5,    TIM_CHANNEL_2);
}

void _control_S_AU(void)
{

}

/*----------------------------------------------------------------------------*/
/* Implementation                                                             */
/*----------------------------------------------------------------------------*/

void Update_Process(void)
{
	// Read Inputs
	_readInputs();
	
	// Control S_AU

	// Execute Command
	/* PowerOut : Nothing to do */
}

void EmergencyStop(uint8_t len, uint8_t *buff)
{
	if(buff[0] == 0xFF) {
		_emergencyStop = true;
		_stop();
	}
}

void SetAngle(uint8_t len, uint8_t *buff)
{
	uint8_t unit    = buff[0];
	uint8_t angle   = buff[1];

	/* TODO : Bad precision
		IN Values  : 0 to 255
		OUT Values : 8 + (0 to 8)
		Factor : 32
		   8pwm = 1.0ms 
		  12pwm = 1.5ms
		  16pwm = 2.0ms 
	*/
	
	uint16_t pwm = 8U + ((uint16_t)angle+1U) / 32U;
	
	switch (unit)
	{
		case 0x01:
			__HAL_TIM_SetCompare(SERVO_TIM_1234, TIM_CHANNEL_1, pwm);
			HAL_TIM_PWM_Start_IT(SERVO_TIM_1234, TIM_CHANNEL_1);
			break;
		case 0x02:
			__HAL_TIM_SetCompare(SERVO_TIM_1234, TIM_CHANNEL_2, pwm);
			HAL_TIM_PWM_Start_IT(SERVO_TIM_1234, TIM_CHANNEL_2);
			break;
		case 0x03:
			__HAL_TIM_SetCompare(SERVO_TIM_1234, TIM_CHANNEL_3, pwm);
			HAL_TIM_PWM_Start_IT(SERVO_TIM_1234, TIM_CHANNEL_3);
			break;
		case 0x04:
			__HAL_TIM_SetCompare(SERVO_TIM_1234, TIM_CHANNEL_4, pwm);
			HAL_TIM_PWM_Start_IT(SERVO_TIM_1234, TIM_CHANNEL_4);
			break;
		case 0x05:
			__HAL_TIM_SetCompare(SERVO_TIM_5, TIM_CHANNEL_2, pwm);
			HAL_TIM_PWM_Start_IT(SERVO_TIM_5, TIM_CHANNEL_2);
			break;
		default:
			break;
	}
}

/*----------------------------------------------------------------------------*/
/* Callbacks                                                                  */
/*----------------------------------------------------------------------------*/

