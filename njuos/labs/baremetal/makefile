CC = i686-elf-gcc
LD = i686-elf-ld
AS = i686-elf-as
QEMU = qemu-system-i386

CFLAGS = -ffreestanding -m32 -O0 -nostdlib
LDFLAGS = -T linker.ld

OBJS = startup.o main.o

kernel.elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.s
	$(AS) -o $@ $<

run: kernel.elf
	$(QEMU) -kernel kernel.elf -serial stdio

clean:
	rm -f *.o kernel.elf

.PHONY: run clean
