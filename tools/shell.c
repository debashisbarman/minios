#include <string.h>
#include <asm/io.h>
#include <asm/system.h>
#include <minios/tty.h>
#include <minios/kernel.h>

extern void timer_wait(size_t ticks);

void prompt(void)
{
	printk("\nminios $ ");
}

void shell(void)
{
	prompt();
}

static void reboot(void)
{
	unsigned char good = 0x02;
	while (good & 0x02)
		good = inb(0x64);
	outb(0x64, 0xFE);
	hlt();
}

static void about(void)
{
	printk("\nName : Mini Operating System");
	printk("\nDeveloper : Debashis Barman");
	printk("\nVersion : 0.0.01");
	printk("\nLicense : GPL 3.0\n");
}

static void help(void)
{
	printk("\nShell help : available commands\n");
	printk("---------------------------------\n");
	printk("  about    - print about the OS\n");
	printk("  reboot   - reboot the system\n");
	printk("  clear    - clear the screen\n");
	printk("  help     - print this help\n");
}

void proccmd(char * cmd)
{
	if (strcmp(cmd, "clear") == 0) {
		clrscr();
		gotoxy(0, -1);	/* csr_y = -1 because of "\n" in prompt */
	} else if (strcmp(cmd, "about") == 0)
		about();
	else if (strcmp(cmd, "reboot") == 0) {
		printk("\nrebooting...");
		timer_wait(10);
		reboot();
	} else if (strcmp(cmd, "help") == 0)
		help();
	else
		printk("\n%s : command not found\n", cmd);
}
