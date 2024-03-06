#include "FloatTask.h"

#include <stdio.h>

FloatTask::FloatTask()
    : PTask("FloatTask", 128, 4)
    , _data(0)
{
}

FloatTask::~FloatTask()
{
}

bool FloatTask::work()
{
    _data += 0.01f;
    printf("data的值为: %.4f\r\n", _data);
    vTaskDelay(1000);

    return true;
}
