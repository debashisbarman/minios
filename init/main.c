#define __MINIOS_LIBC 1
#include <stddef.h>
#include <stdarg.h>
#include <string.h>

#include <time.h>
#include <asm/io.h>
#include <asm/system.h>
#include <minios/tty.h>
#include <minios/head.h>
#include <minios/sched.h>
#include <minios/mm.h>
#include <minios/kernel.h>

static char buf[1024];

extern int vsprintf();
static void init();

/* This is the kernel entry point */
void kernel_main()
{	
	/*
	 * Interrupts are still disabled. Do necessary setups, then
	 * enable them.
	 */
	tty_init();
	trap_init();
	sched_init();
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

static void init()
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
