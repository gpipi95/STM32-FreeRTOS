#include "system.h"

#include "delay.h"
#include "usart.h"
#include "sys.h"
#include "led.h"

bool initSystem()
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); // ����ϵͳ�ж����ȼ�����4
    delay_init(168);                                // ��ʼ����ʱ����
    uart_init(115200);                              // ��ʼ������
    LED_Init();                                     // ��ʼ��LED�˿�
    return true;
}
