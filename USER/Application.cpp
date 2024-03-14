#include "Application.h"
#include "Global.h"
#include "StartTask.h"
#include "Utils.h"

#include "lwrb/lwrb.h"

#include <iostream>

uint8_t rx_buffer1[BUFFER_SIZE];
uint8_t rx_buffer3[BUFFER_SIZE];
uint8_t rx_rng_buffer1[BUFFER_SIZE * 2];
uint8_t rx_rng_buffer3[BUFFER_SIZE * 2];

lwrb_t rng_buf1;
lwrb_t rng_buf3;

uint16_t buf1Last = 0;
uint16_t buf3Last = 0;

void startFirstTask()
{
    Global::SetRxBuffer1(rx_buffer1);
    Global::SetRxBuffer3(rx_buffer3);
    Global::SetRxRngBuffer1(rx_rng_buffer1);
    Global::SetRxRngBuffer3(rx_rng_buffer3);
    Global::SetRngBuffer1(&rng_buf1);
    Global::SetRngBuffer3(&rng_buf3);

    uint8_t ret = 0;
    ret         = lwrb_init(&rng_buf1, rx_rng_buffer1, sizeof(rx_rng_buffer1));
    ret         = lwrb_init(&rng_buf3, rx_rng_buffer3, sizeof(rx_rng_buffer3));

    StartTask* start = new StartTask();
    start->Start();
}

void usrInitFirst()
{

    if (HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rx_buffer1, sizeof(rx_buffer1)) != HAL_OK) {
        Error_Handler();
    }
    if (HAL_UARTEx_ReceiveToIdle_DMA(&huart3, rx_buffer3, sizeof(rx_buffer3)) != HAL_OK) {
        Error_Handler();
    }
}

void mainCyclicJob()
{
}

extern "C" void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef* huart, uint16_t Size)
{
    bool isIdle = false;

    switch (HAL_UARTEx_GetRxEventType(huart)) {
    case HAL_UART_RXEVENT_IDLE:
        isIdle = true;
        break;
    case HAL_UART_RXEVENT_HT:
        return; // do not process half full
        break;
    default:
        break;
    };

    if (huart == &huart1) {
        if (buf1Last > 0) {
            lwrb_write(&rng_buf1, rx_buffer1 + buf1Last, Size - buf1Last);
        } else {
            lwrb_write(&rng_buf1, rx_buffer1, Size);
        }
        buf1Last = isIdle ? Size : 0;

    } else if (huart == &huart3) {
        if (buf3Last > 0) {
            lwrb_write(&rng_buf3, rx_buffer3 + buf3Last, Size - buf3Last);
        } else {
            lwrb_write(&rng_buf3, rx_buffer3, Size);
        }
        buf3Last = isIdle ? Size : 0;
    }
}