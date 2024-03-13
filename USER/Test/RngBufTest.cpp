#include "RngBufTest.h"

#include <iostream>

using namespace std;

RngBufTest::RngBufTest()
    : buffer(NULL)
{
    buffer = new uint8_t[20];
    if (buffer) {
        lwrb_init(&lwrbBuf, buffer, 20);
    }
}

RngBufTest::~RngBufTest()
{
    if (buffer) {
        delete[] buffer;
    }
}

void RngBufTest::Test()
{
    int len = 0;
    if (buffer) {
        len = lwrb_get_full(&lwrbBuf);
        cout << "buffer available:" << len << "\r\n";
        len = lwrb_get_free(&lwrbBuf);
        cout << "buffer getFree:" << len << "\r\n";
        uint8_t a[1] = { 0xAA };
        uint8_t b[1] = { 0x00 };
        len          = lwrb_write(&lwrbBuf, a, 1);
        cout << "buffer write:" << len << "\r\n";
        len = lwrb_get_full(&lwrbBuf);
        cout << "buffer available:" << len << "\r\n";
        len = lwrb_get_free(&lwrbBuf);
        cout << "buffer getFree:" << len << "\r\n";

        len = lwrb_read(&lwrbBuf, b, 1);
        cout << "buffer get:" << len << "\r\n";
        len = lwrb_get_full(&lwrbBuf);
        cout << "buffer available:" << len << "\r\n";
        len = lwrb_get_free(&lwrbBuf);
        cout << "buffer getFree:" << len << "\r\n";
    }
}
