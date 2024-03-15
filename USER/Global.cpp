#include "Global.h"

uint8_t* Global::rx_buffer1_ptr     = NULL;
uint8_t* Global::rx_buffer3_ptr     = NULL;
uint8_t* Global::rx_rng_buffer1_ptr = NULL;
uint8_t* Global::rx_rng_buffer3_ptr = NULL;
lwrb_t*  Global::rng_buf1_ptr       = NULL;
lwrb_t*  Global::rng_buf3_ptr       = NULL;
lwrb_t*  Global::tx_rng_buf1_ptr    = NULL;

uint8_t* Global::GetRxBuffer1()
{
    return rx_buffer1_ptr;
}

uint8_t* Global::GetRxBuffer3()
{
    return rx_buffer3_ptr;
}

uint8_t* Global::GetRxRngBuffer1()
{
    return rx_rng_buffer1_ptr;
}

uint8_t* Global::GetRxRngBuffer3()
{
    return rx_rng_buffer3_ptr;
}

lwrb_t* Global::GetRngBuffer1()
{
    return rng_buf1_ptr;
}

lwrb_t* Global::GetRngBuffer3()
{
    return rng_buf3_ptr;
}

lwrb_t* Global::GetTxRngBuffer1()
{
    return tx_rng_buf1_ptr;
}

void Global::SetRxBuffer1(uint8_t* p)
{
    rx_buffer1_ptr = p;
}

void Global::SetRxBuffer3(uint8_t* p)
{
    rx_buffer3_ptr = p;
}

void Global::SetRxRngBuffer1(uint8_t* p)
{
    rx_rng_buffer1_ptr = p;
}

void Global::SetRxRngBuffer3(uint8_t* p)
{
    rx_rng_buffer3_ptr = p;
}

void Global::SetRngBuffer1(lwrb_t* p)
{
    rng_buf1_ptr = p;
}

void Global::SetRngBuffer3(lwrb_t* p)
{
    rng_buf3_ptr = p;
}

void Global::SetTxRngBuffer1(lwrb_t* p)
{
    tx_rng_buf1_ptr = p;
}
