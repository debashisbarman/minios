/*
 * This function is used through-out the kernel (including mm and fs)
 * to indicate a major problem.
 */
#include <minios/kernel.h>

void panic(const char * str)
{
	printk("Kernel panic : %s\n", str);
	for (;;);
}
