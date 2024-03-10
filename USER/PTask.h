#pragma once
#ifndef PTASK_H
#define PTASK_H

#include <string>

#include "cmsis_os.h"
#include "task.h"

class PTask {
public:
    PTask(const char* name, uint16_t stackSize, uint16_t priority);
    virtual ~PTask();

    bool         Start();
    std::string  Name() const;
    void         Report() const;
    bool         IsDebugEabled() const { return _enableDebug; }
    osThreadId_t Handle() const { return _task; }

private:
    static void  _cyclicJob(void* task);
    osThreadId_t _task;

    char           _taskName[16];
    const uint16_t _stackSize;
    uint16_t       _priority;

protected:
    uint16_t _delayPeriod;
    bool     _isOnce;
    bool     _enableDebug;
    bool     _reportSTK;

    virtual bool init();
    virtual bool work();
};
#endif
