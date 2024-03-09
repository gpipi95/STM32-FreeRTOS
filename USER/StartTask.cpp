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
    _delayPeriod = 2000;
}

StartTask::~StartTask()
{
}

bool StartTask::init()
{
    // 创建LED0任务
    LED0Task* led0Tsk = new LED0Task();
    _tasks[0]         = led0Tsk->Handle();
    led0Tsk->Start();
    cout << "Start Led0 finished.\r\n";
    // 创建LED1任务
    LED1Task* led1Tsk = new LED1Task();
    _tasks[1]         = led1Tsk->Handle();
    led1Tsk->Start();
    cout << "Start Led1 finished.\r\n";
    UARTService* uartServ = new UARTService();
    _tasks[2]             = uartServ->Handle();
    uartServ->Start();
    cout << "Start uartserv finished.\r\n";
    return true;
}

bool StartTask::work()
{
    UBaseType_t stk = 0;
    for (int i = 0; i < 2; i++) {
        stk = uxTaskGetStackHighWaterMark(_tasks[i]);
        cout << "STK" << i << " " << stk << "\r\n";
    }

    return true;
}
