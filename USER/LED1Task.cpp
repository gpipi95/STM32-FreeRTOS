#include "LED1Task.h"

#include "App.h"
#include "led.h"

#include <iostream>

using namespace std;
LED1Task::LED1Task()
    : PTask(LED1_TASK_NAME, LED1_TASK_STK, LED1_TASK_PRI)
{
    _delayPeriod = 800;
    // _reportSTK   = true;
}

LED1Task::~LED1Task()
{
}

bool LED1Task::work()
{
    LED1 = 0;
    vTaskDelay(200);
    LED1 = 1;
    return true;
}
