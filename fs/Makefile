CC = gcc
CFLAGS = -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -c

all: fs.o fat12.o

%.o: %.c
	$(CC) $(CFLAGS) -I ../include $< -o $@

clean:
	rm -rf *.o *~

