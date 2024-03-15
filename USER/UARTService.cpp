#include "UARTService.h"

#include "Application.h"
#include "Utils.h"

#include <iostream>

const int UARTService::_dataSize = BUFFER_SIZE * 3;

UARTService::UARTService(lwrb_t* buf1, lwrb_t* buf3, lwrb_t* txBuf1)
    : PTask(UART_SERVICE_TASK_NAME, UART_SERVICE_TASK_STK, UART_SERVICE_TASK_PRI)
    , _bufferUart1(buf1)
    , _bufferUart3(buf3)
    , _txBufferUart1(txBuf1)
    , _data(NULL)
{
    _data = new uint8_t[_dataSize];

    _delayPeriod = 4;
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
    // receive
    int len = lwrb_get_full(_bufferUart1);
    if (len) {
        len = lwrb_read(_bufferUart1, _data, len);
        if (len > 0) {
            if (_enableDebug) {
                std::cout << "Received1 " << len << " data.\r\n";
                Utils::printArrayHex(_data, len);
            }
        } else {
            // cout << "No data." << hex << _buffer << "\r\n";
        }
    }
    len = lwrb_get_full(_bufferUart3);
    if (len) {
        len = lwrb_read(_bufferUart3, _data, len);
        if (len > 0) {
            if (_enableDebug) {
                std::cout << "Received3 " << len << " data.\r\n";
                Utils::printArrayHex(_data, len);
            }
        } else {
            // cout << "No data." << hex << _buffer << "\r\n";
        }
    }
    // send

    // len           = lwrb_get_linear_block_read_length(_txBufferUart1);
    // uint8_t* addr = (uint8_t*)lwrb_get_linear_block_read_address(_txBufferUart1);
    // while (len > 0) {
    //     HAL_UART_Transmit(&huart1, addr, len, HAL_MAX_DELAY);
    //     len  = lwrb_get_linear_block_read_length(_txBufferUart1);
    //     addr = (uint8_t*)lwrb_get_linear_block_read_address(_txBufferUart1);
    // }
    return true;
}
