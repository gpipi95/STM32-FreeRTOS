#include "LED0Task.h"

#include "led.h"

LED0Task::LED0Task()
    : PTask("LED0Task", 50, 2)
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
