#include "sys.h"

// THUMBָ�֧�ֻ������
// �������·���ʵ��ִ�л��ָ��WFI
void WFI_SET(void)
{
    __ASM("WFI");
}
// �ر������ж�(���ǲ�����fault��NMI�ж�)
void INTX_DISABLE(void)
{
    __ASM("CPSID I");
    __ASM("BX LR");
}
// ���������ж�
void INTX_ENABLE(void)
{
    __ASM("CPSIE I");
    __ASM("BX LR");
}
// ����ջ����ַ
// addr:ջ����ַ
void MSR_MSP(u32 addr)
{
    __ASM("MSR MSP, r0 "); // set Main Stack value
    __ASM("BX r14");
}
