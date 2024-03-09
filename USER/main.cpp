#include "FreeRTOS.h"
#include "LED0Task.h"
#include "LED1Task.h"
#include "StartTask.h"
#include "pSys.h"

#include "delay.h"
#include "led.h"
#include "sys.h"

#include <iostream>

using namespace std;

int main(void)
{
    bool ret = initSystem();
    cout << "Init:" << ret << "\r\n";

    StartTask* tsk = new StartTask();
    tsk->Report();
    tsk->Start();

    vTaskStartScheduler();
    cout << "Exit App.\r\n";
}
