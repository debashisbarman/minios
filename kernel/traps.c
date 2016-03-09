/*
 * traps.c
 *
 * 'Traps.c' handles hardware traps and faults after we have saved some
 * state in 'asm.asm'.
 */
#include <stddef.h>
#include <asm/io.h>
#include <asm/system.h>
#include <minios/head.h>
#include <minios/kernel.h>

extern void divide_error();
extern void debug();
extern void nmi();
extern void int3();
extern void overflow();
extern void bounds();
extern void invalid_op();
extern void device_not_available();
extern void double_fault();
extern void coprocessor_segment_overrun();
extern void invalid_TSS();
extern void segment_not_present();
extern void stack_segment();
extern void general_protection();
extern void page_fault();
extern void coprocessor_error();
extern void reserved();

void trap_init()
{
	set_intr_gate(0, &divide_error);
	set_intr_gate(1, &debug);
	set_intr_gate(2, &nmi);
	set_intr_gate(4, &overflow);
	set_intr_gate(5, &bounds);
	set_intr_gate(6, &invalid_op);
	set_intr_gate(7, &device_not_available);
	set_intr_gate(8, &double_fault);
	set_intr_gate(9, &coprocessor_segment_overrun);
	set_intr_gate(10, &invalid_TSS);
	set_intr_gate(11, &segment_not_present);
	set_intr_gate(12, &stack_segment);
	set_intr_gate(13, &general_protection);
	set_intr_gate(14, &page_fault);
	set_intr_gate(15, &reserved);
	set_intr_gate(16, &coprocessor_error);

	for (size_t i = 17; i < 32; i++)
		set_intr_gate(i, &reserved);	
}

void do_divide_error()
{
	panic("Divide by zero error");
}

void do_debug()
{
	panic("Debug error");
}

void do_nmi()
{
	panic("NMI interrupt");
}

void do_int3()
{
	panic("Breakpoint exception");
}

void do_overflow()
{
	panic("Overflow exception");
}

void do_bounds()
{
	panic("BOUND range exceeded");
}

void do_invalid_op()
{
	panic("Invalid opcode");
}

void do_device_not_available()
{
	panic("Device not available");
}

void do_double_fault()
{
	panic("Double fault");
}

void do_coprocessor_segment_overrun()
{
	panic("Coprocessor segment overrun");
}

void do_invalid_TSS()
{
	panic("Invalid TSS");
}

void do_segment_not_present()
{
	panic("Segment not present");
}

void do_stack_segment()
{
	panic("Stack segment fault");
}

void do_general_protection()
{
	panic("General protection fault");
}

void do_page_fault(struct cpu_state * cpu)
{
	size_t fault_addr;
	__asm__ __volatile__("mov %%cr2, %0":"=r"(fault_addr));
	printk("Page fault at %x\n", fault_addr);
	for (;;);	
}

void do_coprocessor_error()
{
	panic("Coprocessor error");
}

void do_alignment_check()
{
	panic("Alignment check error");
}

void do_machine_check()
{
	panic("Machine check error");
}

void do_reserved()
{
	panic("Reserved (15,17-31) error");
}
