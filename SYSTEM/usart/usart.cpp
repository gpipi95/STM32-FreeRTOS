#include "usart.h"
#include "UARTBuffer.h"
#include "sys.h"

#include "FreeRTOS.h" //FreeRTOS使用

#include <iostream>

static UARTBuffer*             g_buffer       = NULL;
static UARTBuffer::BufferType* g_inter_buffer = NULL;
// 加入以下代码,支持printf函数,而不需要选择use MicroLIB
#ifdef __CC_ARM
#pragma import(__use_no_semihosting)
// 标准库需要的支持函数
struct __FILE {
    int handle;
};
#elif defined(__GNUC__) || defined(__clang__)
__ASM(".global __use_no_semihosting\n\t");
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
    while ((USART1->SR & 0X40) == 0)
        ; // 循环发送,直到发送完毕
    USART1->DR = (u8)ch;
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

// 串口1中断服务程序
// 注意,读取USARTx->SR能避免莫名其妙的错误
u8 USART1_RX_BUF[USART_REC_LEN]; // 接收缓冲,最大USART_REC_LEN个字节.
u8 USART3_RX_BUF[USART_REC_LEN];
// 接收状态
// bit15，	接收完成标志
// bit14，	接收到0x0d
// bit13~0，	接收到的有效字节数目
u16 USART1_RX_STA = 0; // 接收状态标记
u16 USART3_RX_STA = 0;

void uart1_init(u32 bound)
{
    // GPIO端口设置
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  // 使能GPIOA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); // 使能USART1时钟

    // 串口1对应引脚复用映射
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);  // GPIOA9复用为USART1
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); // GPIOA10复用为USART1

    // USART1端口配置
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9 | GPIO_Pin_10; // GPIOA9与GPIOA10
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;             // 复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         // 速度50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;            // 推挽复用输出
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;             // 上拉
    GPIO_Init(GPIOA, &GPIO_InitStructure);                    // 初始化PA9，PA10

    // USART1 初始化设置
    USART_InitStructure.USART_BaudRate            = bound;                          // 波特率设置
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;            // 字长为8位数据格式
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;               // 一个停止位
    USART_InitStructure.USART_Parity              = USART_Parity_No;                // 无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 无硬件数据流控制
    USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;  // 收发模式
    USART_Init(USART1, &USART_InitStructure);                                       // 初始化串口1

    USART_Cmd(USART1, ENABLE);                                                      // 使能串口1

                                                                                    // USART_ClearFlag(USART1, USART_FLAG_TC);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // 开启相关中断

    // Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel                   = USART1_IRQn; // 串口1中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;           // 抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 3;           // 子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;      // IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);                                     // 根据指定的参数初始化VIC寄存器、

    g_buffer = UARTBuffer::instance();
    // 此处生成的buffer在后续任务中不为NULL!
    g_inter_buffer = new UARTBuffer::BufferType();
    if (g_inter_buffer && g_buffer) {
        g_buffer->setBuffer(g_inter_buffer);
    } else {
        std::cout << "Buffer create error.\r\n";
    }
}
// bound:波特率
void uart3_init(u32 bound)
{
    // GPIO端口设置
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);

    // USART3端口配置
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;     // 复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 速度50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    // 推挽复用输出
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;     // 上拉
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // USART3 初始化设置
    USART_InitStructure.USART_BaudRate            = bound;                          // 波特率设置
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;            // 字长为8位数据格式
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;               // 一个停止位
    USART_InitStructure.USART_Parity              = USART_Parity_No;                // 无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 无硬件数据流控制
    USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;  // 收发模式
    USART_Init(USART3, &USART_InitStructure);                                       // 初始化串口1

    USART_Cmd(USART3, ENABLE);                                                      // 使能串口1

                                                                                    // USART_ClearFlag(USART1, USART_FLAG_TC);

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); // 开启相关中断

    // Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel                   = USART3_IRQn; // 串口1中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;           // 抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 3;           // 子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;      // IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);                                     // 根据指定的参数初始化VIC寄存器、
}
void USART3_IRQHandler(void)                                            // 串口3中断服务程序
{
    u8 Res;
    if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)              // 接收中断(接收到的数据必须是0x0d 0x0a结尾)
    {
        Res = USART_ReceiveData(USART3);                                //(USART3->DR);	//读取接收到的数据

        if ((USART3_RX_STA & 0x8000) == 0)                              // 接收未完成
        {
            if (USART3_RX_STA & 0x4000)                                 // 接收到了0x0d
            {
                if (Res != 0x0a)
                    USART3_RX_STA = 0;                                  // 接收错误,重新开始
                else
                    USART3_RX_STA |= 0x8000;                            // 接收完成了
            } else                                                      // 还没收到0X0D
            {
                if (Res == 0x0d)
                    USART3_RX_STA |= 0x4000;
                else {
                    USART3_RX_BUF[USART3_RX_STA & 0X3FFF] = Res;
                    USART3_RX_STA++;
                    if (USART3_RX_STA > (USART_REC_LEN - 1))
                        USART3_RX_STA = 0; // 接收数据错误,重新开始接收
                }
            }
        }
    }
}

void USART1_IRQHandler(void)                               // 串口1中断服务程序
{
    uint8_t data;
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) // 接收中断
    {
        data = USART_ReceiveData(USART1);                  //(USART1->DR);	//读取接收到的数据
        if (!g_buffer->write(&data, 1)) {
            // buffer full?
            std::cout << "Buffer full?" << std::hex << g_buffer << "\r\n";
        } else {
            std::cout << std::hex << data;
        }
    }
}
