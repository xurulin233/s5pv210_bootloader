/*
 * 文件名：    led.c    
 * 作者：    朱老师，我稍作修改
 * 描述：    演示汇编开关icache
 */
 
#define GPJ2CON        0xE0200280
#define GPJ2DAT        0xE0200284
 
#define rGPJ2CON    *((volatile unsigned int *)GPJ2CON)
#define rGPJ2DAT    *((volatile unsigned int *)GPJ2DAT)
 
void delay(void);
 
// 该函数实现led闪烁效果
void led_blink(void)
{
    // led初始化，把GPJ2CON中设置为输出模式
    //volatile unsigned int *p = (unsigned int *)GPJ2CON;
    //volatile unsigned int *p1 = (unsigned int *)GPJ2DAT;
    rGPJ2CON = 0x11111111;
    
    while (1)
    {
        // led亮
        rGPJ2DAT = ((0<<3) | (0<<4) | (0<<5));
        // 延时
        delay();
        // led灭
        rGPJ2DAT = ((1<<3) | (1<<4) | (1<<5));
        // 延时
        delay();
    }
}
 
 
void delay(void)
{
    volatile unsigned int i = 900000;        // volatile 让编译器不要优化，这样才能真正的减
    while (i--);                            // 才能消耗时间，实现delay
}
