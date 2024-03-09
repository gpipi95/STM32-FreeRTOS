#include "LED0Task.h"

#include "App.h"
#include "led.h"

LED0Task::LED0Task()
    : PTask(LED0_TASK_NAME, LED0_TASK_STK, LED0_TASK_PRI)
{
    _delayPeriod = 1000;
}

LED0Task::~LED0Task()
{
}

bool LED0Task::work()
{
    LED0 = ~LED0;
    return true;
}
