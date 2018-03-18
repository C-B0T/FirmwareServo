/**
 * @file    actions.c
 * @author  Jeremy ROULLAND
 * @date    13 mar. 2018
 * @brief   Actions (Simple, Complex, Control, ...)
 */

#include "actions.h"

#include "stm32f0xx_hal.h"
#include "smbus2_cmd.h"
#include "status.h"

/*----------------------------------------------------------------------------*/
/* Definitions                                                                */
/*----------------------------------------------------------------------------*/

#define false (0U)
#define true  (1U)

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

}

void _control_S_AU(void)
{

}

/*----------------------------------------------------------------------------*/
/* Implementation                                                             */
/*----------------------------------------------------------------------------*/

void Actions_Process(void)
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



/*----------------------------------------------------------------------------*/
/* Callbacks                                                                  */
/*----------------------------------------------------------------------------*/

