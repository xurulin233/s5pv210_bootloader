#include "stdio.h"

void uart_init(void);
void timer0_pwm_init(void);

int main(void)
{
	uart_init();
	
	timer0_pwm_init();
	
	while(1)
	{
		putc('a');
		delay();
	}
	
	return 0;
}