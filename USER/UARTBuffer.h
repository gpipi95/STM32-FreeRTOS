#ifndef UARTBUFFER_H
#define UARTBUFFER_H

#pragma once

#include "lwrb/lwrb.h"

class UARTBuffer {
public:
    UARTBuffer(int size);
    ~UARTBuffer();

    int capacity() const { return _size; }
    int write(uint8_t* data, int length);
    int get(uint8_t* data, int length);

private:
    int      _size;
    lwrb_t   _buffer;
    uint8_t* _data;
};

#endif