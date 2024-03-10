#include "usart.h"

#include "FreeRTOS.h"
#include "main.h"

#include <iostream>

#ifdef __CC_ARM
#pragma import(__use_no_semihosting)
struct __FILE {
    int handle;
};
#elif defined(__GNUC__) || defined(__clang__)
__asm(".global __use_no_semihosting\n\t");
#endif
FILE* $Super$$_sys_open(const char* name, int openmode);
FILE* $Sub$$_sys_open(const char* name, int openmode)
{
    return (FILE*)1; /* everything goes to the same output */
}
// FILE __stdout;
// FILE __stdin;
// 定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x)
{
    x = x;
}
// 重定义fputc函数
int $Sub$$fputc(int ch, FILE* f)
{
    HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
    return ch;
}
int $Sub$$fgetc(FILE* f)
{
    return 0;
}
int $Sub$$ferror(FILE* f)
{
    return EOF;
}

void _ttywrch(int ch)
{
    // while ((USART1->SR & 0X40) == 0)
    //     ; // 循环发送,直到发送完毕
    // USART1->DR = (u8)ch;
    ch = ch;
}

void Print_USART1_UART_Init(void)
{

    /* USER CODE BEGIN USART1_Init 0 */

    /* USER CODE END USART1_Init 0 */

    /* USER CODE BEGIN USART1_Init 1 */

    /* USER CODE END USART1_Init 1 */
    huart1.Instance          = USART1;
    huart1.Init.BaudRate     = 115200;
    huart1.Init.WordLength   = UART_WORDLENGTH_8B;
    huart1.Init.StopBits     = UART_STOPBITS_1;
    huart1.Init.Parity       = UART_PARITY_NONE;
    huart1.Init.Mode         = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart1) != HAL_OK) {
        Error_Handler();
    }
    /* USER CODE BEGIN USART1_Init 2 */

    /* USER CODE END USART1_Init 2 */
}