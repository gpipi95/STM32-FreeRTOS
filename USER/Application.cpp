#include "Application.h"
#include "Global.h"
#include "StartTask.h"
#include "Utils.h"

#include "lwrb/lwrb.h"

#include <iostream>

uint8_t rx_buffer1[BUFFER_SIZE];
uint8_t rx_buffer3[BUFFER_SIZE];
uint8_t rx_rng_buffer1[BUFFER_SIZE * 3];
uint8_t rx_rng_buffer3[BUFFER_SIZE * 3];

// for fputc redirect use
// uint8_t tx_rng_buffer1[BUFFER_SIZE];

lwrb_t rng_buf1;
lwrb_t rng_buf3;
// lwrb_t tx_rng_buf1;

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
    // Global::SetRngBuffer3(&tx_rng_buf1);

    lwrb_init(&rng_buf1, rx_rng_buffer1, sizeof(rx_rng_buffer1));
    lwrb_init(&rng_buf3, rx_rng_buffer3, sizeof(rx_rng_buffer3));
    // lwrb_init(&tx_rng_buf1, tx_rng_buffer1, sizeof(tx_rng_buffer1));

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
    // std::cout << "Transmit data by uart3.\r\n";
    // uint8_t test[3] = { 0xEB, 0x90, 0x40 };
    // HAL_UART_Transmit(&huart3, test, 3, HAL_MAX_DELAY);
}

extern "C" void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef* huart, uint16_t Size)
{
    int len = 0;
    if (huart == &huart1) {
        len = Size - buf1Last;
        if (len > 0) {
            lwrb_write(&rng_buf1, rx_buffer1 + buf1Last, len);
        }
        buf1Last = (Size >= sizeof(rx_buffer1)) ? 0 : Size;

    } else if (huart == &huart3) {
        len = Size - buf3Last;
        if (len > 0) {
            lwrb_write(&rng_buf3, rx_buffer3 + buf3Last, len);
        }
        buf3Last = (Size >= sizeof(rx_buffer3)) ? 0 : Size;
    }
}