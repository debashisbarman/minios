#include <string.h>
#include <time.h>
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
	printk("\nMinios %s is an educational operating system for x86 machines \n", VERSION);
	printk("written in C and Assembly and developed by Debashis Barman.\n");
	printk("\nLicense : GNU General Public License v3.0\n");
	printk("\nDocumentation : https://github.com/debashisbarman/minios/README.md\n");
}

static void help(void)
{
	printk("\nMINI shell, version 1.1.12-stable (minios-%s)\n", VERSION);
	printk("These commands are defined internally.\n\n");
	printk(" clear		clear the screen\n");
	printk(" date		print system date and time\n");
	printk(" help		print this help list\n");
	printk(" minios		print about minios-%s\n", VERSION);
	printk(" reboot		reboot the system\n");
}

void proccmd(char * cmd)
{
	if (strcmp(cmd, "clear") == 0) {
		clrscr();
		gotoxy(0, -1);	/* csr_y = -1 because of "\n" in prompt */
	} else if (strcmp(cmd, "minios") == 0)
		about();
	else if (strcmp(cmd, "reboot") == 0) {
		printk("\nrebooting...\n");
		timer_wait(10);
		printk("\n[NOW]");
		timer_wait(5);
		reboot();
	} else if (strcmp(cmd, "help") == 0)
		help();
	else if (strcmp(cmd, "date") == 0) {
		struct time t;
		kernel_mktime(&t);
                printk("\n%02d/%02d\t%02d:%02d:%02d IST\t%04d\n", t.month, t.day, t.hour, t.min, t.sec, t.year);
	} else
		printk("\nMINI shell : %s : command not found\n", cmd);
}
