#include <asm/io.h>
#include <time.h>

#define CMOS_READ(_port) ({ \
		outb(0x70, _port);\
		inb(0x71); \
	})

void kernel_mktime(time_t * tm)
{
	tm->sec = CMOS_READ(0);
	tm->min = CMOS_READ(2);
	tm->hour= CMOS_READ(4);
	tm->dayofweek = CMOS_READ(6);
	tm->day = CMOS_READ(7);
	tm->month = CMOS_READ(8);
	tm->year = CMOS_READ(9);
}
