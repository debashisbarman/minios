#include <asm/io.h>
#include <time.h>

inline unsigned char read_cmos(int reg)
{
	outb(0x70, reg);
        return (unsigned char) inb(0x71);
}

void kernel_mktime(struct time * t)
{
        t->sec = read_cmos(0x00);
        t->min = read_cmos(0x02);
        t->hour= read_cmos(0x04);

        t->dayofweek = read_cmos(0x06);
        t->day = read_cmos(0x07);
        t->month = read_cmos(0x08);
        t->year = read_cmos(0x09);

	/* Convert BCD to binary values if necessary */
	t->sec = (t->sec & 0x0F) + ((t->sec / 16) * 10);
	t->min = (t->min & 0x0F) + ((t->min / 16) * 10); 
	t->hour = ((t->hour & 0x0F) + (((t->hour & 0x70) / 16) * 10) ) | (t->hour & 0x80);
	t->day = (t->day & 0x0F) + ((t->day / 16) * 10);
	t->month = (t->month & 0x0F) + ((t->month / 16) * 10);
	t->year = (t->year & 0x0F) + ((t->year / 16) * 10) + 2000;	/* year offset */

	/* 12 hour format */
	if (!(read_cmos(0x0B) & 0x02) && (t->hour & 0x80))
		t->hour = ((t->hour & 0x7F) + 12) % 24;
}
