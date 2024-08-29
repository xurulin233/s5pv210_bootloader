#include "stdio.h"

void uart_init(void);
void key_init(void);
void key_polling(void);
void led_blink(void);

int main(void)
{
	uart_init();
	key_init();
	//led_blink();
	key_polling();
	
	return 0;
}