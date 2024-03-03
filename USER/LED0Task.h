#ifndef LED0TASK_H
#define LED0TASK_H

#pragma once
#include "PTask.h"

class LED0Task : public PTask {
public:
    LED0Task();
    virtual ~LED0Task();

private:
    virtual bool work();
};

#endif
