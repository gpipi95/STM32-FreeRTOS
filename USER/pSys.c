#include "pSys.h"

#include "delay.h"
#include "led.h"
#include "sys.h"
#include "usart.h"

bool initSystem(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); // ����ϵͳ�ж����ȼ�����4
    delay_init(168);                                // ��ʼ����ʱ����
    uart1_init(115200);                             // ��ʼ������
    LED_Init();                                     // ��ʼ��LED�˿�
    return true;
}
