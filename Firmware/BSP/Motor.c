//
// Created by 孟博文 on 2024/11/6.
//

#include "Motor.h"

MOTOR_PARAM n20_motor;

void motorInit(void)        //初始化，关闭所有输出
{
    HAL_GPIO_WritePin(IN1_GPIO_Port,IN1_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(IN2_GPIO_Port,IN2_Pin,GPIO_PIN_RESET);
    n20_motor.motor_timer = htim1;
    n20_motor.motor_channel = TIM_CHANNEL_2;
    n20_motor.motor_period_count = htim1.Init.Period;
    n20_motor.dutyfactor = 0;
    n20_motor.is_enable = 0;
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,0);
}

void startMotor(void)
{
    HAL_TIM_PWM_Start(&n20_motor.motor_timer,n20_motor.motor_channel);
    n20_motor.is_enable = 1;
}

void stopMotor(void)
{
    HAL_TIM_PWM_Stop(&n20_motor.motor_timer,n20_motor.motor_channel);
    n20_motor.is_enable = 0;
}

void setMotorDirection(uint8_t direction)
{
    if(direction == 0)  //CW 顺时针旋转
    {
        HAL_GPIO_WritePin(IN1_GPIO_Port,IN1_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(IN2_GPIO_Port,IN2_Pin,GPIO_PIN_RESET);
    }
    else if (direction == 1) //CCW 逆时针旋转
    {
        HAL_GPIO_WritePin(IN1_GPIO_Port,IN1_Pin,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(IN2_GPIO_Port,IN2_Pin,GPIO_PIN_SET);
    }
}

void setMotorSpeed(uint16_t speed)
{
    if(speed > n20_motor.motor_period_count)
    {
        speed = n20_motor.motor_period_count;
    }
    else
    {
        speed = speed;
    }
    n20_motor.dutyfactor = speed;
    __HAL_TIM_SET_COMPARE(&n20_motor.motor_timer,n20_motor.motor_channel,n20_motor.dutyfactor);
}



