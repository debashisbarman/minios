MBALIGN     equ  1<<0
MEMINFO     equ  1<<1
FLAGS       equ  MBALIGN | MEMINFO
MAGIC       equ  0x1BADB002
CHECKSUM    equ -(MAGIC + FLAGS)
 
section .multiboot	;---------------------
global mboot
align 4
mboot:
	dd MAGIC
	dd FLAGS
	dd CHECKSUM
 

section .bootstrap_stack, nobits	;-----

align 4
stack_bottom:
	resb 16384
stack_top:
 

section .text	;-----------------------------

global start
start:
	mov esp, stack_top
 
	extern kernel_main
	call kernel_main
 
	cli
.hang:
	hlt
	jmp .hang

global gdt_load

extern gdtp

gdt_load:
	lgdt [gdtp]
	jmp 0x08:reload_segments

reload_segments:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	ret

global idt_load

extern idtp

idt_load:
	lidt [idtp]
	ret
