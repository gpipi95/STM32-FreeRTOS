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
    delay_ms(100);
    cout << "Init:" << ret << "\r\n";
    delay_ms(200);

    // StartTask* tsk = new StartTask();
    // tsk->Name();
    // tsk->Start();
    LED0Task led0Tsk;
    led0Tsk.Name();
    led0Tsk.Start();
    cout << "Start Led0 finished.\r\n";
    // 创建LED1任务
    // LED1Task led1Tsk;
    // cout << "Starting Led1.\r\n";
    // led1Tsk.Start();
    // cout << "Start Led1 finished.\r\n";

    vTaskStartScheduler(); // 开启任务调度
    cout << "Exit App.\r\n";
}
