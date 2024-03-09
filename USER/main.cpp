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
    delay_ms(200);

    StartTask* tsk = new StartTask();
    tsk->Name();
    tsk->Start();

    vTaskStartScheduler(); // 开启任务调度
    cout << "Exit App.\r\n";
}
