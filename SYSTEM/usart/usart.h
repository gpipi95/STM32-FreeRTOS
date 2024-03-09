#ifndef __USART_H
#define __USART_H
#include "stdio.h"
#include "stm32f4xx_conf.h"
#include "sys.h"

#define USART_REC_LEN 200 // 定义最大接收字节数 200
#define EN_USART1_RX 1    // 使能（1）/禁止（0）串口1接收

#ifdef __cplusplus
extern "C" {
#endif

// 如果想串口中断接收，请不要注释以下宏定义
void uart3_init(u32 bound);
void uart1_init(u32 bound);
void _sys_exit(int x);
void _ttywrch(int ch);
int  $Super$$fputc(int ch, FILE* f);
int  $Sub$$fputc(int ch, FILE* f);
int  $Super$$fgetc(FILE* f);
int  $Sub$$fgetc(FILE* f);
int  $Super$$ferror(FILE* f);
int  $Sub$$ferror(FILE* f);

void USART1_IRQHandler(void);
void USART3_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif
