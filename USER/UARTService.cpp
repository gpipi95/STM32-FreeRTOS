#include "UARTService.h"

#include "App.h"

UARTService::UARTService()
    : PTask(UART_SERVICE_TASK_NAME, UART_SERVICE_TASK_STK, UART_SERVICE_TASK_PRI)
    , _data(NULL)
{
    _buffer      = UARTBuffer::instance();
    _delayPeriod = 50;
    _data        = (uint8_t*)malloc(256);
}

UARTService::~UARTService()
{
    if (_data) {
        free(_data);
    }
}

bool UARTService::work()
{
    int len = _buffer->get(_data, 256);

    if (len > 0) {
        printf("Received %d data.\r\n", len);
    }

    return true;
}
