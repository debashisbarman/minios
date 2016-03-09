#ifndef _HEAD_H
#define _HEAD_H

#define pic_remap()	\
	outb(0x20, 0x11);	\
	outb(0xa0, 0x11);	\
	outb(0x21, 0x20);	\
	outb(0xa1, 0x28);	\
	outb(0x21, 0x04);	\
	outb(0xa1, 0x02);	\
	outb(0x21, 0x01);	\
	outb(0xa1, 0x01);	\
	outb(0x21, inb(0x21));	\
	outb(0xa1, inb(0xa1));	

struct gdt_desc {
	unsigned short lmt_lo, base_lo;
	unsigned char base_md, acc, flg, base_hi;
} __attribute__((packed)); 

struct gdt_sel {
	unsigned short lmt;
	unsigned long base;
} __attribute__((packed));

struct idt_desc {
	unsigned short off_lo, sel;
	unsigned char zero, type;
	unsigned short off_hi;
} __attribute__((packed));

struct idt_sel {
	unsigned short lmt;
	unsigned long base;
} __attribute__((packed));

struct gdt_desc gdt[3];
struct gdt_sel gdtp;

struct idt_desc idt[256];
struct idt_sel idtp;

extern void prot_init(void);

extern void gdt_load(void);
extern void idt_load(void);
extern void intr_gate(size_t n, unsigned long off, unsigned char dpl, unsigned char type);
extern void ignore_intr(void);

struct cpu_state {
	/* segment registers */
	unsigned long gs;
	unsigned long fs;
	unsigned long es;
	unsigned long ds;
	unsigned long cs;
	unsigned long ss;

	/* data registers */
	unsigned long eax;
	unsigned long ebx;
	unsigned long ecx;
	unsigned long edx;

	/* index registers */
	unsigned long esi;
	unsigned long edi;

	/* pointer registers */
	unsigned long eip;
	unsigned long esp;	/* user esp */
	unsigned long ebp; 

	/* control flags */
	unsigned long eflags;

	unsigned long int_no;	/* interrupt number */
	unsigned long error_code;
};

#endif
