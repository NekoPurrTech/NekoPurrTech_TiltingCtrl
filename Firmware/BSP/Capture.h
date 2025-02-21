//
// Created by 孟博文 on 2024/11/6.
//

#ifndef FIRMWARE_CAPTURE_H
#define FIRMWARE_CAPTURE_H

#include "tim.h"
#include "gpio.h"

#define GENERAL_TIM_PERIOD 0xffff

typedef struct
{
    uint8_t   ucFinishFlag;   // 捕获结束标志位
    uint8_t   ucStartFlag;    // 捕获开始标志位
    uint16_t  usCtr;          // 捕获寄存器的值
    uint16_t  usPeriod;       // 自动重装载寄存器更新标志
}STRUCT_CAPTURE;

extern STRUCT_CAPTURE TIM_ICUserValueStructure;

void captureInit(void);
void capturePeriod(void);




#endif //FIRMWARE_CAPTURE_H
