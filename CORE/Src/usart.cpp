#include "usart.h"

#include "FreeRTOS.h"
// #include "Global.h"
#include "main.h"

#include "lwrb/lwrb.h"

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
    // lwrb_write(Global::GetTxRngBuffer1(), (uint8_t*)&ch, 1);
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
