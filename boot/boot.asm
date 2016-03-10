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

global _start
_start:

prot_mode:
	extern prot_init
	call prot_init

	extern setup_paging
	call setup_paging

	mov esp, stack_top
	extern main
	call main
	cli
hang:
	hlt
	jmp hang

global gdt_load
gdt_load:
	extern gdtp
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
idt_load:
	extern idtp
	lidt [idtp]
	ret
