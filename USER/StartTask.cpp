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
    // ����LED0����
    LED0Task led0Tsk;
    led0Tsk.Start();
    // ����LED1����
    LED1Task led1Tsk;
    led1Tsk.Start();
    // �����������
    FloatTask floatTsk;
    floatTsk.Start();
    taskEXIT_CRITICAL();
    return true;
}
