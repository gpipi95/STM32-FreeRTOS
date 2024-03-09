#include "PTask.h"

#include <iomanip>
#include <iostream>

using namespace std;

PTask::PTask(const string& name, const uint16_t stackSize, uint16_t priority)
    : _task(NULL)
    , _taskName(name)
    , _stackSize(stackSize)
    , _priority(priority)
    , _delayPeriod(1)
    , _isOnce(false)
    , _enableDebug(false)
{
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
    if (_task) {
        if (_enableDebug) {
            std::cout << "Task " << Name() << " already started.\r\n";
        }
        return true;
    }

    if (init()) {
        if (_enableDebug) {
            std::cout << "Create PTask1 " << Name() << "\r\n";
        }
        BaseType_t xReturned = xTaskCreate((TaskFunction_t)_cyclicJob,
                                           (const char*)_taskName.c_str(),
                                           _stackSize,
                                           (void*)this,
                                           (UBaseType_t)_priority,
                                           &_task);

        if (_enableDebug) {
            std::cout << "Create PTask2 " << Name() << "\r\n";
        }
        if (xReturned != pdPASS) {
            /* The task was created. */
            _task = NULL;
            if (_enableDebug) {
                std::cout << "Create PTask4 " << Name() << "\r\n";
            }
            return false;
        } else {
            if (_enableDebug) {
                std::cout << "Create PTask3 " << Name() << "\r\n";
            }
            return true;
        }
    }
    return false;
}

string PTask::Name() const
{
    return _taskName;
}

void PTask::Report() const
{
    cout << _taskName
         << ":" << _priority
         << ":" << _stackSize
         << ":" << _isOnce
         << "\r\n";
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

void PTask::_cyclicJob(void* pvParameters)
{
    PTask* task = static_cast<PTask*>(pvParameters);
    if (NULL == task) {
        return;
    }

    bool ret = true;
    if (task->_enableDebug) {
        cout << "Task2:" << task->Name() << hex << task << "\r\n";
    }
    do {
        ret = task->work();
        vTaskDelay(task->_delayPeriod);
    } while ((!task->_isOnce) && ret);

    if (task->_enableDebug) {
        cout << "Del task " << task->Name() << ".\r\n";
    }
    delete task;
}
