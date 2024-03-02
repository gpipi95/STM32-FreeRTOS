#include "PTask.h"

using namespace std;

PTask::PTask(const string& name, const uint16_t stackSize, uint16_t priority)
    : _task(NULL)
    , _taskName(name)
    , _stackSize(stackSize)
    , _priority(priority)
{
    BaseType_t xReturned = xTaskCreate((TaskFunction_t)_cyclicJob,
                                       (const char*)_taskName.c_str(),
                                       _stackSize,
                                       (void*)this,
                                       (UBaseType_t)_priority,
                                       _task);
    if (xReturned != pdPASS) {
        /* The task was created. */
        _task = NULL;
    }
}

PTask::~PTask()
{
    if (NULL != _task) {
        vTaskDelete(_task);
    }
}

void PTask::_cyclicJob(PTask* task)
{
    while (true) {
        task->work();
        vTaskDelay(10);
    }
}
