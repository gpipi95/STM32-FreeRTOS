#ifndef FLOATTASK_H
#define FLOATTASK_H

#pragma once
#include "PTask.h"

class FloatTask : public PTask {
public:
    FloatTask();
    virtual ~FloatTask();

private:
    float        _data;
    virtual bool work();
};

#endif
