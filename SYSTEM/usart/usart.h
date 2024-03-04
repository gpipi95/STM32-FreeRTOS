#ifndef __USART_H
#define __USART_H
#include "stdio.h"
#include "stm32f4xx_conf.h"
#include "sys.h"

#define USART_REC_LEN 200 // �����������ֽ��� 200
#define EN_USART1_RX 1    // ʹ�ܣ�1��/��ֹ��0������1����

#ifdef __cplusplus
extern "C" {
#endif

// ����봮���жϽ��գ��벻Ҫע�����º궨��
void uart3_init(u32 bound);
void uart1_init(u32 bound);

#ifdef __cplusplus
}
#endif

#endif
