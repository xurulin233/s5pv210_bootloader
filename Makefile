include $(ECOS_PRODUCT_DIR)/config.mk

BL1.bin: start.o led.o uart.o main.o
	$(LD) -TBL1.lds -o BL1.elf $^
	$(OBJCOPY) -O binary BL1.elf BL1.bin
	$(OBJDUMP) -D BL1.elf > BL1_elf.dis
	gcc mkv210_image.c -o mkmini210
	./mkmini210 BL1.bin bootloader.bin
	
%.o : %.S
	$(CC) -o $@ $< -c -nostdlib 

%.o : %.c
	$(CC) -o $@ $< -c -nostdlib

clean:
	rm *.o *.elf *.bin *.dis mkmini210 -f
