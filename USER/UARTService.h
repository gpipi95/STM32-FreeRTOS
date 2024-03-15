#ifndef UARTSERVICE_H
#define UARTSERVICE_H

#pragma once

#include "PTask.h"
#include "lwrb/lwrb.h"

class UARTService : public PTask {
public:
    UARTService(lwrb_t* buf1, lwrb_t* buf3, lwrb_t* txBuf1);
    virtual ~UARTService();

private:
    const static int _dataSize;
    lwrb_t*          _bufferUart1;
    lwrb_t*          _bufferUart3;
    lwrb_t*          _txBufferUart1;

    uint8_t* _data;

    bool work();
};

#endif