#include "PTask.h"

using namespace std;

PTask::PTask(const string& name, const uint16_t stackSize, uint16_t priority)
    : _task(NULL)
    , _taskName(name)
    , _stackSize(stackSize)
    , _priority(priority)
    , _delayPeriod(1)
    , _isOnce(false)
    , _autoDelete(true)
{
    BaseType_t xReturned = xTaskCreate((TaskFunction_t)_cyclicJob,
                                       (const char*)_taskName.c_str(),
                                       _stackSize,
                                       (void*)this,
                                       (UBaseType_t)_priority,
                                       &_task);

    if (xReturned != pdPASS) {
        /* The task was created. */
        _task = NULL;
    } else {
        vTaskSuspend(_task);
    }
}

PTask::~PTask()
{
    if (NULL != _task) {
        vTaskDelete(_task);
    }
}
/**
 * @brief Start must be invoked in suspended state
 *
 * @return true
 * @return false
 */
bool PTask::Start()
{
    bool ret = true;

    eTaskState state = eTaskGetState(_task);
    if (eSuspended != state) {
        return false;
    }

    ret = init();
    if (_task) {
        vTaskResume(_task);
    }
    return ret;
}
/**
 * @brief Do work
 *
 * @return true  success
 * @return false error accured
 */
bool PTask::init()
{
    return true;
}
bool PTask::work()
{
    return true;
}

void PTask::_cyclicJob(PTask* task)
{
    if (NULL == task) {
        return;
    }

    bool ret = true;
    do {
        ret = task->work();
        vTaskDelay(task->_delayPeriod);
    } while ((!task->_isOnce) && ret);

    if (task->_autoDelete) {
        delete task;
    }
}
