#include "LED0Task.h"

#include "Application.h"
#include "stm32f4xx_hal.h"

#include <iostream>

using namespace std;

LED0Task::LED0Task()
    : PTask(LED0_TASK_NAME, LED0_TASK_STK, LED0_TASK_PRI)
{
    _delayPeriod = 1000;
    // _reportSTK   = true;
    // _enableDebug = true;
}

LED0Task::~LED0Task()
{
}

bool LED0Task::work()
{
    HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_9);
    return true;
}
