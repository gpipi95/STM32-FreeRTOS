#pragma once
#ifndef PTASK_H
#define PTASK_H

#include <string>

#include "FreeRTOS.h"
#include "task.h"

class PTask {
public:
    PTask(const std::string& name, uint16_t stackSize, uint16_t priority);
    virtual ~PTask();

    bool Start();

protected:
    virtual bool work();

private:
    static void    _cyclicJob(PTask* task);
    TaskHandle_t*  _task;
    std::string    _taskName;
    const uint16_t _stackSize;
    uint16_t       _priority;
};
#endif
