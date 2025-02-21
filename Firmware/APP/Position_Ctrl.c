//
// Created by 15216 on 2024/11/10.
//

#include "Position_Ctrl.h"

void motor_pid_control(void)
{
    static uint32_t location_timer = 0;    // 位置环周期

    if (n20_motor.is_enable == 1)              // 电机在使能状态下才进行控制处理
    {
        static int32_t Capture_Count = 0;    // 当前时刻总计数值
        static int32_t Last_Count = 0;       // 上一时刻总计数值
        float cont_val = 0;                  // 当前控制值

        /* 当前时刻总计数值 = 计数器值 + 计数溢出次数 * ENCODER_TIM_PERIOD  */
        Capture_Count = n20_counter.capture_count;

        if (location_timer++%2 == 0)
        {
            cont_val = positionPIDCalculate(&position_pid, Capture_Count);    // 进行 PID 计算

            /* 目标速度上限处理 */
            if (cont_val > TARGET_SPEED_MAX)
            {
                cont_val = TARGET_SPEED_MAX;
            }
            else if (cont_val < -TARGET_SPEED_MAX)
            {
                cont_val = -TARGET_SPEED_MAX;
            }

            setPIDTarget(&speed_pid, cont_val);    // 设定速度的目标值
        }

        /* 转轴转速 = 单位时间内的计数值 / 编码器总分辨率 * 时间系数  */
        int32_t actual_speed = 0;                 // 实际测得速度

        actual_speed = n20_counter.raw_speed;

        /* 记录当前总计数值，供下一时刻计算使用 */
        Last_Count = Capture_Count;

        cont_val = speedPIDCalculate(&speed_pid, actual_speed);    // 进行 PID 计算

        if (cont_val > 0)    // 判断电机方向
        {
            setMotorDirection(1);
        }
        else
        {
            cont_val = -cont_val;
            setMotorDirection(0);
        }

        cont_val = (cont_val > PWM_MAX_PERIOD_COUNT) ? PWM_MAX_PERIOD_COUNT : cont_val;    // 速度上限处理
        setMotorSpeed(cont_val);                                                 // 设置 PWM 占空比

    }
}