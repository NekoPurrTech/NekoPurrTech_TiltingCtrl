//
// Created by 孟博文 on 2024/11/6.
//

#include "Klicky.h"

KLICKY_PARAM klickyParam;

void klickyInit(void)
{
    klickyParam.klicky_status = GPIO_PIN_RESET;
}

void getKlickyStatus(void)
{
    if(HAL_GPIO_ReadPin(Klicky_GPIO_Port,Klicky_Pin) == GPIO_PIN_RESET)
    {
        klickyParam.klicky_status = 0;
    }
    else if(HAL_GPIO_ReadPin(Klicky_GPIO_Port,Klicky_Pin) == GPIO_PIN_SET)
    {
        klickyParam.klicky_status = 1;
    }
}