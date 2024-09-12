#include <exception.h>
#include <stdio.h>



void uart_init();
void timer_request(void);
extern volatile int counter;
static inline unsigned int get_vectors_address(void)
{
    unsigned int temp;

    /* read SCTLR */
	
	__asm__ __volatile__(
		   "mrc p15, 0, %0, c1, c0, 0\n"
			:"=r"(temp)
			:
			
	);
	
    if (temp & (1<<13))
        return (unsigned int ) 0xffff0000;
    /* read VBAR */
    __asm__ __volatile__("mrc p15, 0, %0, c12, c0, 0\n"
            : "=r" (temp) : );
    return (unsigned int ) temp;
}

// ÑÓÊ±º¯Êý
void delay(unsigned long count)
{
	volatile unsigned long i = count;
	while (i--);
}

#if 1
void swifun()
{
    __asm__ (
        "swi 0x1\n"
    );
}

#else
static inline void swifun(int arg)
{
    __asm__ (
		//"stmfd  sp!,  r0\n"
		"mov r0, %0\n"
        "swi 0\n"
		:"=r"(arg)
		:
		:"memory", "cc"
		);
}
#endif
void switest(unsigned int arg);
int main(void)
{
	int temp = 0;
	
	uart_init();
	
	system_initexception();					

	timer_init();
	

	for(;;)
	{
		
		if(temp!=counter && counter%3 == 0)
		{
			switest(counter);
			temp = counter;
		}
	}
}
