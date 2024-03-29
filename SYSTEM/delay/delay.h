#ifndef __DELAY_H
#define __DELAY_H
#include <sys.h>

#ifdef __cplusplus
extern "C" {
#endif
void delay_init(void);
void delay_us(u32 nus);
void delay_ms(u32 nms);
void delay_xms(u32 nms);
#ifdef __cplusplus
}
#endif

#endif
