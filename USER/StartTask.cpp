#include "StartTask.h"

#include "FloatTask.h"
#include "LED0Task.h"
#include "LED1Task.h"

StartTask::StartTask()
    : PTask("StartTask", 128, 1)
{
    _isOnce      = true;
    _delayPeriod = 1;
    _autoDelete  = true;
}

StartTask::~StartTask()
{
}

bool StartTask::work()
{
    taskENTER_CRITICAL();
    // 创建LED0任务
    LED0Task led0Tsk;
    led0Tsk.Start();
    // 创建LED1任务
    LED1Task led1Tsk;
    led1Tsk.Start();
    // 浮点测试任务
    FloatTask floatTsk;
    floatTsk.Start();
    taskEXIT_CRITICAL();
    return true;
}
