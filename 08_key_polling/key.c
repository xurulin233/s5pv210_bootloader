#include "stdio.h"

// 定义操作寄存器的宏
#define GPH2CON		0xE0200C40
#define GPH2DAT		0xE0200C44

#define rGPH2CON	(*(volatile unsigned int *)GPH2CON)
#define rGPH2DAT	(*(volatile unsigned int *)GPH2DAT)

// 第一步：初始化按键，将引脚设置为输入模式
void key_init(void)
{
	// 设置GPHxCON寄存器，设置为输入模式
	// GPH2CON的bit0～15全部设置为0，即可
	rGPH2CON &= ~(0xFFFF<<0);
}

extern void led_off(void);
extern void led1(void);
extern void led2(void);
extern void led3(void);
extern void led4(void);


void delay20ms(void)
{
	// 这个函数作用是延时20ms
	// 因为我们这里是裸机程序，且重点不是真的要消抖，而是教学
	// 所以我这里这个程序只是象征性的，并没有实体
	// 如果是研发，那就要花时间真的调试出延时20ms的程序
	int i, j;
	
	for (i=0; i<100; i++)
	{
		for (j=0; j<1000; j++)
		{
			i * j;
		}
	}
}

// 第二步：循环读取按键对应的GPIO的电平值，判断有无按键按下。
void key_polling(void)
{
	// 轮询的意思就是反复循环判断有无按键，隔很短时间
	while (1)
	{
		// 对应开发板上标着UP的那个按键
		if (rGPH2DAT & (1<<0))
		{
			// 为1，说明没有按键
			led_off();
		}
		else
		{

			// 添加消抖
			// 第一步，延时
			delay20ms();
			// 第二步，再次检验按键状态
			if (!(rGPH2DAT & (1<<0)))
			{
				// 为0，说明有按键
				led1();
				printf("key down.\n");
			}

		}


		// 对应开发板上标着UP的那个按键
		if (rGPH2DAT & (1<<1))
		{
			// 为1，说明没有按键
			led_off();
		}
		else
		{

			// 添加消抖
			// 第一步，延时
			delay20ms();
			// 第二步，再次检验按键状态
			if (!(rGPH2DAT & (1<<1)))
			{
				// 为0，说明有按键
				led2();
				printf("key down.\n");
			}

		}


		// 对应开发板上标着UP的那个按键
		if (rGPH2DAT & (1<<2))
		{
			// 为1，说明没有按键
			led_off();
		}
		else
		{

			// 添加消抖
			// 第一步，延时
			delay20ms();
			// 第二步，再次检验按键状态
			if (!(rGPH2DAT & (1<<2)))
			{
				// 为0，说明有按键
				led3();
				printf("key down.\n");
			}

		}
		// 对应开发板上标着UP的那个按键
		if (rGPH2DAT & (1<<3))
		{
			// 为1，说明没有按键
			led_off();
		}
		else
		{

			// 添加消抖
			// 第一步，延时
			delay20ms();
			// 第二步，再次检验按键状态
			if (!(rGPH2DAT & (1<<3)))
			{
				// 为0，说明有按键
				led4();
				printf("key down.\n");
			}

		}


	}
}

























