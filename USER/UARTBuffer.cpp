#include "UARTBuffer.h"

#include <iostream>
#include <utility>

using namespace std;

static UARTBuffer*             _instance = NULL;
static UARTBuffer::BufferType* _buffer   = NULL;

UARTBuffer* UARTBuffer::instance()
{
    if (!_instance) {
        _instance = new UARTBuffer();
    }
    return _instance;
}

int UARTBuffer::write(uint8_t* data, int length)
{
    if (!_buffer) {
        _buffer = new BufferType();
    }
    if (_buffer) {
        length = min((int)_buffer->GetFree(), length);
        cout << "min length " << length << "\r\n";
        if (_buffer->Write(data, length)) {
            cout << "write success"
                 << "\r\n";
            return length;
        } else {
            cout << "write failed"
                 << "\r\n";
        }
        return 0;
    } else {
        cout << "buffer NULL"
             << "\r\n";
        return 0;
    }
}

int UARTBuffer::get(uint8_t* data, int length)
{
    if (!_buffer) {
        _buffer = new BufferType();
    }
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
{
}
