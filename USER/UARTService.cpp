#include "UARTService.h"

#include "App.h"
#include "Utils.h"

#include <iostream>

using namespace std;

const int UARTService::_buffer_size = 64;

UARTService::UARTService()
    : PTask(UART_SERVICE_TASK_NAME, UART_SERVICE_TASK_STK, UART_SERVICE_TASK_PRI)
    , _data(NULL)
{
    _buffer      = UARTBuffer::instance();
    _delayPeriod = 5;
    _data        = (uint8_t*)malloc(_buffer_size);
    // _enableDebug = true;
    // _reportSTK   = true;
}

UARTService::~UARTService()
{
    if (_data) {
        free(_data);
    }
}

bool UARTService::work()
{
    int len = _buffer->get(_data, _buffer_size);

    if (len > 0) {
        if (_enableDebug) {
            cout << "Received " << len << " data.\r\n";
            Utils::printArray(_data, len);
        }
    } else {
        // cout << "No data." << hex << _buffer << "\r\n";
    }

    return true;
}
