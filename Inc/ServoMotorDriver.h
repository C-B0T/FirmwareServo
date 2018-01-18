/**
 * @file    ServoMotorDriver.h
 * @author  C-Bot
 * @date    18 jan. 2018
 * @brief   Servo Motor Driver
 */

#ifndef INC_SERVOMOTOR_H_
#define INC_SERVOMOTOR_H_

#include "common.h"

/*----------------------------------------------------------------------------*/
/* Definitions                                                                */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Declaration                                                                */
/*----------------------------------------------------------------------------*/

/**
 * @brief ServoMotor Driver Identifier
 */
enum ServoMotor
{
	SERVO1 = 0,
	SERVO2,
	SERVO3,
	SERVO4,
	SERVO5,
	SERVO_MAX
};

/**
 * @brief
 * @param
 */
void ServoMotor_Init ();

/**
 * @brief
 * @param
 */
void ServoMotor_Enable (enum ServoMotor servo);

/**
 * @brief
 * @param
 */
void ServoMotor_Disable (enum ServoMotor servo);

/**
 * @brief Set servo position
 * @param angle in microsec
 */
void ServoMotor_SetPosition_usec (enum ServoMotor servo, uint16_t usec);

/**
 * @brief Set servo position
 * @param angle : degre [-90° to 90°]
 */
void ServoMotor_SetPosition (enum ServoMotor servo, int16_t angle);


#endif /* INC_DCMOTOR_H_ */
