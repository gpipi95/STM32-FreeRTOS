#include "RngBufTest.h"

#include <iostream>

using namespace lockfree::spsc;
using namespace std;

RngBufTest::RngBufTest()
    : buffer(NULL)
{
    buffer = new TestRngBufType();
}

RngBufTest::~RngBufTest()
{
    if (NULL != buffer) {
        delete buffer;
    }
}

void RngBufTest::Test()
{
    cout << "buffer available:" << buffer->GetAvailable() << endl;
    cout << "buffer getFree:" << buffer->GetFree() << endl;
    uint8_t a[1] = { 0xAA };
    uint8_t b[1] = { 0x00 };
    cout << "buffer write:" << buffer->Write(a, 1) << endl;
    cout << "buffer available:" << buffer->GetAvailable() << endl;
    cout << "buffer getFree:" << buffer->GetFree() << endl;

    cout << "buffer get:" << buffer->Read(b, 1) << endl;
    cout << "buffer available:" << buffer->GetAvailable() << endl;
    cout << "buffer getFree:" << buffer->GetFree() << endl;
}
