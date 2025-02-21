//
// Created by 孟博文 on 2024/11/6.
//

#ifndef FIRMWARE_ENCODER_H
#define FIRMWARE_ENCODER_H

#include "tim.h"
#include "gpio.h"
#include "Retarget.h"
#include "usart.h"

typedef struct EncoderPara
{
    TIM_HandleTypeDef encoder_timer;
    uint8_t encoder_resolution;         //编码器分辨率
    uint8_t encoder_total_resolution;   //编码器总分辨率 = 编码器分辨率 * 倍频数
    uint8_t gear_ratio;                 //齿轮箱减速比
}EncoderPara;

typedef struct EncoderCounter
{
    int8_t overflow_count;
    int8_t direction;
    int32_t capture_count;
    int32_t last_count;
    float shaft_speed;
    float raw_speed;
}EncoderCounter;

extern EncoderPara n20_encoder;
extern EncoderCounter n20_counter;


void encoderInit(void);
void calcuateSpeed(void);
uint32_t getEncoderCount(void);

#endif //FIRMWARE_ENCODER_H
