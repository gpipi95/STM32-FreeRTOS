#ifndef LED1TASK_H
#define LED1TASK_H

#pragma once
#include "PTask.h"

class LED1Task : public PTask {
public:
    LED1Task();
    virtual ~LED1Task();

private:
    virtual bool work();
};

#endif
