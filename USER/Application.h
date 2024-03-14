#ifndef APPLICATION_H
#define APPLICATION_H

#pragma once

#include "main.h"

#define START_TASK_PRI 1
#define LED0_TASK_PRI 2
#define LED1_TASK_PRI 3
#define UART_SERVICE_TASK_PRI 4

#define START_TASK_STK 108
#define LED0_TASK_STK 108
#define LED1_TASK_STK 108
#define UART_SERVICE_TASK_STK 118

#define START_TASK_NAME "StartTsk"
#define LED0_TASK_NAME "LED0Tsk"
#define LED1_TASK_NAME "LED1Tsk"
#define UART_SERVICE_TASK_NAME "UARTSrvTsk"

#define BUFFER_SIZE 128

#ifdef __cplusplus
extern "C" {
#endif

void startFirstTask();

void usrInitFirst();
void mainCyclicJob();

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef* huart, uint16_t Size);

#ifdef __cplusplus
}
#endif
#endif
