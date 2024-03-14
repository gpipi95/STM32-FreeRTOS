#ifndef GLOBAL_H
#define GLOBAL_H

#include "lwrb/lwrb.h"

#ifdef __cplusplus
extern "C" {
#endif
class Global {
public:
    static uint8_t* GetRxBuffer1();
    static uint8_t* GetRxBuffer3();
    static uint8_t* GetRxRngBuffer1();
    static uint8_t* GetRxRngBuffer3();
    static lwrb_t*  GetRngBuffer1();
    static lwrb_t*  GetRngBuffer3();

    static void SetRxBuffer1(uint8_t* p);
    static void SetRxBuffer3(uint8_t* p);
    static void SetRxRngBuffer1(uint8_t* p);
    static void SetRxRngBuffer3(uint8_t* p);
    static void SetRngBuffer1(lwrb_t* p);
    static void SetRngBuffer3(lwrb_t* p);

private:
    static uint8_t* rx_buffer1_ptr;
    static uint8_t* rx_buffer3_ptr;
    static uint8_t* rx_rng_buffer1_ptr;
    static uint8_t* rx_rng_buffer3_ptr;
    static lwrb_t*  rng_buf1_ptr;
    static lwrb_t*  rng_buf3_ptr;
};

#ifdef __cplusplus
}
#endif
#endif
