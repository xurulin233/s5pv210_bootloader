
#define 	GPD0CON		(0xE02000A0)
#define 	TCFG0		(0xE2500000)
#define 	TCFG1		(0xE2500004)
#define 	CON			(0xE2500008)
#define 	TCNTB0		(0xE250000C)
#define 	TCMPB0		(0xE2500010)

#define 	rGPD0CON	(*(volatile unsigned int *)GPD0CON)
#define 	rTCFG0		(*(volatile unsigned int *)TCFG0)
#define 	rTCFG1		(*(volatile unsigned int *)TCFG1)
#define 	rCON		(*(volatile unsigned int *)CON)
#define 	rTCNTB0		(*(volatile unsigned int *)TCNTB0)
#define 	rTCMPB0		(*(volatile unsigned int *)TCMPB0)


// 初始化PWM timer0，使其输出PWM波形：频率是2KHz、duty为50%
void timer0_pwm_init(void)
{
	// 设置GPD0_0引脚，将其配置为XpwmTOUT_2
	rGPD0CON &= ~(0xf);
	rGPD0CON |= (2);
	
	// 设置PWM定时器的一干寄存器，使其工作
	rTCFG0 &= ~(0xff);
	rTCFG0 |= (65);			// prescaler1 = 65, 预分频后频率为1MHz
	
	rTCFG1 &= ~(0x0f);
	rTCFG1 |= (1);			// MUX2设置为1/2,分频后时钟周期为500KHz
	// 时钟设置好，我们的时钟频率是500KHz，对应的时钟周期是2us。也就是说每隔2us
	// 计一次数。如果要定的时间是x，则TCNTB中应该写入x/2us
	
	rCON |= (1<<3);		// 使能auto-reload，反复定时才能发出PWM波形
	//rTCNTB2 = 250;			// 0.5ms/2us = 500us/2us = 250
	//rTCMPB2 = 125;			// duty = 50%
	
	rTCNTB0 = 50;			
	rTCMPB0 = 25;	
	
	// 第一次需要手工将TCNTB中的值刷新到TCNT中去，以后就可以auto-reload了
	rCON |= (1<<1);		// 打开自动刷新功能
	rCON &= ~(1<<1);		// 关闭自动刷新功能
	
	rCON |= (1);		// 开timer2定时器。要先把其他都设置好才能开定时器
}

















