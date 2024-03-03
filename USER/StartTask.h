#ifndef STARTTASK_H
#define STARTTASK_H

#pragma once

#include "PTask.h"

class StartTask : public PTask {
public:
    StartTask();
    virtual ~StartTask();

private:
    virtual bool work();
};

#endif
