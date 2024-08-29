#include "stdio.h"

// ��������Ĵ����ĺ�
#define GPH2CON		0xE0200C40
#define GPH2DAT		0xE0200C44

#define rGPH2CON	(*(volatile unsigned int *)GPH2CON)
#define rGPH2DAT	(*(volatile unsigned int *)GPH2DAT)

// ��һ������ʼ������������������Ϊ����ģʽ
void key_init(void)
{
	// ����GPHxCON�Ĵ���������Ϊ����ģʽ
	// GPH2CON��bit0��15ȫ������Ϊ0������
	rGPH2CON &= ~(0xFFFF<<0);
}

extern void led_off(void);
extern void led1(void);
extern void led2(void);
extern void led3(void);
extern void led4(void);


void delay20ms(void)
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

// �ڶ�����ѭ����ȡ������Ӧ��GPIO�ĵ�ƽֵ���ж����ް������¡�
void key_polling(void)
{
	// ��ѯ����˼���Ƿ���ѭ���ж����ް��������ܶ�ʱ��
	while (1)
	{
		// ��Ӧ�������ϱ���UP���Ǹ�����
		if (rGPH2DAT & (1<<0))
		{
			// Ϊ1��˵��û�а���
			led_off();
		}
		else
		{

			// �������
			// ��һ������ʱ
			delay20ms();
			// �ڶ������ٴμ��鰴��״̬
			if (!(rGPH2DAT & (1<<0)))
			{
				// Ϊ0��˵���а���
				led1();
				printf("key down.\n");
			}

		}


		// ��Ӧ�������ϱ���UP���Ǹ�����
		if (rGPH2DAT & (1<<1))
		{
			// Ϊ1��˵��û�а���
			led_off();
		}
		else
		{

			// �������
			// ��һ������ʱ
			delay20ms();
			// �ڶ������ٴμ��鰴��״̬
			if (!(rGPH2DAT & (1<<1)))
			{
				// Ϊ0��˵���а���
				led2();
				printf("key down.\n");
			}

		}


		// ��Ӧ�������ϱ���UP���Ǹ�����
		if (rGPH2DAT & (1<<2))
		{
			// Ϊ1��˵��û�а���
			led_off();
		}
		else
		{

			// �������
			// ��һ������ʱ
			delay20ms();
			// �ڶ������ٴμ��鰴��״̬
			if (!(rGPH2DAT & (1<<2)))
			{
				// Ϊ0��˵���а���
				led3();
				printf("key down.\n");
			}

		}
		// ��Ӧ�������ϱ���UP���Ǹ�����
		if (rGPH2DAT & (1<<3))
		{
			// Ϊ1��˵��û�а���
			led_off();
		}
		else
		{

			// �������
			// ��һ������ʱ
			delay20ms();
			// �ڶ������ٴμ��鰴��״̬
			if (!(rGPH2DAT & (1<<3)))
			{
				// Ϊ0��˵���а���
				led4();
				printf("key down.\n");
			}

		}


	}
}

























