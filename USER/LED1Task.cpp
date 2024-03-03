#include "LED1Task.h"

#include "led.h"

LED1Task::LED1Task()
    : PTask("LED1Task", 50, 3)
{
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
