
include $(ECOS_PRODUCT_DIR)/config.mk

INCLUDEDIR 	:= $(shell pwd)/include
#CFLAGS 		:= -Wall -O2 -fno-builtin
CFLAGS 		:= -Wall -g -O2 -fno-builtin -mabi=apcs-gnu -march=armv7-a 
##-Wa,-mimplicit-it=thumb -mthumb-interwork
CPPFLAGS   	:= -nostdinc -nostdlib -I$(INCLUDEDIR)

export 	CC AR LD OBJCOPY OBJDUMP INCLUDEDIR CFLAGS CPPFLAGS 

objs := start.o main.o uart.o exception.o timer.o lib/libc.a

BL2.bin: $(objs)
	${LD} -Tzmos.lds -o zmos.elf $^
	${OBJCOPY} -O binary -S zmos.elf $@
	${OBJDUMP} -D zmos.elf > zmos.dis
	
.PHONY : lib/libc.a
lib/libc.a:
	cd lib; make; cd ..
	
%.o:%.c
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o:%.S
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	make  clean -C lib
	rm -f *.bin *.elf *.dis *.o *~
