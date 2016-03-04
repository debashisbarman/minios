#define __MINIOS_LIBC 1
#include <stddef.h>
#include <stdarg.h>
#include <string.h>

#include <time.h>
#include <asm/io.h>
#include <asm/system.h>
#include <minios/tty.h>
#include <minios/prot.h>
#include <minios/mm.h>

static char buf[1024];

extern int vsprintf();

void init();

volatile size_t timer_ticks = 0;

/* FIXME: fix the timer_ticks */
void do_timer_intr(cpu_state_t * cpu)
{
	timer_ticks++;

	/* if (timer_ticks % 18 == 0)
	 *	printk("Time : %d Sec\n", timer_ticks / 18);
	 */

	if (cpu->int_no >= 40)
		outb(0xa0, 0x20);

	/* Always send interrupt to master */
	outb(0x20, 0x20);	
}

void timer_wait(size_t ticks)
{
	unsigned long eticks;

	eticks = timer_ticks + ticks;

	while(timer_ticks < eticks)
		hlt();
}

/* This is the kernel entry point */
void kernel_main()
{	
	/*
	 * Interrupts are still disabled. Do necessary setups, then
	 * enable them.
	 */
	prot_init();
	trap_init();
	tty_init();
	setup_paging();
	sti();

	init();

	for (;;);
}

static size_t printf(const char *fmt, ...)
{
	va_list args;
        size_t i;

        va_start(args, fmt);
        i = vsprintf(buf, fmt, args);
        va_end(args);
        puts(buf);
        return i;
}

void init()
{
	printf("Initializing...");

	timer_wait(50);

	printf("\n\n[OK]");

	timer_wait(10);

	clrscr();

	/* FIXME: say something more interesting... */
	printf("Hello, world! Welcome to Mini Operating System 0.0.01.\n\n");
	printf("This is a simple kernel written for x86 machines. As the version\n");
	printf("(0.0.01) suggests this is not a mature product. Currently only a \n");
	printf("subset of AT hardwares is supported (screen, keyboard and serial lines).\n");
	printf("Memory management is done with the help of both segmentation and paging.\n");
	printf("Since the kernel alone leads to nowhere, a basic shell is written on the top\n");
	printf("of it. Just type \"help\" and press hit. Enjoy...:-)\n");
	printf("\n- Debashis Barman\n");

	shell();
}
