//
// Created by 15216 on 2024/11/10.
//

#ifndef FIRMWARE_PID_H
#define FIRMWARE_PID_H

#include "stm32f0xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "Encoder.h"


/*pid*/
typedef struct PID
{
    float target_val;     //Ä¿±êÖµ
    float actual_val;     //Êµ¼ÊÖµ
    float err;            //¶¨Òåµ±Ç°Æ«²îÖµ
    float err_next;       //¶¨ÒåÏÂÒ»¸öÆ«²îÖµ
    float err_last;       //¶¨Òå×îºóÒ»¸öÆ«²îÖµ
    float Kp, Ki, Kd;     //¶¨Òå±ÈÀý¡¢»ý·Ö¡¢Î¢·ÖÏµÊý
    float integral;
}PID;

extern PID position_pid;
extern PID speed_pid;


void pidParamInit(void);
void setPIDTarget(PID *pid, float temp_val);
float getPIDTarget(PID *pid);
void setPIDParam(PID *pid, float Kp,float Ki,float Kd);
float positionPIDCalculate(PID *pid, float actual_val);
float speedPIDCalculate(PID *pid, float actual_val);



#endif //FIRMWARE_PID_H
