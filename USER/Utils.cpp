#include "Utils.h"

#include <iostream>

using namespace std;

Utils::Utils()
{
}

Utils::~Utils()
{
}

void Utils::printArrayHexASCII(uint8_t* buf, int len)
{
    char ch[3];

    for (int i = 0; i < len; i++) {
        printf("%02X ", buf[i]);
    }
    cout << "\r\n";
}

void Utils::printArray(uint8_t* buf, int len)
{
    for (int i = 0; i < len; i++) {
        cout << hex << buf[i] << ' ';
    }
    cout << "\r\n";
}
