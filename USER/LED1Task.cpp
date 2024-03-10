#include "LED1Task.h"

#include "App.h"
#include "stm32f4xx_hal.h"

#include <iostream>

using namespace std;
LED1Task::LED1Task()
    : PTask(LED1_TASK_NAME, LED1_TASK_STK, LED1_TASK_PRI)
{
    _delayPeriod = 800;
    // _reportSTK   = true;
    // _enableDebug = true;
}

LED1Task::~LED1Task()
{
}

bool LED1Task::work()
{
    HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_10);
    osDelay(200);
    HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_10);
    return true;
}
