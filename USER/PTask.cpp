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
    , _autoDelete(true)
{
    cout << "Task1:" << hex << this << "\r\n";
    cout << "Start task 1" << Name() << ".\r\n";
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
        return true;
    }

    if (init()) {
        std::cout << "Create PTask1 " << _taskName.c_str() << "\r\n";
        BaseType_t xReturned = xTaskCreate((TaskFunction_t)_cyclicJob,
                                           (const char*)_taskName.c_str(),
                                           _stackSize,
                                           (void*)this,
                                           (UBaseType_t)_priority,
                                           &_task);

        std::cout << "Create PTask2 " << _taskName.c_str() << "\r\n";
        if (xReturned != pdPASS) {
            /* The task was created. */
            _task = NULL;
            std::cout << "Create PTask4 " << _taskName.c_str() << "\r\n";
            return false;
        } else {
            std::cout << "Create PTask3 " << _taskName.c_str() << "\r\n";
            return true;
        }
    }
    return false;
}
string PTask::Name() const
{
    cout << "My name: " << _taskName.size()
         << ":" << _priority
         << ":" << _stackSize
         << ":" << _autoDelete
         << ":" << _isOnce
         << "\r\n";
    return _taskName;
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
    cout << "Task2:" << hex << task << "\r\n";
    cout << "Start task " << task->Name() << ".\r\n";
    // do {
    //     ret = task->work();
    //     vTaskDelay(task->_delayPeriod);
    // } while ((!task->_isOnce) && ret);

    cout << "Exit task " << task->Name() << ".\r\n";
    if (task->_autoDelete) {
        cout << "Del task " << task->Name() << ".\r\n";
        delete task;
    }
}
