#include "UARTBuffer.h"

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
    if (_buffer) {
        length = min((int)_buffer->GetFree(), length);
        if (_buffer->Write(data, length)) {
            return length;
        }
        return 0;
    } else {
        return 0;
    }
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
    _buffer = new BufferType();
}

UARTBuffer::~UARTBuffer()
{
    if (_buffer) {
        delete _buffer;
    }
}