#include "stdio.h"
#include "main.h"

// 定义操作寄存器的宏
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



//------------------------轮询方式处理按键---------------------------
// 初始化按键
void key_init(void)
{
	// 设置GPHxCON寄存器，设置为输入模式
	// GPH2CON的bit0～15全部设置为0，即可
	rGPH2CON &= ~(0xFFFF<<0);
}

static void delay20ms(void)
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

//-----------------------中断方式处理按键-----------------------------------
// 以中断方式来处理按键的初始化
void key_init_interrupt(void)
{
	// 1. 外部中断对应的GPIO模式设置
	rGPH2CON |= 0xFFFF<<0;		// GPH2_0123共4个引脚设置为外部中断模式
	
	// 2. 中断触发模式设置
	rEXT_INT_2_CON &= ~(0xFFFF<<0);
	rEXT_INT_2_CON |= ((2<<0)|(2<<4)|(2<<8)|(2<<12));	
	
	// 3. 中断允许
	rEXT_INT_2_MASK &= ~(0x0f<<0); // 外部中断允许
	
	// 4. 清挂起，清除是写1，不是写0
	rEXT_INT_2_PEND |= (0x0F<<0);
}


void isr_eint16171819(void)
{
	// 真正的isr应该做2件事情。
	// 第一，中断处理代码，就是真正干活的代码
	// 因为EINT16～31是共享中断，所以要在这里再次去区分具体是哪个子中断
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

	// 第二，清除中断挂起
	rEXT_INT_2_PEND |= (0x0f<<0);
	intc_clearvectaddr();
}















