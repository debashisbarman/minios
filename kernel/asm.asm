global divide_error
extern do_divide_error
divide_error:
	cli
	push byte 0
	push byte 0
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax,0x10
	mov ds, ax
	mov es, ax
	call do_divide_error
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add eax, 8
	iret

global debug
extern do_debug
debug:
	cli
	push byte 0
	push byte 0
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax,0x10
	mov ds, ax
	mov es, ax
	call do_debug
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add eax, 8
	iret

global nmi
extern do_nmi
nmi:
	cli
	push byte 0
	push byte 0
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax,0x10
	mov ds, ax
	mov es, ax
	call do_nmi
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add eax, 8
	iret

global int3
extern do_int3
int3:
	cli
	push byte 0
	push byte 0
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax,0x10
	mov ds, ax
	mov es, ax
	call do_int3
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add eax, 8
	iret

global overflow
extern do_overflow
overflow:
	cli
	push byte 0
	push byte 0
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax,0x10
	mov ds, ax
	mov es, ax
	call do_overflow
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add eax, 8
	iret

global bounds
extern do_bounds
bounds:
	cli
	push byte 0
	push byte 0
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax,0x10
	mov ds, ax
	mov es, ax
	call do_bounds
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add eax, 8
	iret

global invalid_op
extern do_invalid_op
invalid_op:
	cli
	push byte 0
	push byte 0
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax,0x10
	mov ds, ax
	mov es, ax
	call do_invalid_op
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add eax, 8
	iret

global device_not_available
extern do_device_not_available
device_not_available:
	cli
	push byte 0
	push byte 7
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax,0x10
	mov ds, ax
	mov es, ax
	call do_device_not_available
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add eax, 8
	iret

global double_fault
extern do_double_fault ;error
double_fault:
	cli
	push byte 8
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax,0x10
	mov ds, ax
	mov es, ax
	call do_double_fault
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add eax, 8
	iret

global coprocessor_segment_overrun
extern do_coprocessor_segment_overrun
coprocessor_segment_overrun:
	cli
	push byte 0
	push byte 9
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax,0x10
	mov ds, ax
	mov es, ax
	call do_coprocessor_segment_overrun
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add eax, 8
	iret

global invalid_TSS
extern do_invalid_TSS	;error
invalid_TSS:
	cli
	push byte 10
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax,0x10
	mov ds, ax
	mov es, ax
	call do_invalid_TSS
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add eax, 8
	iret

global segment_not_present
extern do_segment_not_present	;error
segment_not_present:
	cli
	push byte 11
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax,0x10
	mov ds, ax
	mov es, ax
	call do_segment_not_present
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add eax, 8
	iret

global stack_segment
extern do_stack_segment	;error
stack_segment:
	cli
	push byte 12
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax,0x10
	mov ds, ax
	mov es, ax
	call do_stack_segment
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add eax, 8
	iret

global general_protection
extern do_general_protection	;error
general_protection:
	cli
	push byte 13
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax,0x10
	mov ds, ax
	mov es, ax
	call do_general_protection
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add eax, 8
	iret

global page_fault
extern do_page_fault	;error
page_fault:
	cli
	push byte 14
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax,0x10
	mov ds, ax
	mov es, ax
	call do_page_fault
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add eax, 8
	iret

global coprocessor_error
extern do_coprocessor_error
coprocessor_error:
	cli
	push byte 0
	push byte 16
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax,0x10
	mov ds, ax
	mov es, ax
	call do_coprocessor_error
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add eax, 8
	iret

global reserved
extern do_reserved
reserved:
	cli
	push byte 0
	push byte 17
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax,0x10
	mov ds, ax
	mov es, ax
	call do_reserved
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add eax, 8
	iret

global ignore_intr
extern do_ignore_intr
ignore_intr:
	cli
	push byte 0
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax,0x10
	mov ds, ax
	mov es, ax
	call do_ignore_intr
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add eax, 8
	iret

global timer_intr		;--------------------
timer_intr:
	cli
	push byte 0
	push byte 32
	pusha
	push ds
	push es
	push fs
	push gs

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov eax, esp

	push eax
	extern do_timer
	mov eax, do_timer
	call eax
	pop eax

	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8
	iret

global kbd_intr
kbd_intr:
	cli
	push byte 0
	push byte 33
	pusha
	push ds
	push es
	push fs
	push gs

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov eax, esp

	push eax
	extern do_kbd_intr
	mov eax, do_kbd_intr
	call eax
	pop eax

	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8
	iret
