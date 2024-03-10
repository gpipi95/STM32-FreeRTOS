#ifndef __USART_H
#define __USART_H
#include "stdio.h"

#define USART_REC_LEN 200 // 定义最大接收字节数 200
#define EN_USART1_RX 1    // 使能（1）/禁止（0）串口1接收

#ifdef __cplusplus
extern "C" {
#endif

void  _sys_exit(int x);
void  _ttywrch(int ch);
int   $Super$$fputc(int ch, FILE* f);
int   $Sub$$fputc(int ch, FILE* f);
int   $Super$$fgetc(FILE* f);
int   $Sub$$fgetc(FILE* f);
int   $Super$$ferror(FILE* f);
int   $Sub$$ferror(FILE* f);
FILE* $Super$$_sys_open(const char* name, int openmode);
FILE* $Sub$$_sys_open(const char* name, int openmode);

#ifdef __cplusplus
}
#endif

#endif
