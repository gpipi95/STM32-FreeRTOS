#include "StartTask.h"

#include "App.h"
#include "FloatTask.h"
#include "LED0Task.h"
#include "LED1Task.h"
#include "UARTService.h"

#include <iostream>

using namespace std;

StartTask::StartTask()
    : PTask(START_TASK_NAME, START_TASK_STK, START_TASK_PRI)
{
    _isOnce      = true;
    _delayPeriod = 1;
}

StartTask::~StartTask()
{
}

bool StartTask::work()
{
    taskENTER_CRITICAL();
    // 创建LED0任务
    LED0Task* led0Tsk = new LED0Task();
    led0Tsk->Start();
    cout << "Start Led0 finished.\r\n";
    // 创建LED1任务
    LED1Task* led1Tsk = new LED1Task();
    led1Tsk->Start();
    cout << "Start Led1 finished.\r\n";
    auto uartServ = new UARTService();
    uartServ->Start();
    cout << "Start uartserv finished.\r\n";
    // 浮点测试任务
    // FloatTask floatTsk;
    // floatTsk.Start();
    taskEXIT_CRITICAL();
    return true;
}
