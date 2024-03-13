#ifndef RNGBUFTEST_H
#define RNGBUFTEST_H

#pragma once

#include "lwrb/lwrb.h"

class RngBufTest {
public:
    RngBufTest();
    ~RngBufTest();

    void Test();

private:
    uint8_t* buffer;
    lwrb_t   lwrbBuf;
};

#endif