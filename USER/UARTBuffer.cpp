#include "UARTBuffer.h"

#include <iostream>
#include <utility>

using namespace std;

static UARTBuffer* _instance = NULL;

UARTBuffer* UARTBuffer::instance()
{
    if (!_instance) {
        _instance = new UARTBuffer();
    }
    return _instance;
}

int UARTBuffer::write(uint8_t* data, int length)
{
    int actual = 0;
    if (_buffer) {
        length = min((int)_buffer->GetFree(), length);
        if (_buffer->Write(data, length)) {
            cout << "write "
                 << length
                 << ":"
                 << _buffer->GetAvailable()
                 << "\r\n";
            actual = length;
        } else {
            cout << "write failed"
                 << "\r\n";
        }
    } else {
        cout << "buffer is null."
             << "\r\n";
    }
    return actual;
}

int UARTBuffer::get(uint8_t* data, int length)
{
    if (_buffer) {
        length = min((int)_buffer->GetAvailable(), length);
        if (_buffer->Read(data, length)) {
            return length;
        }
        return 0;
    } else {
        return 0;
    }
}

UARTBuffer::UARTBuffer()
    : _buffer(NULL)
{
}
