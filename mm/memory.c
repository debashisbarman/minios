/*
 * memory.c
 * 
 * FIXME : do dynamic allocation and rewrite paging.
 */
#include <stddef.h>
#include <minios/mm.h>

/* 
 * name     | size  | description
 * -----------------------------------------
 * Address  | 31-12 | Physical address of the page, or the page table
 * Avail    |  11-9 | Available for kernel use 
 * Reserved |   8-7 | Used by CPU internally
 * D        |     6 | Dirty flag
 * A        |     5 | Set if page has been accessed
 * Reserved |   4-3 | Used by CPU internally
 * U/S      |     2 | User/supervisor priviledge
 * R/W      |     1 | Read/write flag
 * P        |     0 | Present flag
 */

#define PAGE_SIZE		4096
#define NUM_PAGE_TABLE_ENTRY	1024

#define PA_KERNEL_PRESENT	0x3	/* 011 */
#define PA_KERNEL_NOT_PRESENT 	0x2	/* 010 */

/* (static) global objects with GCC extension "__attribute__((align(4096)))" */
unsigned long page_directory[NUM_PAGE_TABLE_ENTRY] __attribute__((aligned(PAGE_SIZE)));
unsigned long page_table[NUM_PAGE_TABLE_ENTRY] __attribute__((aligned(PAGE_SIZE)));

void setup_paging(void)
{
	unsigned long paddr = 0x00000000;	/* Physical address of the page */

	/* Map the first 4MB of memory */
	for(size_t i = 0; i < NUM_PAGE_TABLE_ENTRY; i++) {
		page_table[i] = ((unsigned long) paddr) | PA_KERNEL_PRESENT;	/* supervisor, r/w, present */
		paddr = paddr + PAGE_SIZE;
	};

	/* Fill the first entry of the page directory */
	page_directory[0] = page_table;
	page_directory[0] = page_directory[0] | PA_KERNEL_PRESENT;

	/* Fill the rest of the page directory */
	for(size_t i = 1; i < NUM_PAGE_TABLE_ENTRY; i++)
		page_directory[i] = 0 | PA_KERNEL_NOT_PRESENT;

	/* Put that page directory address into CR3 */
	load_page_directory(page_directory);

	/* Set the paging bit in CR0 to 1 */
	enable_paging();
};
