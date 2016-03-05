#define move_to_user_mode() \
	__asm__ __volatile__("  \
		cli; \
		mov $0x23, %ax; \
		mov %ax, %ds; \
		mov %ax, %es; \
		mov %ax, %fs; \
		mov %ax, %gs; \
		mov %esp, %eax; \
     		pushl $0x23; \
     		pushl %eax; \
     		pushf; \
     		pushl $0x1B; \
     		push $1f; \
     		iret; \
   		1: \
     	")

#define cli() __asm__ __volatile__ ("cli")
#define sti() __asm__ __volatile__ ("sti")
#define hlt() __asm__ __volatile__ ("hlt")

#define set_trap_gate(n, addr) \
	intr_gate(n, (unsigned long)addr, 0x0, 0)

#define set_intr_gate(n, addr) \
	intr_gate(n, (unsigned long)addr, 0x0, 0)

