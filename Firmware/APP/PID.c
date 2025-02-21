/* Includes ------------------------------------------------------------------*/
#include "PID.h"

PID position_pid;
PID speed_pid;

/**
  * @brief PID参数初始化
  * @note None
  * @para Nonw
  * @retval None
**/
void pidParamInit()
{
    position_pid.target_val = n20_encoder.encoder_resolution * n20_encoder.gear_ratio;
    position_pid.actual_val = 0.0;
    position_pid.err = 0.0;
    position_pid.err_last = 0.0;
    position_pid.err_next = 0.0;
    position_pid.integral = 0.0;

    position_pid.Kp = 5.145;
    position_pid.Ki = 1.332;
    position_pid.Kd = 10.402;

    speed_pid.target_val = 100.0;
    speed_pid.actual_val = 0.0;
    speed_pid.err = 0.0;
    speed_pid.err_last = 0.0;
    speed_pid.integral = 0.0;

    speed_pid.Kp = 19.240;
    speed_pid.Ki = 3.500;
    speed_pid.Kd = 22.430;
}

/**
  * @brief 设定PID目标值
  * @note None
  * @para temp_val:当前值
  * @retval None
**/
void setPIDTarget(PID *pid, float temp_val)
{
    pid -> target_val = temp_val;
}

/**
  * @brief 获取PID目标值
  * @note None
  * @para None
  * @retval 设定的目标值
**/
float getPIDTarget(PID *pid)
{
    return pid -> target_val;
}

/**
  * @brief 设定PID参数
  * @note None
  * @para Kp:比例值, Ki:积分值, Kd:微分值
  * @retval None
**/
void setPIDParam(PID *pid, float Kp,float Ki,float Kd)
{
    pid -> Kp = Kp;
    pid -> Ki = Ki;
    pid -> Kd = Kd;
}

/**
  * @brief PID调节器解算
  * @note None
  * @para actual_val:实际值
  * @retval PID解算结果
**/
float positionPIDCalculate(PID *pid, float actual_val)
{
    /*计算目标值与实际值的误差*/
    pid->err=pid->target_val-actual_val;

    /* 设定闭环死区 */
    if((pid->err >= -20) && (pid->err <= 20))
    {
        pid->err = 0;
        pid->integral = 0;
    }

    pid->integral += pid->err;    // 误差累积

    /*PID算法实现*/
    pid->actual_val = pid->Kp*pid->err+pid->Ki*pid->integral+pid->Kd*(pid->err-pid->err_last);

    /*误差传递*/
    pid->err_last=pid->err;

    /*返回当前实际值*/
    return pid->actual_val;
}

float speedPIDCalculate(PID *pid, float actual_val)
{
    /*计算目标值与实际值的误差*/
    pid->err=pid->target_val-actual_val;

    if((pid->err<0.2f )&& (pid->err>-0.2f))
        pid->err = 0.0f;

    pid->integral += pid->err;    // 误差累积

    /*PID算法实现*/
    pid->actual_val = pid->Kp*pid->err+pid->Ki*pid->integral+pid->Kd*(pid->err-pid->err_last);

    /*误差传递*/
    pid->err_last=pid->err;

    /*返回当前实际值*/
    return pid->actual_val;
}