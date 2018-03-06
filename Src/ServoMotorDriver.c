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

#define USE_SERVO1
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
#endif

#ifdef USE_SERVO2
#define SERVO2_TIMER          (&htim2)
#define SERVO2_TIMER_CHANNEL  (TIM_CHANNEL_2)
#endif

#ifdef USE_SERVO3
#define SERVO3_TIMER          (&htim2)
#define SERVO3_TIMER_CHANNEL  (TIM_CHANNEL_3)
#endif

#ifdef USE_SERVO4
#define SERVO4_TIMER          (&htim2)
#define SERVO4_TIMER_CHANNEL  (TIM_CHANNEL_4)
#endif

#ifdef USE_SERVO5
#define SERVO5_TIMER          (&htim3)
#define SERVO5_TIMER_CHANNEL  (TIM_CHANNEL_2)
#endif

/*----------------------------------------------------------------------------*/
/* Private members                                                            */
/*----------------------------------------------------------------------------*/

static uint32_t Servo_min = 96000;
static uint32_t Servo_max = 48000;


/*----------------------------------------------------------------------------*/
/* Private function                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Implementation                                                             */
/*----------------------------------------------------------------------------*/

void ServoMotor_Init ()
{
    uint32_t Freq = HAL_RCC_GetPCLK1Freq();

    uint32_t Period = Freq / 50;	// 50Hz (20ms)
    uint32_t Servo_moy = Freq / 750;	// 750Hz (1.5ms)

    Servo_min = (Period / 10) * 1;	// (1ms)
    Servo_max = (Period / 10) * 2;	// (2ms)

    Servo_moy = (Servo_min + Servo_max) / 2U;

    // Initialization Period (20ms)
#if defined(USE_SERVO1) || defined(USER_SERVO2) || defined(USER_SERVO3) || defined(USER_SERVO4)
    __HAL_TIM_SET_AUTORELOAD(SERVO1_TIMER, Period);
#endif
#if defined(USE_SERVO5)
    __HAL_TIM_SET_AUTORELOAD(SERVO5_TIMER, Period);
#endif

    // Initialization Servo on middle (1,5ms)
#if defined(USE_SERVO1)
    __HAL_TIM_SET_COMPARE(SERVO1_TIMER, SERVO1_TIMER_CHANNEL, Servo_moy);
#endif
#if defined(USE_SERVO2)
    __HAL_TIM_SET_COMPARE(SERVO2_TIMER, SERVO2_TIMER_CHANNEL, Servo_moy);
#endif
#if defined(USE_SERVO3)
    __HAL_TIM_SET_COMPARE(SERVO3_TIMER, SERVO3_TIMER_CHANNEL, Servo_moy);
#endif
#if defined(USE_SERVO4)
    __HAL_TIM_SET_COMPARE(SERVO4_TIMER, SERVO4_TIMER_CHANNEL, Servo_moy);
#endif
#if defined(USE_SERVO5)
    __HAL_TIM_SET_COMPARE(SERVO5_TIMER, SERVO5_TIMER_CHANNEL, Servo_moy);
#endif
}

void ServoMotor_Enable (enum ServoMotor servo)
{
    switch (servo)
    {
#ifdef USE_SERVO1
        case SERVO1:
            HAL_TIM_PWM_Start(SERVO1_TIMER, SERVO1_TIMER_CHANNEL);
		break;
#endif
#ifdef USE_SERVO2
        case SERVO2:
            HAL_TIM_PWM_Start(SERVO2_TIMER, SERVO2_TIMER_CHANNEL);
        break;
#endif
#ifdef USE_SERVO3
        case SERVO3:
            HAL_TIM_PWM_Start(SERVO3_TIMER, SERVO3_TIMER_CHANNEL);
        break;
#endif
#ifdef USE_SERVO4
        case SERVO4:
            HAL_TIM_PWM_Start(SERVO4_TIMER, SERVO4_TIMER_CHANNEL);
        break;
#endif
#ifdef USE_SERVO5
        case SERVO5:
            HAL_TIM_PWM_Start(SERVO5_TIMER, SERVO5_TIMER_CHANNEL);
        break;
#endif
        default:
        break;
    }
}

void ServoMotor_Disable (enum ServoMotor servo)
{
    switch (servo)
    {
#ifdef USE_SERVO1
        case SERVO1:
            HAL_TIM_PWM_Stop(SERVO1_TIMER, SERVO1_TIMER_CHANNEL);
        break;
#endif
#ifdef USE_SERVO2
        case SERVO2:
            HAL_TIM_PWM_Stop(SERVO2_TIMER, SERVO2_TIMER_CHANNEL);
        break;
#endif
#ifdef USE_SERVO3
        case SERVO3:
            HAL_TIM_PWM_Stop(SERVO3_TIMER, SERVO3_TIMER_CHANNEL);
        break;
#endif
#ifdef USE_SERVO4
        case SERVO4:
            HAL_TIM_PWM_Stop(SERVO4_TIMER, SERVO4_TIMER_CHANNEL);
        break;
#endif
#ifdef USE_SERVO5
        case SERVO5:
            HAL_TIM_PWM_Stop(SERVO5_TIMER, SERVO5_TIMER_CHANNEL);
        break;
#endif
        default:
        break;
    }
}

void ServoMotor_SetPosition_usec (enum ServoMotor servo, uint16_t usec)
{
    uint16_t pwm = 0;

    // Check limits
    if (usec < 1000)
    	usec = 1000;
    else if(usec > 2000)
    	usec = 2000;

    pwm = 1000*1000 / usec;

    switch (servo)
    {
#ifdef USE_SERVO1
        case SERVO1:
            __HAL_TIM_SET_COMPARE(SERVO1_TIMER, SERVO1_TIMER_CHANNEL, pwm);
        break;
#endif
#ifdef USE_SERVO2
        case SERVO2:
            __HAL_TIM_SET_COMPARE(SERVO2_TIMER, SERVO2_TIMER_CHANNEL, pwm);
        break;
#endif
#ifdef USE_SERVO3
        case SERVO3:
            __HAL_TIM_SET_COMPARE(SERVO3_TIMER, SERVO3_TIMER_CHANNEL, pwm);
        break;
#endif
#ifdef USE_SERVO4
        case SERVO4:
            __HAL_TIM_SET_COMPARE(SERVO4_TIMER, SERVO4_TIMER_CHANNEL, pwm);
        break;
#endif
#ifdef USE_SERVO5
        case SERVO5:
            __HAL_TIM_SET_COMPARE(SERVO5_TIMER, SERVO5_TIMER_CHANNEL, pwm);
        break;
#endif
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
