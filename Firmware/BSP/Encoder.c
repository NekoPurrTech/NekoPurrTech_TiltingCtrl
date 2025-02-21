//
// Created by 孟博文 on 2024/11/6.
//

#include "Encoder.h"
EncoderPara n20_encoder;
EncoderCounter n20_counter;

void encoderInit(void)
{
    n20_encoder.encoder_timer = htim1;
    n20_encoder.encoder_resolution = 17;
    n20_encoder.encoder_total_resolution = n20_encoder.encoder_resolution * 4;
    n20_counter.overflow_count = 0;
    n20_counter.direction = 0;
    n20_counter.capture_count = 0;
    n20_counter.last_count = 0;
    n20_counter.shaft_speed = 0.0f;
    n20_encoder.gear_ratio = 160;
    HAL_TIM_Encoder_Start(&n20_encoder.encoder_timer, TIM_CHANNEL_ALL);
    HAL_TIM_Base_Start_IT(&htim3);
//    RetargetInit(&huart1);
}

uint32_t getEncoderCount(void)
{
    n20_counter.capture_count =
            __HAL_TIM_GET_COUNTER(&n20_encoder.encoder_timer) + (n20_counter.overflow_count * 65535);
    return n20_counter.capture_count;
}

void calcuateSpeed(void)
{
    n20_counter.direction = __HAL_TIM_IS_TIM_COUNTING_DOWN(&n20_encoder.encoder_timer);
    n20_counter.capture_count =
            __HAL_TIM_GET_COUNTER(&n20_encoder.encoder_timer) + (n20_counter.overflow_count * 65535);
    n20_counter.shaft_speed = (float) (n20_counter.capture_count - n20_counter.last_count) /
                              (float) n20_encoder.encoder_total_resolution * 1;
    n20_counter.raw_speed = n20_counter.shaft_speed / (float) n20_encoder.gear_ratio;
//    printf("%.2f\r\n", n20_counter.raw_speed);
    n20_counter.last_count = n20_counter.capture_count;
    n20_counter.overflow_count = 0;
}