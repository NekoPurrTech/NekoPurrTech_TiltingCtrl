//
// Created by 孟博文 on 2024/11/6.
//

#ifndef FIRMWARE_MOTOR_H
#define FIRMWARE_MOTOR_H

#include "gpio.h"
#include "tim.h"

typedef struct MOTOR_PARAM
{
    TIM_HandleTypeDef motor_timer;
    uint32_t motor_channel;
    uint8_t motor_period_count;
    uint16_t dutyfactor;
    uint8_t is_enable;
}MOTOR_PARAM;

void motorInit(void);
void startMotor(void);
void stopMotor(void);
void setMotorDirection(uint8_t direction);
void setMotorSpeed(uint16_t speed);

extern MOTOR_PARAM n20_motor;

#endif //FIRMWARE_MOTOR_H
