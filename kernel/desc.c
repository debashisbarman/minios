/*
 * desc.c
 *
 * This file includes initialization code for protected
 * mode descriptor tables, interrupts...
 */
#include <stddef.h>
#include <asm/io.h>
#include <asm/system.h>
#include <minios/head.h>
#include <minios/kernel.h>

static const unsigned char base = 0;
static const unsigned long lmt = 0xffffffff;
static const unsigned char segsel_kernel_cs = 0x08;

static void init_segment(size_t n, unsigned char dpl, unsigned char type)
{
	gdt[n].base_lo = base & 0xffff;
	gdt[n].base_md = (base >> 16) & 0xff;
	gdt[n].base_hi = (base >> 24) & 0xff;
	gdt[n].lmt_lo = lmt & 0xffff;
	gdt[n].flg = (0x01 << 7) | (0x01 << 6) | 0x0f;
	gdt[n].acc = (0x01 << 7) | ((dpl & 0x03) << 5) | (0x01 << 4) | (type & 0x0f);
}

void intr_gate(size_t n, unsigned long off, unsigned char dpl, unsigned char type)
{
	idt[n].off_lo = off & 0xffff;
	idt[n].off_hi = (off >> 16) & 0xffff;
	idt[n].sel = segsel_kernel_cs;
	idt[n].zero = 0;
	idt[n].type = (0x01 << 7) | ((dpl & 0x03) << 5) | (0x01 << 3) | (0x01 << 2) | (0x01 << 1) | type;
}

void prot_init(void)
{
	gdtp.lmt = (sizeof(struct gdt_desc) * 3) - 1;
	gdtp.base = (unsigned long) &gdt;

	init_segment(0, 0, 0);
	init_segment(1, 0, 0xa);
	init_segment(2, 0, 0x2);

	gdt_load();

	idtp.lmt = (sizeof(struct idt_desc) * 256) - 1;
	idtp.base = (unsigned long) &idt;

	for (size_t i = 0; i < 32; i++)
		set_intr_gate(i, &ignore_intr);

	idt_load();

	pic_remap();
}

void do_ignore_intr(cpu_state_t * cpu)
{
	printk("Interrupt #%d\n", cpu->int_no);
}
