//
// Created by 15216 on 2024/11/10.
//

#ifndef FIRMWARE_POSITION_CTRL_H
#define FIRMWARE_POSITION_CTRL_H

#include "Motor.h"
#include "PID.h"
#include "Encoder.h"

#define TARGET_SPEED_MAX    150    // 目标速度的最大值 r/m

#define PWM_MAX_PERIOD_COUNT              (PWM_PERIOD_COUNT - 100)

#define PWM_PERIOD_COUNT     (5600)

void positionCtrl(void);

#endif //FIRMWARE_POSITION_CTRL_H
