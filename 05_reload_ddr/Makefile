include $(ECOS_PRODUCT_DIR)/config.mk

INCDIR	:= $(shell pwd)
# C预处理器的flag，flag就是编译器可选的选项
CPPFLAGS	:= -nostdlib -nostdinc -I$(INCDIR)/include
# C编译器的flag
CFLAGS		:= -Wall -O2 -fno-builtin

#导出这些变量到全局，其实就是给子文件夹下面的Makefile使用
export CC LD OBJCOPY OBJDUMP AR CPPFLAGS CFLAGS

objs := start.o led.o clock.o sdram_init.o

bootload.bin: $(objs)
	$(LD) -Tlink.lds -o bootload.elf $^
	$(OBJCOPY) -O binary bootload.elf bootload.bin
	$(OBJDUMP) -D bootload.elf > bootload_elf.dis
	gcc mkv210_image.c -o mkx210
	./mkx210 bootload.bin 210.bin

	
%.o : %.S
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $< -c

%.o : %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $< -c

clean:
	rm *.o *.elf *.bin *.dis mkx210 -f
