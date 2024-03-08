#ifndef UARTSERVICE_H
#define UARTSERVICE_H

#pragma once

#include "PTask.h"
#include "UARTBuffer.h"

class UARTService : public PTask {
public:
    UARTService();
    virtual ~UARTService();

private:
    UARTBuffer* _buffer;
    uint8_t*    _data;

    bool work();
};

#endif