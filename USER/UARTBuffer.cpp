#include "UARTBuffer.h"

#include <iostream>

using namespace std;

int UARTBuffer::write(uint8_t* data, int length)
{
    int actual = 0;
    if (_data) {
        length = min((int)lwrb_get_free(&_buffer), length);
        actual = (int)lwrb_write(&_buffer, data, length);
    }
    return actual;
}

int UARTBuffer::get(uint8_t* data, int length)
{
    if (_data) {
        length = min((int)lwrb_get_full(&_buffer), length);
        return lwrb_read(&_buffer, data, length);
    }
    return 0;
}

UARTBuffer::UARTBuffer(int size)
    : _data(NULL)
    , _size(0)
{
    if (size > 0) {
        _size = size;
    }
    _data = new uint8_t[_size];
    if (_data) {
        lwrb_init(&_buffer, _data, _size);
    }
}

UARTBuffer::~UARTBuffer()
{
    if (_data) {
        delete[] _data;
    }
}
