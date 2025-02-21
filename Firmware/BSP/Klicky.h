//
// Created by 孟博文 on 2024/11/6.
//

#ifndef FIRMWARE_KLICKY_H
#define FIRMWARE_KLICKY_H

#include "gpio.h"

typedef struct KLICKY_PARAM
{
    uint8_t klicky_status;
}KLICKY_PARAM;

void klickyInit(void);
void getKlickyStatus(void);

extern KLICKY_PARAM klickyParam;

#endif //FIRMWARE_KLICKY_H
