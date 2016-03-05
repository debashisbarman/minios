#include <asm/io.h>
#include <time.h>

#define CMOS_READ(_port) ({ \
		outb(0x70, _port);\
		inb(0x71); \
	})

void kernel_mktime(time_t * time)
{
	time->sec = CMOS_READ(0);
	time->min = CMOS_READ(2);
	time->hour= CMOS_READ(4);
	time->dayofweek = CMOS_READ(6);
	time->day = CMOS_READ(7);
	time->month = CMOS_READ(8);
	time->year = CMOS_READ(9);
}
