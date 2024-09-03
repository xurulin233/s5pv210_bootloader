

include $(ECOS_PRODUCT_DIR)/config.mk

BL2.bin: start.o lcd.o main.o led.o
	$(LD) -Tlink.lds -o BL2.elf $^
	$(OBJCOPY) -O binary BL2.elf BL2.bin
	$(OBJDUMP) -D BL2.elf > BL2_elf.dis
	
%.o : %.S
	$(CC) -o $@ $< -c -nostdlib

%.o : %.c
	$(CC) -o $@ $< -c -nostdlib

clean:
	rm *.o *.elf *.bin *.dis mkx210 -f

	
	
