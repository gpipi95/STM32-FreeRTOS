#ifndef UTILS_H
#define UTILS_H

#pragma once

#include "FreeRTOS.h"

class Utils {
public:
    Utils();
    ~Utils();

    static void printArray(uint8_t* buf, int len);
    static void printArrayHexASCII(uint8_t* buf, int len);

private:
};

#endif