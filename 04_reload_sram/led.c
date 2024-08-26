#define GPJ2CON		0xE0200280
#define GPJ2DAT		0xE0200284

#define rGPJ2CON	*((volatile unsigned int *)GPJ2CON)
#define rGPJ2DAT	*((volatile unsigned int *)GPJ2DAT)

static void delay(void);

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
		rGPJ2DAT = ((0<<3) | (0<<4) | (0<<5));
		// ��ʱ
		delay();
		// led��
		rGPJ2DAT = ((1<<3) | (1<<4) | (1<<5));
		// ��ʱ
		delay();
	}
}

// ��1��led
void led1(void)
{
	rGPJ2CON = 0x11111111;
	rGPJ2DAT = ((0<<3) | (1<<4) | (1<<5));
}

// ��2��led
void led2(void)
{
	rGPJ2CON = 0x11111111;
	rGPJ2DAT = ((0<<3) | (0<<4) | (1<<5));
}

// ��3��led
void led3(void)
{
	rGPJ2CON = 0x11111111;
	rGPJ2DAT = ((0<<3) | (0<<4) | (0<<5));
}

void led_off(void)
{
	rGPJ2CON = 0x11111111;
	rGPJ2DAT = ((1<<3) | (1<<4) | (1<<5));
}


static void delay(void)
{
	volatile unsigned int i = 900000;		// volatile �ñ�������Ҫ�Ż����������������ļ�
	while (i--);							// ��������ʱ�䣬ʵ��delay
}

	
