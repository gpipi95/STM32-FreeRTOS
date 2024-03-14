#include "UARTService.h"

#include "Application.h"
#include "Utils.h"

#include <iostream>

const int UARTService::_dataSize = 256;

UARTService::UARTService(lwrb_t* buf1, lwrb_t* buf3)
    : PTask(UART_SERVICE_TASK_NAME, UART_SERVICE_TASK_STK, UART_SERVICE_TASK_PRI)
    , _bufferUart1(buf1)
    , _bufferUart3(buf3)
    , _data(NULL)
{
    _data = new uint8_t[_dataSize];

    _delayPeriod = 5;
    _enableDebug = true;
    // _reportSTK   = true;
}

UARTService::~UARTService()
{
    if (_data) {
        delete[] _data;
    }
}

bool UARTService::work()
{
    int len  = lwrb_get_full(_bufferUart1);
    int rlen = std::min(len, _dataSize);
    if (rlen) {
        len = lwrb_read(_bufferUart1, _data, rlen);
        if (len > 0) {
            if (_enableDebug) {
                std::cout << "Received1 " << len << " data.\r\n";
                Utils::printArrayHex(_data, len);
            }
        } else {
            // cout << "No data." << hex << _buffer << "\r\n";
        }
    }
    len  = lwrb_get_full(_bufferUart3);
    rlen = std::min(len, _dataSize);
    if (rlen) {
        len = lwrb_read(_bufferUart3, _data, rlen);
        if (len > 0) {
            if (_enableDebug) {
                std::cout << "Received3 " << len << " data.\r\n";
                Utils::printArrayHex(_data, len);
            }
        } else {
            // cout << "No data." << hex << _buffer << "\r\n";
        }
    }

    return true;
}
