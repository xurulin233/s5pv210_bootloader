#include <boot_config.h>

	.global _start
	.global IRQ_handle
	.global SWI_handle
	.global SWI_test
	.global reset_handler
	.global exceptionpabort
	.global exceptiondabort
	.global exceptionreserved
	.global exceptionfiq

	.global _interrupt_vector_table

_start:

_interrupt_vector_table:

	ldr	pc, =reset_handle
	ldr	pc, =undef_handle
	ldr	pc, =swi_handle
	ldr	pc, =pabort_handle
	ldr	pc, =dabort_handle
	ldr	pc, =reserved_handle
	ldr	pc, =irq_handle
	ldr	pc, =fiq_handle
	
	
reset_handle:

	/*
	 * set the cpu to SVC32 mode
	 */
	mrs	r0, cpsr
	bic	r0, r0, #0x1f
	orr	r0, r0, #0xd3
	msr	cpsr, r0
	
	// πÿ±’ø¥√≈π∑
	ldr	r0, =0xE2700000			
	mov	r1, #0
	str	r1, [r0]
	
	//bl _disable_interrupt
	
	bl _init_stacks
	bl cpu_init_crit
	
	bl _enable_interrupt
	
	ldr pc, =main
	
cpu_init_crit:
	/*
	 * Invalidate L1 I/D
	 */
	mov	r0, #0			@ set up for MCR
	mcr	p15, 0, r0, c8, c7, 0	@ invalidate TLBs
	mcr	p15, 0, r0, c7, c5, 0	@ invalidate icache
	mcr	p15, 0, r0, c7, c5, 6	@ invalidate BP array
	mcr     p15, 0, r0, c7, c10, 4	@ DSB
	mcr     p15, 0, r0, c7, c5, 4	@ ISB

	/*
	 * disable MMU stuff and caches
	 */
	mrc	p15, 0, r0, c1, c0, 0
	bic	r0, r0, #0x00002000	@ clear bits 13 (--V-)
	bic	r0, r0, #0x00000007	@ clear bits 2:0 (-CAM)
	orr	r0, r0, #0x00000002	@ set bit 1 (--A-) Align
	orr	r0, r0, #0x00000800	@ set bit 11 (Z---) BTB
//#ifdef CONFIG_SYS_ICACHE_OFF
//	bic	r0, r0, #0x00001000	@ clear bit 12 (I) I-cache
//#else
	orr	r0, r0, #0x00001000	@ set bit 12 (I) I-cache
//#endif
	mcr	p15, 0, r0, c1, c0, 0
	
	mov 	pc, lr
	
    .LTORG 	

	
//---------------------------------------------------------------------
//  Initialize Stack
//---------------------------------------------------------------------
_init_stacks:
	mrs      r0, cpsr
	bic      r0, r0, #Mode_MASK
	
	orr      r1, r0, #Mode_IRQ
	msr      cpsr_c, r1                      // IRQ Mode
	ldr      sp, =(IRQStack_PA) 

	orr      r1, r0, #Mode_FIQ
	msr      cpsr_c, r1                      // FIQ Mode
	ldr      sp, =(FIQStack_PA) 

	orr      r1, r0, #Mode_ABT
	msr      cpsr_c, r1                      // ABORT Mode
	ldr      sp, =(AbortStack_PA) 

	orr      r1, r0, #Mode_UND
	msr      cpsr_c, r1                      // UND Mode
	ldr      sp, =(UndefStack_PA) 

	orr      r1, r0, #Mode_SYS
	msr      cpsr_c, r1                      // UND Mode
	ldr      sp, =(SysStack_PA)  

	orr      r1, r0, #Mode_SVC
	msr      cpsr_c, r1                      // Supervisor Mode
	ldr      sp, =(SVCStack_PA)  

	mov      pc, lr

   .LTORG   	
	
.global __bss_start
.global _end
_clear_bss:
	ldr	r0, =__bss_start		/* find start of bss segment        */
	ldr	r1, =_end				/* stop here                        */
	mov 	r2, #0x00000000		/* clear                            */

clbss_l:
	str	r2, [r0]				/* clear loop...                    */
	add	r0, r0, #4
	cmp	r0, r1
	ble	clbss_l   
    mov pc, lr
   .LTORG    
   
   .global switest
switest:
	stmfd	sp!, 	{fp, lr}
	swi 0x8
	ldmfd 	sp!, 	{fp, pc}
	

swi_handle:
	stmfd	sp!, 	{r0-r12, lr}
	mov 	r1,		r0
	mrs 	r0,		spsr
	stmfd	sp!,	{r0}
	
	tst 	r0, 	#0x20
	ldrne 	r0, 	[lr, #-2]
	bicne 	r0, 	r0,		#0xff00
	ldreq 	r0, 	[lr, #-4]
	biceq 	r0, 	r0,		#0xff000000
	
	bl 		c_swi_handler
	
	ldmfd	sp!,	{r0}
	msr 	spsr_cf, r0
	ldmfd 	sp!, 	{r0-r12, pc}^

irq_handle:
	sub		lr,		lr,		#4
	stmfd	sp!, 	{r0-r12, lr}
	bl		irq_handler
	ldmfd 	sp!, 	{r0-r12, pc}^	

	.global _disable_interrupt
_disable_interrupt:
	mrs 	r0,cpsr
	orr 	r1,r0,#NOINT
	msr 	cpsr_c,r1
	and		r0, r0,#NOINT		// Return old interrupt bits
	mov		pc, lr
	
	.LTORG   	

	.global _enable_interrupt
_enable_interrupt:
	mrs 	r1,cpsr
	bic 	r1,r1,#NOINT
	and     r0, r0,#NOINT 	// Extract only the interrupt bits
	orr		r1,r1,r0			// Mask 
	msr 	cpsr_c,r1
	mov   	pc, lr
	
	.LTORG  

	.global _set_interrupt_vector
_set_interrupt_vector:
	
	mcr	p15, 0, r0, c12, c0, 0
	mrc	p15, 0, r0, c12, c0, 0
	
	mov pc, lr
