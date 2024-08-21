/*
 * ¿¿¿¿    start.S    
 * ¿¿¿    ¿¿¿¿¿¿¿¿¿
 * ¿¿¿    ¿¿¿¿¿¿icache
 */
 
#define WTCON        0xE2700000
#define SVC_STACK    0xd0037d80
 
.global _start                    // ¿_start¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿_start¿
_start:
    // ¿1¿¿¿¿¿¿¿¿WTCON¿bit5¿¿0¿¿¿
    ldr r0, =WTCON
    ldr r1, =0x0 //¿¿¿¿¿¿
    ldr r1, =0x00008001 //¿¿¿¿¿¿¿¿¿¿WTCON¿¿¿¿¿¿¿¿
    str r1, [r0]
    
    // ¿2¿¿¿¿SVC¿
    ldr sp, =SVC_STACK
    
    // ¿3¿¿¿/¿icache
    mrc p15,0,r0,c1,c0,0; // ¿CP15¿c1¿r0¿
    //bic r0, r0, #(1<<12) // bit12 ¿0 ¿¿iCache
    orr r0, r0, #(1<<12) // bit12 ¿1 ¿¿iCache
    mcr p15,0,r0,c1,c0,0; // ¿r0¿CP15¿c1¿
 
    // ¿¿C¿¿led_blink
    bl led_blink                    // led_blink¿C¿¿¿¿¿¿¿¿¿
    
    // ¿¿¿¿¿¿¿¿
    b .
