CC = gcc
CFLAGS = -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -c

AS = nasm
ASFLAGS = -f elf32

all: memory.o page.o

%.o: %.c
	$(CC) $(CFLAGS) -I ../include $< -o $@

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o *~

