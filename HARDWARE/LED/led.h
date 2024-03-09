#ifndef __LED_H
#define __LED_H
#include "sys.h"

#define LED0 PFout(9)  // DS0
#define LED1 PFout(10) // DS1

#ifdef __cplusplus
extern "C" {
#endif

void LED_Init(void); // 初始化

#ifdef __cplusplus
}
#endif
#endif
