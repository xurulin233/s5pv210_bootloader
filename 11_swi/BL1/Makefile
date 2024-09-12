
include $(ECOS_PRODUCT_DIR)/config.mk

bootloader1.bin: start.o  sdram_init.o sd_relocate.o led.o clock.o
	$(LD) -Tlink.lds -o bootloader1.elf $^
	$(OBJCOPY) -O binary bootloader1.elf bootloader1.bin
	$(OBJDUMP) -D bootloader1.elf > bootloader1_elf.dis
	gcc mkv210_image.c -o mkx210
	./mkx210 bootloader1.bin BL1.bin
	
%.o : %.S
	$(CC) -o $@ $< -c -nostdlib

%.o : %.c
	$(CC) -o $@ $< -c -nostdlib

clean:
	rm *.o *.elf *.bin *.dis mkx210 -f

	
	
