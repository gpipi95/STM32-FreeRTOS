#include "FreeRTOS.h"
#include "StartTask.h"
#include "system.h"

int main(void)
{
    initSystem();
    StartTask start;

    start.Start();
    vTaskStartScheduler(); // 开启任务调度
}
