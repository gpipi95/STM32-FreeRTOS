#ifndef UARTBUFFER_H
#define UARTBUFFER_H

#pragma once

#include "lockfree.hpp"

class UARTBuffer {
public:
    static UARTBuffer* instance();

    typedef lockfree::spsc::RingBuf<uint8_t, 256> BufferType;

    int capacity() const { return 256; }
    int write(uint8_t* data, int length);
    int get(uint8_t* data, int length);

private:
    UARTBuffer();
    ~UARTBuffer() { }
};

#endif