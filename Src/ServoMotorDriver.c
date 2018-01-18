/**
 * @file    ServoMotorDriver.c
 * @author  C-Bot
 * @date    18 jan. 2018
 * @brief   Servo Motor Driver
 */

#include "ServoMotorDriver.h"

#include "stm32f0xx_hal.h"
#include "main.h"
#include "tim.h"

/**
 * To configure, uncomment define
 *
 */

/*----------------------------------------------------------------------------*/
/* Configuration                                                              */
/*----------------------------------------------------------------------------*/

//#define USE_SERVO1
//#define USE_SERVO2
//#define USE_SERVO3
//#define USE_SERVO4
//#define USE_SERVO5


/*----------------------------------------------------------------------------*/
/* Definitions                                                                */
/*----------------------------------------------------------------------------*/

#ifdef USE_SERVO1
#define SERVO1_TIMER          (&htim2)
#define SERVO1_TIMER_CHANNEL  (TIM_CHANNEL_1)
#else
#define SERVO1_TIMER          ((TIM_HandleTypeDef *)NULL)
#define SERVO1_TIMER_CHANNEL  (0)
#endif

#ifdef USE_SERVO2
#define SERVO2_TIMER          (&htim2)
#define SERVO2_TIMER_CHANNEL  (TIM_CHANNEL_2)
#else
#define SERVO2_TIMER          ((TIM_HandleTypeDef *)NULL)
#define SERVO2_TIMER_CHANNEL  (0)
#endif

#ifdef USE_SERVO3
#define SERVO3_TIMER          (&htim2)
#define SERVO3_TIMER_CHANNEL  (TIM_CHANNEL_3)
#else
#define SERVO3_TIMER          ((TIM_HandleTypeDef *)NULL)
#define SERVO3_TIMER_CHANNEL  (0)
#endif

#ifdef USE_SERVO4
#define SERVO4_TIMER          (&htim2)
#define SERVO4_TIMER_CHANNEL  (TIM_CHANNEL_4)
#else
#define SERVO4_TIMER          ((TIM_HandleTypeDef *)NULL)
#define SERVO4_TIMER_CHANNEL  (0)
#endif

#ifdef USE_SERVO5
#define SERVO5_TIMER          (&htim3)
#define SERVO5_TIMER_CHANNEL  (TIM_CHANNEL_2)
#else
#define SERVO5_TIMER          ((TIM_HandleTypeDef *)NULL)
#define SERVO5_TIMER_CHANNEL  (0)
#endif

/*----------------------------------------------------------------------------*/
/* Private members                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Private function                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Implementation                                                             */
/*----------------------------------------------------------------------------*/

void ServoMotor_Init ()
{
    
}

void ServoMotor_Enable (enum ServoMotor servo)
{
    switch (servo)
    {
        case SERVO1:
            HAL_TIM_PWM_Start(SERVO1_TIMER, SERVO1_TIMER_CHANNEL);
        break;
        case SERVO2:
            HAL_TIM_PWM_Start(SERVO2_TIMER, SERVO2_TIMER_CHANNEL);
        break;
        case SERVO3:
            HAL_TIM_PWM_Start(SERVO3_TIMER, SERVO3_TIMER_CHANNEL);
        break;
        case SERVO4:
            HAL_TIM_PWM_Start(SERVO4_TIMER, SERVO4_TIMER_CHANNEL);
        break;
        case SERVO5:
            HAL_TIM_PWM_Start(SERVO5_TIMER, SERVO5_TIMER_CHANNEL);
        break;
        default:
        break;
    }
}

void ServoMotor_Disable (enum ServoMotor servo)
{
    switch (servo)
    {
        case SERVO1:
            HAL_TIM_PWM_Stop(SERVO1_TIMER, SERVO1_TIMER_CHANNEL);
        break;
        case SERVO2:
            HAL_TIM_PWM_Stop(SERVO2_TIMER, SERVO2_TIMER_CHANNEL);
        break;
        case SERVO3:
            HAL_TIM_PWM_Stop(SERVO3_TIMER, SERVO3_TIMER_CHANNEL);
        break;
        case SERVO4:
            HAL_TIM_PWM_Stop(SERVO4_TIMER, SERVO4_TIMER_CHANNEL);
        break;
        case SERVO5:
            HAL_TIM_PWM_Stop(SERVO5_TIMER, SERVO5_TIMER_CHANNEL);
        break;
        default:
        break;
    }
}

void ServoMotor_SetPosition_usec (enum ServoMotor servo, uint16_t usec)
{
    uint16_t pwm = 0;

    // Calculate pwm motor (100%=3000)
    // TODO: convert usec to pwm
    pwm = usec;

    switch (servo)
    {
        case SERVO1:
            __HAL_TIM_SET_COMPARE(SERVO1_TIMER, SERVO1_TIMER_CHANNEL, pwm);
        break;
        case SERVO2:
            __HAL_TIM_SET_COMPARE(SERVO2_TIMER, SERVO2_TIMER_CHANNEL, pwm);
        break;
        case SERVO3:
            __HAL_TIM_SET_COMPARE(SERVO3_TIMER, SERVO3_TIMER_CHANNEL, pwm);
        break;
        case SERVO4:
            __HAL_TIM_SET_COMPARE(SERVO4_TIMER, SERVO4_TIMER_CHANNEL, pwm);
        break;
        case SERVO5:
            __HAL_TIM_SET_COMPARE(SERVO5_TIMER, SERVO5_TIMER_CHANNEL, pwm);
        break;
        default:
        break;
    }
}

void ServoMotor_SetPosition (enum ServoMotor servo, int16_t angle)
{
    int16_t usec = 0;
    
    if (angle < -90)
        angle = -90;
    else if (angle > 90)
        angle = 90;
    
    usec = 1500 + 1000 * (angle / 180);
    
    ServoMotor_SetPosition_usec(servo, (uint16_t)usec);
}
