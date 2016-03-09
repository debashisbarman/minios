/*
 * sched.c
 *
 * "sched.c" is incomplete. Currently it setup pit, then initializes 
 * and handles the timer interrupts.
 *
 * TODO: do some actual multitasking...
 */
#include <stddef.h>
#include <stdbool.h>
#include <asm/io.h>
#include <asm/system.h>
#include <minios/head.h>
#include <minios/sched.h>
#include <minios/kernel.h>

static const unsigned char segsel_kernel_cs = 0x08;

unsigned long interval = 40;	/* min should be 40 */
volatile size_t jiffies = 0;

void do_timer(void)
{
	jiffies++;

	/* if (jiffies % 18 == 0)
	 *	printk("\nTime : %d Sec", jiffies / 18);	
	 */

	/* Send acknowledge to pic master */
	outb(0x20, 0x20);
}

void timer_wait(size_t ticks)
{
	static unsigned long interval;

	interval = jiffies + ticks;

	while(jiffies < interval)
		hlt();
}

void sched_init(void)
{
	unsigned long frequency;
	unsigned char data;
	unsigned short temp;

	/* name | value | size | desc
	 * --------------------------
	 * chan |     0 |    2 | the channel to use, channel 0 = IRQ0
	 * acs  |   0x3 |    2 | how the temp is sent, 3 = lobyte then hibyte
	 * mode |   0x3 |    3 | the mode of the pit, mode 3 = square wave
	 * bcd  |     0 |    1 | bcd or binary mode, 0 = binary, 1 = bcd
	 */
	data = (1 << 5) | (1 << 4) | (1 << 2) | (1 << 1) | 0x00;
	outb(0x43, data);	/* 0x43 = pit command port */

	frequency = 1000 / interval;

	if (frequency > 0)
		/* that's ok */; 
	else
		frequency = 40;  /* minimum 40 Hz */

	temp = (unsigned short) (1193180 / frequency);

	outb(0x40, (unsigned char)(temp & 0xff));
	outb(0x40, (unsigned char)((temp >> 8) & 0xff));

	set_intr_gate(32, &timer_intr);	/* timer */
}
