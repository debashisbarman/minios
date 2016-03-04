#include <minios/kernel.h>

__attribute__((__noreturn__))
void exit(void)
{
	/* TODO: Add proper kernel panic. */
	printk("Kernel Panic: exit()\n");
	while ( 1 ) { }
	__builtin_unreachable();
}
