/*
 * tty_io.c
 *
 * This file contains different functions for console, keyboard
 * and user shell.
 */
#include <string.h>
#include <asm/io.h>
#include <asm/system.h>
#include <minios/head.h>
#include <minios/tty.h>
#include <minios/kernel.h>

#define KBD_DATA_PORT   0x60

char bfr[256];
size_t inbfr = 0;

/* Handles the keyboard interrupt */
void do_kbd_intr(struct cpu_state * cpu)
{
	unsigned char scancode;
	char ch;

	extern size_t csr_x;
	extern size_t csr_y;

	scancode = inb(KBD_DATA_PORT);

	/* If the top bit of the byte we read from the keyboard is
	 * set, that means that a key has just been released. 
	 */
	if (scancode & 0x80) {

	}
	else {
		ch = toascii(scancode);

		switch (ch) {
			case '\b' :	if (csr_x < strlen("minios $ ") + 1)	/* + 1 for the space */
						/* do nothing */;
					else {
						gotoxy(--csr_x, csr_y);
						printk(" ");
						gotoxy(--csr_x, csr_y);
						bfr[--inbfr] = 0;
					}
					break;
			case '\n' : 	proccmd(bfr);
					prompt();
					inbfr = 0;
					bfr[inbfr] = 0;
					break;
			default :	bfr[inbfr++] = ch;
					bfr[inbfr] = 0;
					printk("%c", ch);
					break;
		}
	}	

	if (cpu->int_no >= 40)
		outb(0xa0, 0x20);

	/* Always send interrupt to master */
	outb(0x20, 0x20);	
}

/* Installs the keyboard handler into IRQ1 */
void kbd_init(void)
{
	set_intr_gate(33, &kbd_intr);
}

void tty_init(void)
{
	/* Initialize the console */
	cons_init();

	/* Initialize keyboard */
	kbd_init();
}
