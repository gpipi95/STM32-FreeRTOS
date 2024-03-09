#include "Utils.h"

#include <iostream>

using namespace std;

Utils::Utils()
{
}

Utils::~Utils()
{
}

void Utils::printArray(uint8_t* buf, int len)
{
    for (int i = 0; i < len; i++) {
        cout << hex << buf[i] << ' ';
    }
    cout << "\r\n";
}
