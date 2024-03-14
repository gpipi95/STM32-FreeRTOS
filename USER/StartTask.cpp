#include "StartTask.h"

#include "Application.h"
#include "FloatTask.h"
#include "Global.h"
#include "LED0Task.h"
#include "LED1Task.h"
#include "UARTService.h"
#include "main.h"

#include <iostream>

using namespace std;

StartTask::StartTask()
    : PTask(START_TASK_NAME, START_TASK_STK, START_TASK_PRI)
{
    _delayPeriod = 2000;
    // _reportSTK   = true;
    // _enableDebug = true;
}

StartTask::~StartTask()
{
}

bool StartTask::init()
{

    return true;
}

bool StartTask::work()
{
    static bool runOnce = true;
    if (runOnce) {
        taskENTER_CRITICAL();
        LED0Task* led0Tsk = new LED0Task();
        if (!led0Tsk) {
            cout << "Led0 create failed.\r\n";
        } else {
            _tasks[0] = led0Tsk->Handle();
            led0Tsk->Start();
            cout << "Start Led0 finished.\r\n";
        }
        LED1Task* led1Tsk = new LED1Task();
        if (!led1Tsk) {
            cout << "Led1 create failed.\r\n";
        } else {
            _tasks[1] = led1Tsk->Handle();
            led1Tsk->Start();
            cout << "Start Led1 finished.\r\n";
        }
        UARTService* uartServ = new UARTService(Global::GetRngBuffer1(), Global::GetRngBuffer3());
        _tasks[2]             = uartServ->Handle();
        uartServ->Start();
        cout << "Start uartserv finished.\r\n";
        taskEXIT_CRITICAL();
        runOnce = false;
    }

    return true;
}
