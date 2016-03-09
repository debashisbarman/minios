#define __MINIOS_LIBC 1
#include <stddef.h>
#include <stdarg.h>
#include <string.h>

/* kernel includes */
#include <time.h>
#include <asm/io.h>
#include <asm/system.h>
#include <minios/tty.h>
#include <minios/head.h>
#include <minios/sched.h>
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
	printf("Initializing...\n");
	timer_wait(50);
	printf("\n[OK]");
	timer_wait(10);
	clrscr();

	/* FIXME: say something more interesting... */
	printf("Hello, world! Welcome to Mini Operating System 0.0.01.\n");

	shell();
}
