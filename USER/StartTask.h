#ifndef STARTTASK_H
#define STARTTASK_H

#pragma once

#include "PTask.h"

class StartTask : public PTask {
public:
    StartTask();
    virtual ~StartTask();

private:
    bool init();
    bool work();

    TaskHandle_t _tasks[3];
};

#endif
