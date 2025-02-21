//
// Created by 15216 on 2024/11/10.
//

#include "LED.h"

void setLEDstatus(uint8_t led_status)
{
    if(led_status == 1)
    {
        HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_RESET);
    }
    else if(led_status == 0)
    {
        HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_SET);
    }
}
