#include "FreeRTOS.h"
#include "StartTask.h"
#include "pSys.h"

#include "delay.h"
#include "led.h"
#include "sys.h"

#include "Test/RngBufTest.h"

#include <iostream>
#include <stdio.h>

using namespace std;

int main(void)
{
    bool ret = initSystem();
    printf("Init: %d\r\n", ret);
    delay_ms(2000);
    auto start = new StartTask();

    printf("Starting 1\r\n");

    delay_ms(2000);

    ret = start->Start();
    printf("StartTask start: %d\r\n", ret);

    RngBufTest test;

    test.Test();

    cout << "this is a test string" << endl;

    vTaskStartScheduler(); // 开启任务调度
}
