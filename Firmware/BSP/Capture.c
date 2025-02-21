//
// Created by 孟博文 on 2024/11/6.
//

#include "Capture.h"

STRUCT_CAPTURE TIM_ICUserValueStructure;

void captureInit(void)
{
    TIM_ICUserValueStructure.ucFinishFlag = 0;
    TIM_ICUserValueStructure.ucStartFlag = 0;
    TIM_ICUserValueStructure.usCtr = 0;
    TIM_ICUserValueStructure.usPeriod = 0;
    HAL_TIM_Base_Start_IT(&htim1);
    HAL_TIM_IC_Start_IT(&htim1,TIM_CHANNEL_3);
}

void capturePeriod(void)
{
    uint32_t time,TIM_PscCLK;
    float pulse_period = 0.0;
    if (TIM_ICUserValueStructure.ucFinishFlag == 1 ) {
        /* 计算高电平计数值 */
        time = TIM_ICUserValueStructure .usPeriod *
               GENERAL_TIM_PERIOD + TIM_ICUserValueStructure .
                usCtr;
        /* 打印高电平脉宽时间 */
        pulse_period = time/TIM_PscCLK+time%TIM_PscCLK;
//        printf ( "测得高电平脉宽时间：%d.%d s\n", time /
//                                                 TIM_PscCLK, time % TIM_PscCLK );
        TIM_ICUserValueStructure .ucFinishFlag = 0;
    }
}
