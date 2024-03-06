#ifndef RNGBUFTEST_H
#define RNGBUFTEST_H

#pragma once

#include "lockfree.hpp"

class RngBufTest {
public:
    RngBufTest();
    ~RngBufTest();

    void Test();

    typedef lockfree::spsc::RingBuf<uint8_t, 200> TestRngBufType;

private:
    TestRngBufType* buffer;
};

#endif