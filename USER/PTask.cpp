#include "PTask.h"

#include <iomanip>
#include <iostream>

using namespace std;

PTask::PTask(const char* name, const uint16_t stackSize, uint16_t priority)
    : _task(NULL)
    , _stackSize(stackSize)
    , _priority(priority)
    , _delayPeriod(1)
    , _isOnce(false)
    , _enableDebug(false)
    , _reportSTK(false)
{
    strcpy(_taskName, name);
}

PTask::~PTask()
{
    if (NULL != _task) {
        osThreadTerminate(_task);
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
    osThreadAttr_t attr;
    attr.name       = _taskName;
    attr.stack_size = _stackSize;
    attr.priority   = (osPriority_t)osPriorityNormal;

    if (_task) {
        if (_enableDebug) {
            std::cout << "Task " << Name() << " already created.\r\n";
        }
        return true;
    }

    if (init()) {
        if (_enableDebug) {
            std::cout << "Task init success." << Name() << "\r\n";
        }
        // osThreadId_t _task = osThreadNew(_cyclicJob, this, &attr);
        BaseType_t xReturned = xTaskCreate((TaskFunction_t)_cyclicJob,
                                           (const char*)_taskName,
                                           _stackSize,
                                           (void*)this,
                                           (UBaseType_t)_priority,
                                           &_task);
        if (!_task) {
            /* The task was created. */
            if (_enableDebug) {
                std::cout << "Task create failed." << Name() << "\r\n";
            }
            return false;
        } else {
            if (_enableDebug) {
                std::cout << "Task create success." << Name() << "\r\n";
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
        if (task->_enableDebug) {
            cout << "Task " << task->Name() << " is NULL.\r\n";
        }
        return;
    }

    bool ret = true;
    do {
        ret = task->work();
        if (task->_reportSTK) {
            uint16_t stk = 0;
            stk          = uxTaskGetStackHighWaterMark2(NULL);
            cout << "STK" << pcTaskGetName(NULL) << " " << dec << stk << "\r\n";
        }
        osDelay(task->_delayPeriod);
    } while ((!task->_isOnce) && ret);

    if (task->_enableDebug) {
        cout << "Del Task " << task->Name() << ".\r\n";
    }
    delete task;
}

extern "C" {
void vApplicationStackOverflowHook(TaskHandle_t xTask, char* pcTaskName)
{
    cout << "Task " << hex << xTask << pcTaskName << " STK overflow.\r\n";
}
}
