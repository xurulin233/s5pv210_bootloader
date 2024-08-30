#include "stdio.h"
#include "main.h"

// ��������Ĵ����ĺ�
#define GPH2CON		0xE0200C40
#define GPH2DAT		0xE0200C44


#define rGPH2CON	(*(volatile unsigned int *)GPH2CON)
#define rGPH2DAT	(*(volatile unsigned int *)GPH2DAT)


#define EXT_INT_2_CON	0xE0200E08
#define EXT_INT_2_PEND	0xE0200F48
#define EXT_INT_2_MASK	0xE0200F08


#define rEXT_INT_2_CON	(*(volatile unsigned int *)EXT_INT_2_CON)
#define rEXT_INT_2_PEND	(*(volatile unsigned int *)EXT_INT_2_PEND)
#define rEXT_INT_2_MASK	(*(volatile unsigned int *)EXT_INT_2_MASK)



//------------------------��ѯ��ʽ������---------------------------
// ��ʼ������
void key_init(void)
{
	// ����GPHxCON�Ĵ���������Ϊ����ģʽ
	// GPH2CON��bit0��15ȫ������Ϊ0������
	rGPH2CON &= ~(0xFFFF<<0);
}

static void delay20ms(void)
{
	// ���������������ʱ20ms
	// ��Ϊ��������������������ص㲻�����Ҫ���������ǽ�ѧ
	// �����������������ֻ�������Եģ���û��ʵ��
	// ������з����Ǿ�Ҫ��ʱ����ĵ��Գ���ʱ20ms�ĳ���
	int i, j;
	
	for (i=0; i<100; i++)
	{
		for (j=0; j<1000; j++)
		{
			i * j;
		}
	}
}

//-----------------------�жϷ�ʽ������-----------------------------------
// ���жϷ�ʽ���������ĳ�ʼ��
void key_init_interrupt(void)
{
	// 1. �ⲿ�ж϶�Ӧ��GPIOģʽ����
	rGPH2CON |= 0xFFFF<<0;		// GPH2_0123��4����������Ϊ�ⲿ�ж�ģʽ
	
	// 2. �жϴ���ģʽ����
	rEXT_INT_2_CON &= ~(0xFFFF<<0);
	rEXT_INT_2_CON |= ((2<<0)|(2<<4)|(2<<8)|(2<<12));	
	
	// 3. �ж�����
	rEXT_INT_2_MASK &= ~(0x0f<<0); // �ⲿ�ж�����
	
	// 4. ����������д1������д0
	rEXT_INT_2_PEND |= (0x0F<<0);
}


void isr_eint16171819(void)
{
	// ������isrӦ����2�����顣
	// ��һ���жϴ�����룬���������ɻ�Ĵ���
	// ��ΪEINT16��31�ǹ����жϣ�����Ҫ�������ٴ�ȥ���־������ĸ����ж�
	if (rEXT_INT_2_PEND & (1<<0))
	{
		printf("eint16\n");
	}
	if (rEXT_INT_2_PEND & (1<<1))
	{
		printf("eint17\n");
	}
	if (rEXT_INT_2_PEND & (1<<2))
	{
		printf("eint18\n");
	}
	if (rEXT_INT_2_PEND & (1<<3))
	{
		printf("eint19\n");
	}

	// �ڶ�������жϹ���
	rEXT_INT_2_PEND |= (0x0f<<0);
	intc_clearvectaddr();
}















