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

    bool        Start();
    std::string Name() const;
    void        Report() const;

private:
    static void    _cyclicJob(void* task);
    TaskHandle_t   _task;
    std::string    _taskName;
    const uint16_t _stackSize;
    uint16_t       _priority;

protected:
    uint16_t _delayPeriod;
    bool     _isOnce;

    virtual bool init();
    virtual bool work();
};
#endif
