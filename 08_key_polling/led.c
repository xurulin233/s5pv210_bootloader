#define GPJ2CON		0xE0200280
#define GPJ2DAT		0xE0200284

#define rGPJ2CON	*((volatile unsigned int *)GPJ2CON)
#define rGPJ2DAT	*((volatile unsigned int *)GPJ2DAT)

void delay(void);

// �ú���Ҫʵ��led��˸Ч��
void led_blink(void)
{
	// led��ʼ����Ҳ���ǰ�GPJ2CON������Ϊ���ģʽ
	//volatile unsigned int *p = (unsigned int *)GPJ2CON;
	//volatile unsigned int *p1 = (unsigned int *)GPJ2DAT;
	rGPJ2CON = 0x11111111;
	
	while (1)
	{
		// led��
		rGPJ2DAT = ((0) | (0<<1) | (0<<2) | (0<<3));
		// ��ʱ
		delay();
		// led��
		rGPJ2DAT = ((1) | (1<<1) | (1<<2) | (1<<3));
		// ��ʱ
		delay();
	}
}

// ��1��led
void led1(void)
{
	rGPJ2CON = 0x11111111;
	rGPJ2DAT = ((0) | (1<<1) | (1<<2) | (1<<3));
}


// ��2��led
void led2(void)
{
	rGPJ2CON = 0x11111111;
	rGPJ2DAT = ((1) | (0<<1) | (1<<2) | (1<<3));
}

// ��3��led
void led3(void)
{
	rGPJ2CON = 0x11111111;
	rGPJ2DAT = ((1) | (1<<1) | (0<<2) | (1<<3));
}

// ��4��led
void led4(void)
{
	rGPJ2CON = 0x11111111;
	rGPJ2DAT = ((1) | (1<<1) | (1<<2) | (0<<3));
}

void led_off(void)
{
	rGPJ2CON = 0x11111111;
	rGPJ2DAT = ((1) | (1<<1) | (1<<2)| (1<<3));
}


void delay(void)
{
	volatile unsigned int i = 900000;		// volatile �ñ�������Ҫ�Ż����������������ļ�
	while (i--);							// ��������ʱ�䣬ʵ��delay
}

	
